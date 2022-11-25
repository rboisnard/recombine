#ifndef _CLASS1_H
#define _CLASS1_H

#include <string>

namespace recombine {

class Class1 {
private:
  std::string _value;

public:
  explicit Class1(const std::string& value)
      : _value(value) {}

  Class1 operator=(const Class1& class1) {
    return Class1(class1.getValue());
  }

  const std::string& getValue() const;
  const std::string operator() () const;
};

} // namespace recombine

#endif // _CLASS1_H