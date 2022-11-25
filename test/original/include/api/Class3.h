#ifndef _CLASS3_H
#define _CLASS3_H

#include <string>

#include "api/Class1.h"
#include "api/Class2.h"

namespace recombine {

class Class3 {
private:
  Class1 _class1;
  Class2 _class2;

public:
  Class3(const std::string& value1, const std::string& value2)
      : _class1(Class1(value1)),
        _class2(Class2(value2)) {}

  const std::string operator() () const;
};

} // namespace recombine

#endif // _CLASS3_H