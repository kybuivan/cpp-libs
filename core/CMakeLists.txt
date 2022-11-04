add_library(core twin_core.cxx)
target_link_libraries(core twin_compiler_flags)

# link our compiler flags interface library
target_include_directories(core
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )

# install libs
set(installable_libs core twin_compiler_flags)
install(TARGETS ${installable_libs} DESTINATION lib)

# install include headers
install(FILES twin_core.h DESTINATION include)
