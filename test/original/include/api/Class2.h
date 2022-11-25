#ifndef _CLASS2_H
#define _CLASS2_H

#include <string>

namespace recombine {

class Class2 {
private:
  std::string _value;

public:
  explicit Class2(const std::string& value)
      : _value(value) {}

  Class2 operator=(const Class2& class2) {
    return Class2(class2.getValue());
  }

  const std::string& getValue() const;
  const std::string operator() () const;
};

} // namespace recombine

#endif // _CLASS2_H