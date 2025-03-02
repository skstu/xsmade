project(zipcc)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
if(xsSYSTYPE_WINDOWS)
  set(SOURCES
      ${OUT_HEADER_S}
      ${OUT_SOURCE_S}
      ${xs3RDPARTY_DIR}/zlib/contrib/minizip/zip.c
      ${xs3RDPARTY_DIR}/zlib/contrib/minizip/unzip.c
      ${xs3RDPARTY_DIR}/zlib/contrib/minizip/ioapi.c
      ${xs3RDPARTY_DIR}/zlib/contrib/minizip/iowin32.c)
elseif(xsSYSTYPE_APPLE)
  set(SOURCES
      ${OUT_HEADER_S}
      ${OUT_SOURCE_S}
      ${xs3RDPARTY_DIR}/zlib/contrib/minizip/zip.c
      ${xs3RDPARTY_DIR}/zlib/contrib/minizip/unzip.c
      ${xs3RDPARTY_DIR}/zlib/contrib/minizip/ioapi.c)
elseif(xsSYSTYPE_LINUX)
  set(SOURCES
      ${OUT_HEADER_S}
      ${OUT_SOURCE_S}
      ${xs3RDPARTY_DIR}/zlib/contrib/minizip/zip.c
      ${xs3RDPARTY_DIR}/zlib/contrib/minizip/unzip.c
      ${xs3RDPARTY_DIR}/zlib/contrib/minizip/ioapi.c)
endif()

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${xsINCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
          ${xs3RDPARTY_DIR}/utfcpp/source/ ${xs3RDPARTY_DIR}/zlib/
          ${xs3RDPARTY_DIR}/zlib/contrib/minizip/)

# xs_set_target_output_dir(${PROJECT_NAME})

set(INSTALL_BIN_DIR
    "${xsBASE_INSTALL_PREFIX}/bin"
    CACHE PATH "Installation directory for executables")
set(INSTALL_LIB_DIR
    "${xsBASE_INSTALL_PREFIX}/lib"
    CACHE PATH "Installation directory for libraries")
set(INSTALL_INC_DIR
    "${xsBASE_INSTALL_PREFIX}/include"
    CACHE PATH "Installation directory for headers")
set(INSTALL_MAN_DIR
    "${xsBASE_INSTALL_PREFIX}/share/man"
    CACHE PATH "Installation directory for manual pages")
set(INSTALL_PKGCONFIG_DIR
    "${xsBASE_INSTALL_PREFIX}/share/pkgconfig"
    CACHE PATH "Installation directory for pkgconfig (.pc) files")

set(PROJECT_PC ${CMAKE_CURRENT_BINARY_DIR}/zipcc.pc)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/zipcc.pc.cmakein ${PROJECT_PC} @ONLY)
# configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/zconf.h.cmakein
# ${CMAKE_CURRENT_BINARY_DIR}/zconf.h @ONLY)

install(
  TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}")
# install(FILES ${OUT_HEADER_S} DESTINATION "${INSTALL_INC_DIR}/stl")
# install(FILES zlib.3 DESTINATION "${INSTALL_MAN_DIR}/man3")
install(FILES ${PROJECT_PC} DESTINATION "${INSTALL_PKGCONFIG_DIR}")
