# ##############################################################################
# Name:        build/cmake/main.cmake Purpose:     Main CMake file Author:
# Martell Created:     2024-11-04 Copyright:   (c) 2024 skstu development team
# Licence:     skstu licence
# ##############################################################################

# cmake -G "Ninja Multi-Config" .. cmake --build . --config Release cmake -G
# "Ninja" .. -DCMAKE_BUILD_TYPE=Release cmake --build . --config Release

cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(xsSOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(xsROOT_DIR ${xsSOURCE_DIR})
set(xs3RDPARTY_DIR ${xsSOURCE_DIR}/3rdparty)
set(xsINCLUDE_DIR ${xsSOURCE_DIR}/include)
set(xsOUTPUT_DIR ${xsSOURCE_DIR}/out)
set(xsLIBS_DIR ${xsSOURCE_DIR}/out/libs)
set(xsBIN_DIR ${xsSOURCE_DIR}/out/bin)
set(xsPROJECTS_DIR ${xsSOURCE_DIR}/projects)
set(xsBASE_DIR ${xsSOURCE_DIR}/base)
set(xsBUILD_DIR ${xsSOURCE_DIR}/build)
set(xsBUILD_INSTALLED_DIR ${xsBUILD_DIR}/installed)
if(WIN32)
  set(xsMSYS2_DIR "c:/msys64")
endif()

include(build/cmake/modules/message.cmake)
include(build/cmake/policies.cmake)
include(build/cmake/toolchain.cmake)
include(build/cmake/build_type.cmake)
include(build/cmake/modules/global.cmake)
include(build/cmake/functions.cmake)
project(xsmade VERSION 1.0.1)

include(build/cmake/main.cmake)

gfn_message_info("CMAKE_C_COMPILER=${CMAKE_C_COMPILER}")
gfn_message_info("CMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}")
gfn_message_info("CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}")
gfn_message_info("CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
gfn_message_info("CMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}")
