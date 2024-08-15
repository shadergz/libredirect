cmake_minimum_required(VERSION 3.21)
project(Redirect)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(redirect STATIC)

target_include_directories(redirect PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    $<INSTALL_INTERFACE:include/redirect>
)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)