cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
project(gui_imgui CXX)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake ${PROJECT_SOURCE_DIR}/../cmake/external)

message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

include(FetchContent)
include(glfw)
include(glad)
include(imgui)

file(GLOB _files
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp"
)

add_executable(${PROJECT_NAME} ${_files})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE external::glfw external::glad external::imgui)