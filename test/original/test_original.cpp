#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "api/Class1.h"
#include "api/Class2.h"
#include "api/Class3.h"

TEST(original, class1) {
  recombine::Class1 class1("test1");
  EXPECT_THAT(class1(), ::testing::StrEq("class1:test1:31"));
}

TEST(original, class2) {
  recombine::Class2 class2("test2");
  EXPECT_THAT(class2(), ::testing::StrEq("class2:test2:32"));
}

TEST(original, class3) {
  recombine::Class3 class3("test31", "test32");
  EXPECT_THAT(class3(), ::testing::StrEq("class3:test31:test32:33"));
}