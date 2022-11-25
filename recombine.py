import argparse
import logging
from pathlib import Path
import re
import yaml

class CompileDefinitionList:
  def __init__(self, input_config: dict) -> None:
    self._internal = {}
    for definition in input_config["definitions"]:
      if type(definition) is dict:
        if len(definition) > 1:
          logging.warning(f"too many compile definitions in listed element {{{', '.join(definition.keys())}}}")
        else:
          key = list(definition)[0]
          self._internal[key] = definition[key]
      else:
        if "=" in definition:
          key, value = definition.split("=", 1)
          self._internal[key] = value
        else:
          self._internal[definition] = None

  def __contains__(self, key) -> bool:
    return key in self._internal

  def __delitem__(self, key) -> None:
    del(self._internal[key])

  def __getitem__(self, key):
    return self._internal[key]

  def __iter__(self):
    for key in self._internal:
      yield key

  def __repr__(self) -> str:
    return self._internal.__repr__()

  def __setitem__(self, key, value) -> None:
    self._internal[key] = value


def _parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(
    prog="recombine",
    description="aggregate multiple C/C++ source files into one"
  )
  parser.add_argument(
    "-o", "--output",
    action="store",
    dest="output_file",
    default="answer.cpp",
    help="output filename, 'answer.cpp' by default",
    required=False
  )
  parser.add_argument(
    "-d", "--directory",
    action="store",
    dest="directory",
    default=".",
    help="directory containing source files, current directory by default",
    required=False
  )
  parser.add_argument(
    "-f", "--config",
    action="store",
    dest="config_file",
    default="recombine.yaml",
    help="YAML file describing the files which need to be combined together",
    required=False
  )
  parser.add_argument(
    "-v", "--verbose",
    action="store_true",
    dest="verbose",
    default=False,
    help="print debug information during the process on the standard output",
    required=False
  )
  return parser.parse_args()

def _validate_arguments(args: argparse.Namespace) -> None:
  if not Path(args.config_file).exists():
    logging.error(f"config file '{args.config_file}' not found")
    exit(1)
  if not Path(args.directory).exists():
    logging.error(f"source directory '{args.directory}' not found")
    exit(1)

def _parse_include(src: Path, line: str, definitions: CompileDefinitionList, include_dirs: list, condition: bool) -> str:
  result = ""
  headers = re.search("#include[ ]+\"([\./-_a-zA-Z0-9]+)\"", line)
  if headers:
    header = None
    for include_dir in include_dirs:
      tmp_header = src/include_dir/headers.groups(0)[0]
      if tmp_header.exists():
        header = tmp_header
        break
    if header is None:
      logging.warning(f"'{headers.groups(0)[0]}' not found")
    else:
      logging.info(f"new include {header}")
      result += _parse_file(src, header, definitions, include_dirs, condition)
  else:
    # system header
    logging.info("system header")
    result += _parse_line(line, definitions)
  result += "\n"
  return result

def _update_definitions(line: str, definitions: CompileDefinitionList) -> str:
  defs = re.search("#define[ ]+(.*)$", line)
  if " " not in defs.groups(0)[0]:
    definitions[defs.groups(0)[0]] = None
    logging.info(f"new definition {defs.groups(0)[0]}")
    return defs.groups(0)[0]
  key, value = defs.groups(0)[0].split(" ")
  definitions[key] = value
  logging.info(f"new definition {key} = {value}")
  return key

def _remove_definitions(line: str, definitions: CompileDefinitionList) -> None:
  defs = re.search("#undef[ ]+(.*)$", line)
  if defs.groups(0)[0] in definitions:
    del definitions[defs.groups(0)[0]]
    logging.info(f"removed definition {defs.groups(0)[0]}")

def _parse_line(line: str, definitions: CompileDefinitionList) -> str:
  if "#if" in line or "#endif" in line:
    return line
  for key in definitions:
    pattern = re.compile(f"(?!\w)*{key}(?!\w)*")
    if pattern.search(line) is not None:
      logging.info(f"replacing {key}")
    if definitions[key] is not None:
      line = pattern.sub(definitions[key], line)
    else:
      line = pattern.sub(f"/* removed {key} */", line)
  return line

