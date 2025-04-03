project(sys)

# gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
# set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

set(common_srcs_ "${CMAKE_CURRENT_SOURCE_DIR}/sys.h"
                 "${CMAKE_CURRENT_SOURCE_DIR}/sys.cc")

if(xsSYSTYPE_WINDOWS)
  set(srcs_dir "win")
elseif(xsSYSTYPE_APPLE)
  set(srcs_dir "apple")
elseif(xsSYSTYPE_LINUX)
  set(srcs_dir "linux")
endif()
set(srcs_
    "${CMAKE_CURRENT_SOURCE_DIR}/${srcs_dir}/net.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/${srcs_dir}/proc.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/${srcs_dir}/common.cc")

set(SOURCES ${common_srcs_} ${srcs_})

add_library(${PROJECT_NAME} STATIC ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${xsINCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
          ${xs3RDPARTY_DIR}/utfcpp/source/ ${xs3RDPARTY_DIR}/tinyxml2/)

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

set(PROJECT_PC ${CMAKE_CURRENT_BINARY_DIR}/sys.pc)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/sys.pc.cmakein ${PROJECT_PC} @ONLY)
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
