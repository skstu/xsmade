# ##############################################################################
# Name:        build/cmake/main.cmake Purpose:     Main CMake file Author:
# Martell Created:     2024-11-04 Copyright:   (c) 2024 skstu development team
# Licence:     skstu licence
# ##############################################################################
cmake_minimum_required(VERSION 3.5)

set(xsSYSTYPE_WINDOWS ON)
set(xsSYSTYPE_APPLE OFF)
set(xsSYSTYPE_LINUX OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(WIN32)
  set(xsSYSTYPE_WINDOWS ON)
  set(xsSYSTYPE_APPLE OFF)
  set(xsSYSTYPE_LINUX OFF)
  set(CMAKE_SYSTEM_NAME "Windows")
  set(CMAKE_C_COMPILER C:/msys64/clang64/bin/clang.exe)
  set(CMAKE_CXX_COMPILER C:/msys64/clang64/bin/clang++.exe)
elseif(APPLE)
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
set(xs3RDPARTY_DIR ${xsSOURCE_DIR}/3rdparty/)
set(xsINCLUDE_DIR ${xsSOURCE_DIR}/include/)

# set(xsBINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}) set(xsOUTPUT_DIR
# ${xsBINARY_DIR}/lib)

# message(STATUS "SOURCE_DIR: ${xsSOURCE_DIR}") message(STATUS "BINARY_DIR:
# ${xsBINARY_DIR}") message(STATUS "OUTPUT_DIR: ${xsOUTPUT_DIR}")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      Debug
      CACHE STRING "Build type" FORCE)
endif()
set(CMAKE_BUILD_TYPE
    Debug
    CACHE STRING "Build type" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

project(xsmade)

set(wxBUILD_SHARED
    OFF
    CACHE BOOL "Build wxWidgets as shared library" FORCE)
if(xsSYSTYPE_WINDOWS)
  set(wxBUILD_TOOLKIT
      "msw"
      CACHE STRING "Choose wxWidgets toolkit" FORCE)
elseif()
set(wxBUILD_TOOLKIT
"osx_cocoa"
CACHE STRING "Choose wxWidgets toolkit" FORCE)
endif()
set(wxBUILD_SAMPLES
    "ALL"
    CACHE STRING "Choose wxWidgets toolkit" FORCE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-command-line-argument")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-command-line-argument")
add_subdirectory(${xsSOURCE_DIR}/3rdparty/wxwidgets/ "wxWidgets")
# set_target_properties(wxwidgets PROPERTIES FOLDER "3rdparty") cmake -G Ninja
# .. -DwxBUILD_SAMPLES=ALL -DwxBUILD_SHARED=OFF
# -DCMAKE_C_FLAGS="-Wno-unused-command-line-argument"
# -DCMAKE_CXX_FLAGS="-Wno-unused-command-line-argument"
include(build/cmake/main.cmake)
# LIST(APPEND CMAKE_MODULE_PATH ${LOCAL_CMAKE_MODULES_PATH}) include(global)
# list(APPEND CMAKE_MODULE_PATH "${wxSOURCE_DIR}/build/cmake/modules")
# add_subdirectory(${SOLUTION_ROOT_DIR}/3rdlocal/bit7z-4.0.8/ "bit7z")
