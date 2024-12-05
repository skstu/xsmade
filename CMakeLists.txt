# ##############################################################################
# Name:        build/cmake/main.cmake Purpose:     Main CMake file Author:
# Martell Created:     2024-11-04 Copyright:   (c) 2024 skstu development team
# Licence:     skstu licence
# ##############################################################################

# cmake -G "Ninja Multi-Config" .. cmake --build . --config Release cmake -G
# "Ninja" .. -DCMAKE_BUILD_TYPE=Release cmake --build . --config Release

cmake_minimum_required(VERSION 3.5)

if(NOT CMAKE_CONFIGURATION_TYPES)
  get_property(HAVE_MULTI_CONFIG_GENERATOR GLOBAL
               PROPERTY GENERATOR_IS_MULTI_CONFIG)
  if(HAVE_MULTI_CONFIG_GENERATOR)
    set(CMAKE_CONFIGURATION_TYPES
        "Debug;Release"
        CACHE STRING "Available build types" FORCE)
  endif()
endif()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(default_build_type "Debug")
  message(
    STATUS
      "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE
      "${default_build_type}"
      CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
                                               "RelWithDebInfo" "MinSizeRel")
endif()

if(CMAKE_CONFIGURATION_TYPES)
  message(
    STATUS
      "Multi-config generator detected. Available build types: ${CMAKE_CONFIGURATION_TYPES}"
  )
else()
  message(
    STATUS "Single-config generator detected. Build type: ${CMAKE_BUILD_TYPE}")
endif()

# set(CMAKE_EXPORT_COMPILECOMMANDS ON)

set(xsSYSTYPE_WINDOWS ON)
set(xsSYSTYPE_APPLE OFF)
set(xsSYSTYPE_LINUX OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(WIN32)
  add_definitions(-DUNICODE -D_UNICODE)
  set(MSYS2_DIR c:/msys64/)
  set(MSYS2_CLANG64_DIR ${MSYS2_DIR}/clang64/)
  set(MSYS2_MINGW64_DIR ${MSYS2_DIR}/mingw64/)
  set(xsSYSTYPE_WINDOWS ON)
  set(xsSYSTYPE_APPLE OFF)
  set(xsSYSTYPE_LINUX OFF)
  set(CMAKE_SYSTEM_NAME "Windows")
  set(CMAKE_C_COMPILER ${MSYS2_CLANG64_DIR}/bin/clang.exe)
  set(CMAKE_CXX_COMPILER ${MSYS2_CLANG64_DIR}/bin/clang++.exe)

  add_compile_options(-Wno-inconsistent-dllimport)
elseif(APPLE)
  enable_language(OBJC)
  set(xsSYSTYPE_WINDOWS OFF)
  set(xsSYSTYPE_APPLE ON)
  set(xsSYSTYPE_LINUX OFF)
  set(CMAKE_SYSTEM_NAME "macOS")
  set(CMAKE_C_COMPILER /usr/bin/clang)
  set(CMAKE_CXX_COMPILER /usr/bin/clang++)
elseif(UNIX)
  set(xsSYSTYPE_WINDOWS OFF)
  set(xsSYSTYPE_APPLE OFF)
  set(xsSYSTYPE_LINUX ON)
  set(CMAKE_SYSTEM_NAME "Linux")
  set(CMAKE_C_COMPILER /usr/bin/clang)
  set(CMAKE_CXX_COMPILER /usr/bin/clang++)
else()
  set(CMAKE_SYSTEM_NAME "Unknown System")
endif()
message(STATUS ${CMAKE_SYSTEM_NAME})

include(build/cmake/policies.cmake NO_POLICY_SCOPE)

set(xsSOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(xsROOT_DIR ${xsSOURCE_DIR})
set(xs3RDPARTY_DIR ${xsSOURCE_DIR}/3rdparty)
set(xsINCLUDE_DIR ${xsSOURCE_DIR}/include)
set(xsOUTPUT_DIR ${xsSOURCE_DIR}/out)
set(xsLIBS_DIR ${xsSOURCE_DIR}/out/libs)
set(xsBIN_DIR ${xsSOURCE_DIR}/out/bin)
set(xsPROJECTS_DIR ${xsSOURCE_DIR}/projects)
set(xsBUILD_DIR ${xsSOURCE_DIR}/build)
set(xsBUILD_INSTALLED_DIR ${xsBUILD_DIR}/installed)

# set(xsBINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}) set(xsOUTPUT_DIR
# ${xsBINARY_DIR}/lib)

# message(STATUS "SOURCE_DIR: ${xsSOURCE_DIR}") message(STATUS "BINARY_DIR:
# ${xsBINARY_DIR}") message(STATUS "OUTPUT_DIR: ${xsOUTPUT_DIR}")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      "Debug"
      CACHE STRING "Build type" FORCE)
endif()

set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
                                             "RelWithDebInfo" "MinSizeRel")

