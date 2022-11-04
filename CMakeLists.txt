cmake_minimum_required(VERSION 3.15)

# set the project name and version
project(twin VERSION 0.1)

# specify the C++ standard
add_library(twin_compiler_flags INTERFACE)
target_compile_features(twin_compiler_flags INTERFACE cxx_std_11)

# add compiler warning flags just when building this project via
# the BUILD_INTERFACE genex
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(twin_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

# should we use our own core functions
option(USE_CORE "Use twin provided core implementation" ON)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(twin_config.h.in twin_config.h)

# add the core library
if(USE_CORE)
  add_subdirectory(core)
  list(APPEND EXTRA_LIBS core)
endif()

# add the executable
add_executable(twin twin.cxx)
target_link_libraries(twin PUBLIC ${EXTRA_LIBS} twin_compiler_flags)

# add the binary tree to the search path for include files
target_include_directories(twin PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )



install(TARGETS twin DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/twin_config.h"
  DESTINATION include
)