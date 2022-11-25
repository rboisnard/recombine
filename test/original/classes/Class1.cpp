#include "api/Class1.h"
#include "values.h"
#include "overrides1.h"

#ifdef OVERRIDE_FROM_HEADER
#include "overrides2.h"
#endif

#if defined(OVERRIDE_FROM_HEADER)
#include "overrides3.h"
#endif

namespace recombine {

const std::string& Class1::getValue() const {
  return _value;
}

const std::string Class1::operator() () const {
  std::string result = "class1:";
  result += _value;
  result += ":";
  result += std::to_string(VALUE1);
  return result;
}

} // namespace recombine