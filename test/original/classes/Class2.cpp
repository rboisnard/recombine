#include "api/Class2.h"
#include "values.h"
#include "overrides1.h"

#ifdef OVERRIDE_FROM_COMBINE_CONFIG
#include "overrides2.h"
#endif

#if defined(OVERRIDE_FROM_CMAKE_CONFIG)
#include "overrides3.h"
#endif

namespace recombine {

const std::string& Class2::getValue() const {
  return _value;
}

const std::string Class2::operator() () const {
  std::string result = "class2:";
  result += _value;
  result += ":";
  result += std::to_string(VALUE2);
  return result;
}

} // namespace recombine