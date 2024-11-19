cmake_minimum_required(VERSION 3.5)

project(zipcc)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES
    ${OUT_HEADER_S} ${OUT_SOURCE_S}
    ${xs3RDPARTY_DIR}/zlib/contrib/minizip/zip.c
    ${xs3RDPARTY_DIR}/zlib/contrib/minizip/unzip.c
    ${xs3RDPARTY_DIR}/zlib/contrib/minizip/ioapi.c
    ${xs3RDPARTY_DIR}/zlib/contrib/minizip/iowin32.c)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${xsINCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
          ${xs3RDPARTY_DIR}/utfcpp/source/ ${xs3RDPARTY_DIR}/zlib/
          ${xs3RDPARTY_DIR}/zlib/contrib/minizip/)

xs_set_target_output_dir(${PROJECT_NAME})
