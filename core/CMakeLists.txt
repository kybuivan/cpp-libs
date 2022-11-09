# add the library that runs
add_library(core twin_core.cxx)

set_property(TARGET core PROPERTY VERSION "0.1.0")
set_property(TARGET core PROPERTY SOVERSION "1")

# state that anybody linking to us needs to include the current source dir
# to find twin_core.h, while we don't.
target_include_directories(core
            INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
            $<INSTALL_INTERFACE:include>
          )

# should we use our own core functions
option(USE_CORE "Use twin provided core implementation" ON)

if(USE_CORE)
  target_compile_definitions(core PRIVATE "USE_MYMATH")

  add_executable(MakeTable MakeTable.cxx)
  target_link_libraries(MakeTable PRIVATE twin_compiler_flags)

  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    DEPENDS MakeTable
    )

  # library that just does sqrt
  add_library(SqrtLibrary STATIC
      mysqrt.cxx
      ${CMAKE_CURRENT_BINARY_DIR}/Table.h
      )

  # state that we depend on our binary dir to find Table.h
  target_include_directories(SqrtLibrary PRIVATE
                ${CMAKE_CURRENT_BINARY_DIR}
                )

  target_link_libraries(SqrtLibrary PUBLIC twin_compiler_flags)
  target_link_libraries(core PRIVATE SqrtLibrary)
endif()

target_link_libraries(core PUBLIC twin_compiler_flags)

# state that SqrtLibrary need PIC when the default is shared libraries
set_target_properties(SqrtLibrary PROPERTIES
                      POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS}
                      )
                      
# install libs
set(installable_libs core twin_compiler_flags)
if(TARGET SqrtLibrary)
  list(APPEND installable_libs SqrtLibrary)
endif()
install(TARGETS ${installable_libs} DESTINATION lib)

# install include headers
install(FILES twin_core.h DESTINATION include)