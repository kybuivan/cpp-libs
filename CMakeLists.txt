cmake_minimum_required(VERSION 3.10)

project(twin VERSION 0.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
configure_file(twin_config.h.in twin_config.h)

add_executable(twin twin.cxx)

target_include_directories(twin PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )