# ##############################################################################
# Name:        build/cmake/main.cmake Purpose:     Main CMake file Author:
# Martell Created:     2024-11-03 Copyright:   (c) 2024 skstu development team
# Licence:     skstu licence
# ##############################################################################

list(APPEND CMAKE_MODULE_PATH ${xsBUILD_DIR}/cmake/deps/)
if(xsUSE_ZLIB)
  include(zlib)
  if(xsUSE_MINIZIP)
    include(minizip)
  endif()
endif()
if(xsUSE_HTTPPARSER)
  include(http_parser)
endif()
if(xsUSE_SQLITE3)
  include(sqlite3)
endif()
if(xsUSE_TINYXML2)
  include(tinyxml2)
endif()
if(xsUSE_LIBUV)
  include(libuv)
endif()
if(xsUSE_CURL)
  include(CURL)
endif()
if(xsUSE_WXWIDGETS)
  include(wxWidgets)
endif()

list(APPEND CMAKE_MODULE_PATH ${xsBUILD_DIR}/cmake/modules)

include(global)
include(FindWX)
include(FindSSL)
include(build/cmake/functions.cmake) # skstu functions

add_subdirectory(base)
add_subdirectory(projects)
add_subdirectory(tests)
