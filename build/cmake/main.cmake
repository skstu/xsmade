#############################################################################
# Name:        build/cmake/main.cmake
# Purpose:     Main CMake file
# Author:      Martell
# Created:     2024-11-03
# Copyright:   (c) 2024 skstu development team
# Licence:     skstu licence
#############################################################################

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/modules)

include(global)
#include(FindICU)
include(build/cmake/functions.cmake)        # skstu functions

add_subdirectory(projects)
add_subdirectory(tests)