# ##############################################################################
# Name:        build/cmake/projects/CMakeLists.txt Purpose:     Build projects
# components Author:      Martell Created:     2024-11-04 Copyright:   (c) 2024
# skstu development team Licence:     skstu licence
# ##############################################################################

add_subdirectory(stl)
add_subdirectory(sys)
if(xsUSE_ZLIB AND xsUSE_MINIZIP)
  add_subdirectory(zipcc)
endif()
if(xsUSE_WXWIDGETS)
  add_subdirectory(wxui)
endif()
add_subdirectory(uvpp)
if(xsUSE_CURL)
  add_subdirectory(curlcc)
endif()
