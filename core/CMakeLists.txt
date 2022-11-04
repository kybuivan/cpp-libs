add_library(core twin_core.cxx)
target_link_libraries(core twin_compiler_flags)

# link our compiler flags interface library
target_include_directories(core
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )

# does this system provide the log and exp functions?
include(CheckCXXSourceCompiles)
check_cxx_source_compiles("
  #include <cmath>
  int main() {
    std::log(1.0);
    return 0;
  }
" HAVE_LOG)
check_cxx_source_compiles("
  #include <cmath>
  int main() {
    std::exp(1.0);
    return 0;
  }
" HAVE_EXP)

if(HAVE_LOG AND HAVE_EXP)
  target_compile_definitions(core
                             PRIVATE "HAVE_LOG" "HAVE_EXP")
endif()

# install libs
set(installable_libs core twin_compiler_flags)
install(TARGETS ${installable_libs} DESTINATION lib)

# install include headers
install(FILES twin_core.h DESTINATION include)
