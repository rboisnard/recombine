#include <iostream>


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

#ifndef _CLASS3_H
#define _CLASS3_H

#include <string>


#ifndef _CLASS1_H
#endif // _CLASS1_H

#ifndef _CLASS2_H
#endif // _CLASS2_H


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


int main() {
  recombine::Class1 class1("main1");
  recombine::Class2 class2("main2");
  recombine::Class3 class3("main31", "main32");

  std::cout << "class1 value: " << class1() << std::endl;
  std::cout << "class2 value: " << class2() << std::endl;
  std::cout << "class3 value: " << class3() << std::endl;
}
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

#ifndef _VALUES_H
#define _VALUES_H

#define VALUE1 1
#define VALUE2 2
#define VALUE3 3
#define VALUE4 4

#endif // _VALUES_H

#ifndef _OVERRIDES1_H
#define _OVERRIDES1_H

#undef VALUE1
#undef VALUE2
#undef VALUE3
#undef VALUE4

#define VALUE1 11
#define VALUE2 12
#define VALUE3 13
#define VALUE4 14

#define OVERRIDE_FROM_HEADER

#endif // _OVERRIDES1_H


#ifdef OVERRIDE_FROM_HEADER
#ifndef _OVERRIDES2_H
#define _OVERRIDES2_H

#undef VALUE1
#undef VALUE2
#undef VALUE3
#undef VALUE4

#define VALUE1 21
#define VALUE2 22
#define VALUE3 23
#define VALUE4 24

#endif // _OVERRIDES2_H

#endif

#if defined(OVERRIDE_FROM_HEADER)
#ifndef _OVERRIDES3_H
#define _OVERRIDES3_H

#undef VALUE1
#undef VALUE2
#undef VALUE3
#undef VALUE4

#define VALUE1 31
#define VALUE2 32
#define VALUE3 33
#define VALUE4 34

#endif // _OVERRIDES3_H

#endif

namespace recombine {

const std::string& Class1::getValue() const {
  return _value;
}

const std::string Class1::operator() () const {
  std::string result = "class1:";
  result += _value;
  result += ":";
  result += std::to_string(31);
  return result;
}

} // namespace recombine
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

#ifndef _VALUES_H
#define _VALUES_H

#define VALUE1 1
#define VALUE2 2
#define VALUE3 3
#define VALUE4 4

#endif // _VALUES_H

#ifndef _OVERRIDES1_H
#define _OVERRIDES1_H

#undef VALUE1
#undef VALUE2
#undef VALUE3
#undef VALUE4

#define VALUE1 11
#define VALUE2 12
#define VALUE3 13
#define VALUE4 14

#define OVERRIDE_FROM_HEADER

#endif // _OVERRIDES1_H


#ifdef OVERRIDE_FROM_COMBINE_CONFIG
#ifndef _OVERRIDES2_H
#define _OVERRIDES2_H

#undef VALUE1
#undef VALUE2
#undef VALUE3
#undef VALUE4

#define VALUE1 21
#define VALUE2 22
#define VALUE3 23
#define VALUE4 24

#endif // _OVERRIDES2_H

#endif

#if defined(OVERRIDE_FROM_CMAKE_CONFIG)
#endif

namespace recombine {

const std::string& Class2::getValue() const {
  return _value;
}

const std::string Class2::operator() () const {
  std::string result = "class2:";
  result += _value;
  result += ":";
  result += std::to_string(22);
  return result;
}

} // namespace recombine
#ifndef _CLASS3_H
#define _CLASS3_H

#include <string>


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

#ifndef _VALUES_H
#define _VALUES_H

#define VALUE1 1
#define VALUE2 2
#define VALUE3 3
#define VALUE4 4

#endif // _VALUES_H

#ifndef _OVERRIDES1_H
#define _OVERRIDES1_H

#undef VALUE1
#undef VALUE2
#undef VALUE3
#undef VALUE4

#define VALUE1 11
#define VALUE2 12
#define VALUE3 13
#define VALUE4 14

#define OVERRIDE_FROM_HEADER

#endif // _OVERRIDES1_H


#ifdef OVERRIDE_FROM_COMBINE_CONFIG
#ifndef _OVERRIDES2_H
#define _OVERRIDES2_H

#undef VALUE1
#undef VALUE2
#undef VALUE3
#undef VALUE4

#define VALUE1 21
#define VALUE2 22
#define VALUE3 23
#define VALUE4 24

#endif // _OVERRIDES2_H

#endif

#if defined(OVERRIDE_FROM_CMAKE_CONFIG)
#endif

namespace recombine {

const std::string Class3::operator() () const {
  std::string result = "class3:";
  result += _class1.getValue();
  result += ":";
  result += _class2.getValue();
  result += ":";
  result += std::to_string(23);
  return result;
}

} // namespace recombine
