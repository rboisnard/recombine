#include "api/Class3.h"
#include "values.h"
#include "overrides1.h"

#ifdef OVERRIDE_FROM_COMBINE_CONFIG
#include "overrides2.h"
#endif

#if defined(OVERRIDE_FROM_CMAKE_CONFIG)
#include "overrides3.h"
#endif

namespace recombine {

const std::string Class3::operator() () const {
  std::string result = "class3:";
  result += _class1.getValue();
  result += ":";
  result += _class2.getValue();
  result += ":";
  result += std::to_string(VALUE3);
  return result;
}

} // namespace recombine