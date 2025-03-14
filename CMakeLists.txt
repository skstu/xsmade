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
set(xsOUTPUT_DIR ${xsSOURCE_DIR})
set(xsLIBS_DIR ${xsSOURCE_DIR}/libs)
set(xsBIN_DIR ${xsSOURCE_DIR}/bin)
set(xsTOOLS_DIR ${xsSOURCE_DIR}/tools)
set(xsTOOLS_NSIS_PLUGIN_DIR ${xsTOOLS_DIR}/NSIS/NSIS/Plugins/amd64-unicode)
set(xsOUTPUT_COMPONENTS_DIR ${xsBIN_DIR}/components)
set(xsOUTPUT_PLUGINS_DIR ${xsBIN_DIR}/plugins)
set(xsCOMPONENTS_DIR ${xsSOURCE_DIR}/components)
set(xsOUTPUT_ENGINE_DIR ${xsBIN_DIR}/engine)
set(xsPROJECTS_DIR ${xsSOURCE_DIR}/projects)
set(xsBASE_DIR ${xsSOURCE_DIR}/base)
set(xsBUILD_DIR ${xsSOURCE_DIR}/build)
set(xsBUILD_INSTALLED_DIR ${xsBUILD_DIR}/installed)

include(build/cmake/modules/message.cmake)
include(build/cmake/policies.cmake)
include(build/cmake/toolchain.cmake)
include(build/cmake/build_type.cmake)
include(build/cmake/modules/global.cmake)
include(build/cmake/functions.cmake)
include(build/cmake/modules/FindSSL.cmake)

set(xsLIBS_LIB_DIR ${xsLIBS_DIR}/${CMAKE_BUILD_TYPE}/lib)
set(xsLIBS_INCLUDE_DIR ${xsLIBS_DIR}/${CMAKE_BUILD_TYPE}/include)
set(xsBUILD_INSTALLED_LIB_DIR ${xsBUILD_DIR}/installed/${CMAKE_BUILD_TYPE}/lib)
set(xsBUILD_INSTALLED_INCLUDE_DIR
    ${xsBUILD_DIR}/installed/${CMAKE_BUILD_TYPE}/include)

set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE BOOL "enable output - clangd compile commands" FORCE)
project(xsmade VERSION 1.0.1)

set(xsBASE_INSTALL_PREFIX ${xsSOURCE_DIR}/libs/${CMAKE_BUILD_TYPE})
include(build/cmake/main.cmake)

gfn_message_info("CMAKE_C_COMPILER=${CMAKE_C_COMPILER}")
gfn_message_info("CMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}")
gfn_message_info("CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}")
gfn_message_info("CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
gfn_message_info("CMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}")
