#############################################################################
# Name:        build/cmake/main.cmake
# Purpose:     Main CMake file
# Author:      Martell
# Created:     2024-11-03
# Copyright:   (c) 2024 skstu development team
# Licence:     skstu licence
#############################################################################

list(APPEND CMAKE_MODULE_PATH "${xsSOURCE_DIR}/build/cmake/modules")

include(global)
include(build/cmake/functions.cmake)        # skstu functions
#[[
include(build/cmake/files.cmake)            # Files list
include(build/cmake/source_groups.cmake)    # Source group definitions
include(build/cmake/functions.cmake)        # wxWidgets functions
include(build/cmake/toolkit.cmake)          # Platform/toolkit settings
include(build/cmake/options.cmake)          # User options
include(build/cmake/init.cmake)             # Init various global build vars
include(build/cmake/pch.cmake)              # Precompiled header support
]]

add_subdirectory(projects projects)