# set minimum cmake version
cmake_minimum_required(VERSION 3.22.1)

# project name and language
project(example LANGUAGES C)

# require C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

# add sqlite3 library
find_package(SQLite3 REQUIRED)

# add executable
add_executable(main test.c add_order.c T5.c)
target_link_libraries(main PRIVATE SQLite::SQLite3)

# add test executable
add_executable(cpp_test test.c add_order.c T5.c)
target_link_libraries(cpp_test PRIVATE SQLite::SQLite3)

# enable testing functionality
enable_testing()

# define tests
add_test(
  NAME cpp_test
  COMMAND cpp_test
)