def _parse_file(src: Path, filepath: Path, definitions: CompileDefinitionList, include_dirs: list, condition: bool) -> str:
  results = []
  results.append("")
  multiline = ""
  conditions = []
  conditions.append(condition)

  with open(filepath, "r") as input_file:
    for line in input_file:
      if "#include" in line and conditions[-1]:
        results[-1] += _parse_line(_parse_include(src, line, definitions, include_dirs, conditions[-1]), definitions)

      elif "#define" in line and conditions[-1]:
        if line.endswith("\\"):
          multiline = line[-2]
        else:
          new_definition = _update_definitions(line, definitions)
          results[-1] += _parse_line(line, {key: definitions[key] for key in definitions if key != new_definition})

      elif len(multiline) > 0 and conditions[-1]:  # still #define
        if line.endswith("\\"):
          multiline = f"{multiline} {line[-2]}"
        else:
          new_definition = _update_definitions(multiline, definitions)
          results[-1] += _parse_line(line, {key: definitions[key] for key in definitions if key != new_definition})

      elif "#undef" in line and conditions[-1]:
        _remove_definitions(line, definitions)
        results[-1] += _parse_line(line, definitions)

      elif "#if" in line:
        results.append(_parse_line(line, definitions))
        ifndefs = re.search("#ifndef[ ]+(.*)$", line)
        if ifndefs is not None:
          conditions.append(ifndefs.groups(0)[0] not in definitions)
          continue
        ifdefs = re.search("#ifdef[ ]+(.*)$", line)
        if ifdefs is not None:
          conditions.append(ifdefs.groups(0)[0] in definitions)
          continue
        ifnotdefineds = re.search("#if[ ]+not[ ]+defined[ ]+\((.*)\)$", line)
        if ifdefs is not None:
          conditions.append(ifnotdefineds.groups(0)[0] not in definitions)
          continue
        ifdefineds = re.search("#if[ ]+defined[ ]*\((.*)\)$", line)
        if ifdefineds is not None:
          conditions.append(ifdefineds.groups(0)[0] in definitions)
          continue
        else:
          conditions.append(True) # not preprocessing evaluation here
          continue

      elif "#endif" in line:
        tmp_result = results[-1]
        del(results[-1])
        del(conditions[-1])
        if len(results) == 0:
          logging.error("too many #endif")
          exit(1)
        results[-1] += tmp_result
        results[-1] += _parse_line(line, definitions)

      else:
        if conditions[-1]:
          results[-1] += _parse_line(line, definitions)

  if len(results) > 1:
    logging.warning(f"{len(results) - 1} #if/#ifdef/#ifndef are missing a #endif, content will be missing")

  results[0] += "\n"
  return results[0]

def main():
  # command arguments
  args = _parse_args()

  log_level = logging.INFO if args.verbose else logging.WARNING
  logging.basicConfig(level=log_level)
  _validate_arguments(args)
  src = Path(args.directory)

  # read config file
  config = {}
  with open(args.config_file, "r") as config_file:
    try:
      config = yaml.safe_load(config_file)
    except yaml.YAMLError as e:
      logging.error(f"cannot read '{args.config_file}', exiting")
      exit(1)

  # validate config file
  if "sources" not in config:
    logging.error(f"no sources listed in '{args.config_file}', there should be a key 'sources' containing a list of source files to combine")
    exit(1)

  for source_file in config["sources"]:
    if not (src/source_file).exists():
      logging.warning(f"source file '{src/source_file}' not found")
      exit(1)

  for source_file in config["ignore_list"]:
    if source_file in config["sources"]:
      logging.warning(f"source file '{src/source_file}' is listed in both 'sources' and 'ignore_list', this is not compatible")
      exit(1)

  output = ""
  for source_file in config["sources"]:
    cdl = CompileDefinitionList(config)
    output += _parse_file(
      src,
      src/source_file,
      cdl,
      config["include_dirs"],
      True
    )

  with open(args.output_file, "w") as output_file:
    output_file.write(output)

if __name__ == "__main__":
  main()