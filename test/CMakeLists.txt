cmake_minimum_required(VERSION 3.21)

add_executable(example1
    example1.cpp
)
target_link_libraries(example1 PRIVATE redirect)
add_test(example1 "")