project(minizip C)
# set(CMAKE_CXX_STANDARD 17) set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
  set(SOURCES
      ${CMAKE_CURRENT_SOURCE_DIR}/../zlib/contrib/minizip/minizip.c
      ${CMAKE_CURRENT_SOURCE_DIR}/../zlib/contrib/minizip/ioapi.c
      ${CMAKE_CURRENT_SOURCE_DIR}/../zlib/contrib/minizip/iowin32.c
      ${CMAKE_CURRENT_SOURCE_DIR}/../zlib/contrib/minizip/mztools.c
      ${CMAKE_CURRENT_SOURCE_DIR}/../zlib/contrib/minizip/unzip.c
      ${CMAKE_CURRENT_SOURCE_DIR}/../zlib/contrib/minizip/zip.c
      ${CMAKE_CURRENT_SOURCE_DIR}/../zlib/contrib/minizip/miniunz.c)
elseif(APPLE)
  set(SOURCES
      ${CMAKE_CURRENT_SOURCE_DIR}/../zlib/contrib/minizip/minizip.c
      ${CMAKE_CURRENT_SOURCE_DIR}/../zlib/contrib/minizip/ioapi.c
      ${CMAKE_CURRENT_SOURCE_DIR}/../zlib/contrib/minizip/mztools.c
      ${CMAKE_CURRENT_SOURCE_DIR}/../zlib/contrib/minizip/unzip.c
      ${CMAKE_CURRENT_SOURCE_DIR}/../zlib/contrib/minizip/zip.c
      ${CMAKE_CURRENT_SOURCE_DIR}/../zlib/contrib/minizip/miniunz.c)
endif()

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR}/../zlib/contrib/minizip/
                       MINIZIP_HDRS OUTPUT_SOURCES)

set(INSTALL_BIN_DIR
    "${CMAKE_INSTALL_PREFIX}/bin"
    CACHE PATH "Installation directory for executables")
set(INSTALL_LIB_DIR
    "${CMAKE_INSTALL_PREFIX}/lib"
    CACHE PATH "Installation directory for libraries")
set(INSTALL_INC_DIR
    "${CMAKE_INSTALL_PREFIX}/include"
    CACHE PATH "Installation directory for headers")
set(INSTALL_MAN_DIR
    "${CMAKE_INSTALL_PREFIX}/share/man"
    CACHE PATH "Installation directory for manual pages")
set(INSTALL_PKGCONFIG_DIR
    "${CMAKE_INSTALL_PREFIX}/share/pkgconfig"
    CACHE PATH "Installation directory for pkgconfig (.pc) files")

if(MSVC)
  add_compile_options(/wd4996 /wd4267)
endif()

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(
  ${PROJECT_NAME} PRIVATE ${SOLUTION_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
                          ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(MSVC)
  msvc_link_flags_set_console(${PROJECT_NAME})
  if(ENABLE_MSVC_CRT_MT)
    msvc_crt_set(${PROJECT_NAME} "/MT")
  endif(ENABLE_MSVC_CRT_MT)
  # MSVC_USE_PCH(${PROJECT_NAME} ${entry}/stdafx.h ${entry}/stdafx.cc)
endif()

set(ZLIB_PC ${CMAKE_CURRENT_BINARY_DIR}/minizip.pc)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/zlib.pc.cmakein ${ZLIB_PC} @ONLY)
# configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/zconf.h.cmakein
# ${CMAKE_CURRENT_BINARY_DIR}/zconf.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR})

install(
  TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}")
install(FILES ${MINIZIP_HDRS} DESTINATION "${INSTALL_INC_DIR}/contrib/minizip")
# install(FILES zlib.3 DESTINATION "${INSTALL_MAN_DIR}/man3")
install(FILES ${ZLIB_PC} DESTINATION "${INSTALL_PKGCONFIG_DIR}")
