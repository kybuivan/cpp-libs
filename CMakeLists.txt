cmake_minimum_required(VERSION 3.15)

project(twin VERSION 0.1)

add_library(tutorial_compiler_flags INTERFACE)
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_11)
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

option(USE_CORE "Use twin provided core implementation" ON)

configure_file(twin_config.h.in twin_config.h)

if(USE_CORE)
  add_subdirectory(core)
  list(APPEND EXTRA_LIBS core)
endif()

add_executable(twin twin.cxx)

target_link_libraries(twin PUBLIC ${EXTRA_LIBS} tutorial_compiler_flags)

target_include_directories(twin PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

target_compile_options(tutorial_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)