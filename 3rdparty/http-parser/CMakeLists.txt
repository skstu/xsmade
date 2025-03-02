project(http_parser)

set(SOURCES http_parser.c http_parser_method.cxx)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} HTTP_PARSER_HDRS
                       OUTPUT_SOURCES)

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

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME}
                           PRIVATE ${xs3RDPARTY_DIR}/http-parser/)

set(HTTP_PARSER_PC ${CMAKE_CURRENT_BINARY_DIR}/http-parser.pc)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/http-parser.pc.cmakein
               ${HTTP_PARSER_PC} @ONLY)
# configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/zconf.h.cmakein
# ${CMAKE_CURRENT_BINARY_DIR}/zconf.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR})

install(
  TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}")
install(FILES ${HTTP_PARSER_HDRS} DESTINATION "${INSTALL_INC_DIR}/http-parser")
# install(FILES zlib.3 DESTINATION "${INSTALL_MAN_DIR}/man3")
install(FILES ${HTTP_PARSER_PC} DESTINATION "${INSTALL_PKGCONFIG_DIR}")
