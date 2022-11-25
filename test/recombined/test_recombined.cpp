#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "recombined.h"

TEST(original, class1) {
  recombine::Class1 class1("test1");
  EXPECT_THAT(class1(), ::testing::StrEq("class1:test1:31"));
}

TEST(original, class2) {
  recombine::Class2 class2("test2");
  EXPECT_THAT(class2(), ::testing::StrEq("class2:test2:22"));
}

TEST(original, class3) {
  recombine::Class3 class3("test31", "test32");
  EXPECT_THAT(class3(), ::testing::StrEq("class3:test31:test32:23"));
}