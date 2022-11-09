cmake_minimum_required(VERSION 3.15)

# set the project name and version
project(twin VERSION 0.1)

# specify the C++ standard
add_library(twin_compiler_flags INTERFACE)
target_compile_features(twin_compiler_flags INTERFACE cxx_std_11)

set(CMAKE_DEBUG_POSTFIX d)

# add compiler warning flags just when building this project via
# the BUILD_INTERFACE genex
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(twin_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

# should we use our own core functions
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# configure a header file to pass the version number only
configure_file(twin_config.h.in twin_config.h)

# add the core library
add_subdirectory(core)

# add the executable
add_executable(twin twin.cxx)

set_target_properties(twin PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_link_libraries(twin PUBLIC core twin_compiler_flags)
# add the binary tree to the search path for include files
target_include_directories(twin PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

# add the install targets
install(TARGETS twin DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/twin_config.h"
  DESTINATION include
)

install(EXPORT coreTargets
  FILE coreTargets.cmake
  DESTINATION lib/cmake/coreTargets
)

include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/coreConfig.cmake"
  INSTALL_DESTINATION "lib/cmake/example"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/coreConfigVersion.cmake"
  VERSION "${twin_VERSION_MAJOR}.${twin_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/coreConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/coreConfigVersion.cmake
  DESTINATION lib/cmake/core
  )
  
export(EXPORT coreTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/coreTargets.cmake"
)
# enable testing
include(CTest)

# does the application run
add_test(NAME Runs COMMAND twin 25)

# does the usage message work?
add_test(NAME Usage COMMAND ${PROJECT_BINARY_DIR}/twin)
set_tests_properties(Usage
  PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number"
  )
  
# define a function to simplify adding tests
function(do_test target arg result)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  set_tests_properties(Comp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()

# do a bunch of result based tests
do_test(twin 4 "4 is 2")
do_test(twin 9 "9 is 3")
do_test(twin 5 "5 is 2.236")
do_test(twin 7 "7 is 2.645")
do_test(twin 25 "25 is 5")
do_test(twin -25 "-25 is (-nan|nan|0)")
do_test(twin 0.0001 "0.0001 is 0.01")

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${twin_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${twin_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)