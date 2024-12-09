cmake_minimum_required(VERSION 3.5)

project(MediaStreamComm)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${xsROOT_DIR}
          ${xsINCLUDE_DIR}
          ${CMAKE_CURRENT_SOURCE_DIR}
          ${xs3RDPARTY_DIR}/utfcpp/source
          ${xs3RDPARTY_DIR}/http-parser
          ${xs3RDPARTY_DIR}/cpp-httplib
          ${MSYS2_CLANG64_DIR}/include
          ${xsOPENSSL_INCLUDE}
          ${xs3RDPARTY_DIR}/tinyxml2)

xs_set_target_output_dir(${PROJECT_NAME})
