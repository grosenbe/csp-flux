add_executable(cspflux-test
  cspflux-test.cpp)

target_include_directories(cspflux-test PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(cspflux-test
  spa
  gtest
  gtest_main
  cspflux)

target_compile_options(cspflux-test PRIVATE
  -Wall -Wextra -Wpedantic -Werror)

file(COPY ${CMAKE_SOURCE_DIR}/test/assets/testfield.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
