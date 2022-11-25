add_executable(test_recombined)
target_include_directories(test_recombined PRIVATE .)
target_sources(test_recombined
  PRIVATE
  test_recombined.cpp
  recombined.h
)
target_link_libraries(test_recombined
  GTest::gtest_main
  m
  pthread
  dl
  crypt
)
target_compile_options(test_recombined PRIVATE -Wall -Wextra -Werror -O3 -g)
target_compile_definitions(test_recombined PRIVATE OVERRIDE_FROM_CMAKE_CONFIG)
add_test(
  NAME test_recombined
  COMMAND test_recombined
)