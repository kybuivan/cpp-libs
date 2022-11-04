add_library(core twin_core.cxx)
target_link_libraries(core tutorial_compiler_flags)
target_include_directories(core
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )