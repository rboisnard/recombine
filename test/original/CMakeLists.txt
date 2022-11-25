add_executable(decoupled)
target_include_directories(decoupled PRIVATE include)
target_sources(decoupled
  PRIVATE
  main.cpp
  classes/Class1.cpp
  classes/Class2.cpp
  classes/Class3.cpp
  include/api/Class1.h
  include/api/Class2.h
  include/api/Class3.h
  include/values.h
  include/overrides1.h
  include/overrides2.h
  include/overrides3.h
)
target_link_libraries(decoupled
  m
  pthread
  dl
  crypt
)
target_compile_options(decoupled PRIVATE -Wall -Wextra -Werror -O3 -g)
target_compile_definitions(decoupled PRIVATE OVERRIDE_FROM_CMAKE_CONFIG)

add_executable(test_original)
target_include_directories(test_original PRIVATE include)
target_sources(test_original
  PRIVATE
  test_original.cpp
  classes/Class1.cpp
  classes/Class2.cpp
  classes/Class3.cpp
  include/api/Class1.h
  include/api/Class2.h
  include/api/Class3.h
  include/values.h
  include/overrides1.h
  include/overrides2.h
  include/overrides3.h
)
target_link_libraries(test_original
  GTest::gtest_main
  m
  pthread
  dl
  crypt
)
target_compile_options(test_original PRIVATE -Wall -Wextra -Werror -O3 -g)
target_compile_definitions(test_original PRIVATE OVERRIDE_FROM_CMAKE_CONFIG)
add_test(
  NAME test_original
  COMMAND test_original
)