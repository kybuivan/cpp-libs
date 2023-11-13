cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0079 NEW) # for line 67

set(PROJECT ImGuiFileDialog_App)

enable_language(C CXX)
project(${PROJECT} CXX)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake ${PROJECT_SOURCE_DIR}/../cmake/external)

message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

include(FetchContent)
include(glfw)
include(glad)
include(stb)
include(imgui)

if(MSVC)
add_definitions(-DMSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else ()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Wpedantic -Wdeprecated-declarations -Wunused-parameter")
endif ()

add_definitions(${GLFW_DEFINITIONS})
add_definitions(-DIMGUI_DISABLE_OBSOLETE_FUNCTIONS)
add_definitions(-DCUSTOM_IMGUIFILEDIALOG_CONFIG="${CMAKE_SOURCE_DIR}/CustomImGuiFileDialogConfig.h")
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
include(imgui_file_dialog)
target_include_directories(ImGuiFileDialog PRIVATE
    ${CMAKE_SOURCE_DIR}
)

file(GLOB MAIN_SOURCES ${CMAKE_SOURCE_DIR}/main.cpp)
file(GLOB CUSTOM_SOURCES ${CMAKE_SOURCE_DIR}/CustomImGuiFileDialogConfig.h)
file(GLOB RES_SOURCES 
        ${CMAKE_SOURCE_DIR}/CustomFont.cpp 
        ${CMAKE_SOURCE_DIR}/CustomFont.h)
source_group(main FILES ${MAIN_SOURCES})
source_group(src\\Res FILES ${RES_SOURCES})

if (APPLE)
    ##set(ICON icon.icns)
    ##set_source_files_properties(icon.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
endif()

include_directories(
        ${PLOG_INCLUDE_DIR}
        ${GLM_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}
)

add_executable(${PROJECT}
    MACOSX_BUNDLE
    ##${ICON}
    ${RES_SOURCES}
    ${MAIN_SOURCES}
    ${CUSTOM_SOURCES}
)

if(UNIX)
    target_compile_options(${PROJECT} PUBLIC "-Wno-unknown-pragmas")
endif()

if (APPLE)
    set_target_properties(${PROJECT}
        PROPERTIES
        OUTPUT_NAME "${PROJECT}_Macos"
        MACOSX_BUNDLE_EXECUTABLE_NAME "${PROJECT}"
        MACOSX_BUNDLE_BUNDLE_NAME "${PROJECT}"
        FOLDER "${PROJECT}"
        ##RESOURCE icon.icns
        MACOSX_BUNDLE_SHORT_VERSION_STRING ""
        MACOSX_BUNDLE_LONG_VERSION_STRING ""
        ##MACOSX_BUNDLE_ICON_FILE icon.icns
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/MacOSXBundleInfo.plist.in")
elseif(WIN32)
    set_target_properties(${PROJECT} PROPERTIES OUTPUT_NAME "${PROJECT}_WIn32")
elseif(UNIX)
    set_target_properties(${PROJECT} PROPERTIES OUTPUT_NAME "${PROJECT}_Unix")
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}")
install(TARGETS ${PROJECT} DESTINATION ${CMAKE_INSTALL_PREFIX})

target_link_libraries(${PROJECT} PRIVATE
    external::glfw
    external::glad
    external::imgui
    external::imgui_file_dialog
    external::stb
)