set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE BOOL "enable output - clangd compile commands" FORCE)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g") # Release with Debug Info
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG") # MinSizeRel

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Flags: ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}}")

project(xsmade)

set(xsUSE_WXWIDGETS ON)
if(xsUSE_WXWIDGETS)
  set(wxBUILD_SHARED
      OFF
      CACHE BOOL "Build wxWidgets as shared library" FORCE)
  if(xsSYSTYPE_WINDOWS)
    set(wxBUILD_TOOLKIT
        "msw"
        CACHE STRING "Choose wxWidgets toolkit" FORCE)
    #[[
    set(wxUSE_ACCESSIBILITY
        OFF
        CACHE BOOL "Choose wxWidgets toolkit" FORCE)
        ]]
    add_compile_options(-Wno-deprecated-declarations)
  elseif(xsSYSTYPE_APPLE)
    set(wxBUILD_TOOLKIT
        "osx_cocoa"
        CACHE STRING "Choose wxWidgets toolkit" FORCE)
    set(wxUSE_WEBVIEW
        OFF
        CACHE BOOL "Choose wxWidgets toolkit" FORCE)
  elseif(xsSYSTYPE_LINUX)
    set(wxBUILD_TOOLKIT
        "gtk2"
        CACHE STRING "Choose wxWidgets toolkit" FORCE)
  endif()
  set(wxBUILD_SAMPLES
      # "ALL"
      "OFF"
      CACHE STRING "Choose wxWidgets toolkit" FORCE)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-command-line-argument")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-command-line-argument")
  add_subdirectory(${xs3RDPARTY_DIR}/wxwidgets/ "wxWidgets")
endif(xsUSE_WXWIDGETS)

# tinyxml2
add_subdirectory(${xs3RDPARTY_DIR}/tinyxml2/ "tinyxml2")
# sqlite3
add_subdirectory(${xs3RDPARTY_DIR}/sqlite3/ "sqlite3")

set(ZLIB_BUILD_EXAMPLES
    OFF
    CACHE BOOL "disabled zlib build examples." FORCE)
add_subdirectory(${xs3RDPARTY_DIR}/zlib/ "zlib")
# set_target_properties(zlibstatic PROPERTIES FOLDER "3rdparty")
# set_target_properties(zlib PROPERTIES FOLDER "3rdparty")

set(CMAKE_DEBUG_POSTFIX
    ""
    CACHE STRING "..." FORCE)
add_subdirectory(${xs3RDPARTY_DIR}/minizip/ "minizip")
# set_target_properties(minizip PROPERTIES FOLDER "3rdparty")

add_subdirectory(${xs3RDPARTY_DIR}/http-parser/ "http_parser")
# set_target_properties(wxwidgets PROPERTIES FOLDER "3rdparty") cmake -G Ninja
# .. -DwxBUILD_SAMPLES=ALL -DwxBUILD_SHARED=OFF
# -DCMAKE_C_FLAGS="-Wno-unused-command-line-argument"
# -DCMAKE_CXX_FLAGS="-Wno-unused-command-line-argument"

set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(LIBUV_BUILD_SHARED OFF CACHE BOOL "" FORCE)
add_subdirectory(${xs3RDPARTY_DIR}/libuv/ "uv_a")

include(build/cmake/main.cmake)
# LIST(APPEND CMAKE_MODULE_PATH ${LOCAL_CMAKE_MODULES_PATH}) include(global)
# list(APPEND CMAKE_MODULE_PATH "${wxSOURCE_DIR}/build/cmake/modules")
# add_subdirectory(${SOLUTION_ROOT_DIR}/3rdlocal/bit7z-4.0.8/ "bit7z")
