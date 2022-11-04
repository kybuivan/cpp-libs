add_library(core twin_core.cxx)

target_include_directories(core
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )