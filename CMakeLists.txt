#############################################################################
# Name:        build/cmake/main.cmake
# Purpose:     Main CMake file
# Author:      Martell
# Created:     2024-11-04
# Copyright:   (c) 2024 skstu development team
# Licence:     skstu licence
#############################################################################
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(WIN32)
  set(CMAKE_SYSTEM_NAME "Windows")
  set(CMAKE_C_COMPILER C:/msys64/clang64/bin/clang.exe)
  set(CMAKE_CXX_COMPILER C:/msys64/clang64/bin/clang++.exe)
elseif(APPLE)
  set(CMAKE_SYSTEM_NAME "macOS")
  set(CMAKE_C_COMPILER /usr/bin/clang)
  set(CMAKE_CXX_COMPILER /usr/bin/clang++)
elseif(UNIX)
  set(CMAKE_SYSTEM_NAME "Linux")
  set(CMAKE_C_COMPILER /usr/bin/clang)
  set(CMAKE_CXX_COMPILER /usr/bin/clang++)
else()
  set(CMAKE_SYSTEM_NAME "Unknown System")
endif()
message(STATUS ${CMAKE_SYSTEM_NAME})

include(build/cmake/policies.cmake NO_POLICY_SCOPE)

set(xsSOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(xsBINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(xsOUTPUT_DIR ${xsBINARY_DIR}/lib)

message(STATUS "SOURCE_DIR: ${xsSOURCE_DIR}")
message(STATUS "BINARY_DIR: ${xsBINARY_DIR}")
message(STATUS "OUTPUT_DIR: ${xsOUTPUT_DIR}")

project(xsmade)

include(build/cmake/main.cmake)
#LIST(APPEND CMAKE_MODULE_PATH ${LOCAL_CMAKE_MODULES_PATH})
#include(global)
#list(APPEND CMAKE_MODULE_PATH "${wxSOURCE_DIR}/build/cmake/modules")
#add_subdirectory(${SOLUTION_ROOT_DIR}/3rdlocal/bit7z-4.0.8/ "bit7z")

