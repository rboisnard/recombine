#include <iostream>

#include "api/Class1.h"
#include "api/Class2.h"
#include "api/Class3.h"

int main() {
  recombine::Class1 class1("main1");
  recombine::Class2 class2("main2");
  recombine::Class3 class3("main31", "main32");

  std::cout << "class1 value: " << class1() << std::endl;
  std::cout << "class2 value: " << class2() << std::endl;
  std::cout << "class3 value: " << class3() << std::endl;
}