cmake_minimum_required(VERSION 3.10)

project(twin VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(USE_CORE "Use twin provided core implementation" ON)

configure_file(twin_config.h.in twin_config.h)

if(USE_CORE)
  add_subdirectory(core)
  list(APPEND EXTRA_LIBS core)
endif()

add_executable(twin twin.cxx)
target_link_libraries(twin PUBLIC ${EXTRA_LIBS})
target_include_directories(twin PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )