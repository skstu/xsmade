# ##############################################################################
# Name:        build/cmake/main.cmake Purpose:     Main CMake file Author:
# Martell Created:     2024-11-03 Copyright:   (c) 2024 skstu development team
# Licence:     skstu licence
# ##############################################################################

option(xsUSE_3RDPARTY "Enable configure 3rdparty" OFF)
option(xsUSE_TESTS "Enable configure tests" ON)
option(xsUSE_BASE "Enable configure base" ON)
option(xsUSE_PROJECTS "Enable configure base" ON)
option(xsUSE_COMPONENTS "Enable configure components" ON)

if(xsUSE_3RDPARTY)
  include(build/cmake/modules/3rdparty.cmake)
endif()
if(xsUSE_BASE)
  include(build/cmake/modules/base.cmake)
endif()
if(xsUSE_COMPONENTS)
  include(build/cmake/modules/components.cmake)
endif()
if(xsUSE_TESTS)
  add_subdirectory(${xsSOURCE_DIR}/tests)
endif()
if(xsUSE_PROJECTS)
  include(build/cmake/modules/FindFFMPEG.cmake)
  include(build/cmake/modules/FindWX.cmake)
  add_subdirectory(${xsSOURCE_DIR}/projects)
endif()
# list(APPEND CMAKE_MODULE_PATH ${xsBUILD_DIR}/cmake/deps/) if(xsUSE_ZLIB)
# include(zlib) if(xsUSE_MINIZIP) include(minizip) endif() endif()
# if(xsUSE_HTTPPARSER) include(http_parser) endif() if(xsUSE_SQLITE3)
# include(sqlite3) endif() if(xsUSE_TINYXML2) include(tinyxml2) endif()
# if(xsUSE_LIBUV) include(libuv) endif() if(xsUSE_CURL) include(CURL) endif()
# if(xsUSE_WXWIDGETS) include(wxWidgets) endif()

# list(APPEND CMAKE_MODULE_PATH ${xsBUILD_DIR}/cmake/modules)

# include(global) include(FindWX) include(FindSSL)
# include(build/cmake/functions.cmake) # skstu functions

# add_subdirectory(base) add_subdirectory(projects) add_subdirectory(tests)
