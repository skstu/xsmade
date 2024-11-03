cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(WIN32)
  set(CMAKE_SYSTEM_NAME "Windows")
  set(CMAKE_C_COMPILER C:/msys64/clang64/bin/clang.exe)
  set(CMAKE_CXX_COMPILER C:/msys64/clang64/bin/clang++.exe)
elseif(APPLE)
  set(CMAKE_SYSTEM_NAME "macOS")
elseif(UNIX)
  set(CMAKE_SYSTEM_NAME "Linux")
  set(CMAKE_C_COMPILER /usr/bin/clang)
  set(CMAKE_CXX_COMPILER /usr/bin/clang++)
else()
  set(CMAKE_SYSTEM_NAME "Unknown System")
endif()
message(STATUS ${CMAKE_SYSTEM_NAME})

set(xsSOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(xsBINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(xsOUTPUT_DIR ${wxBINARY_DIR}/lib)

file(READ "${wxSOURCE_DIR}/include/version.h" XS_VERSION_H_CONTENTS)
string(REGEX MATCH "wxMAJOR_VERSION[ \t]+([0-9]+)"
    wxMAJOR_VERSION ${WX_VERSION_H_CONTENTS})
string (REGEX MATCH "([0-9]+)"
    wxMAJOR_VERSION ${wxMAJOR_VERSION})
string(REGEX MATCH "wxMINOR_VERSION[ \t]+([0-9]+)"
    wxMINOR_VERSION ${WX_VERSION_H_CONTENTS})
string (REGEX MATCH "([0-9]+)"
    wxMINOR_VERSION ${wxMINOR_VERSION})
string(REGEX MATCH "wxRELEASE_NUMBER[ \t]+([0-9]+)"
    wxRELEASE_NUMBER ${WX_VERSION_H_CONTENTS})
string (REGEX MATCH "([0-9]+)"
    wxRELEASE_NUMBER ${wxRELEASE_NUMBER})

project(cmade)
