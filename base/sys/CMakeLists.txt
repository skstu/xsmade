cmake_minimum_required(VERSION 3.5)

project(sys)

# gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
# set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

set(common_srcs_ "${CMAKE_CURRENT_SOURCE_DIR}/sys.h"
                 "${CMAKE_CURRENT_SOURCE_DIR}/sys.cc")

if(WIN32)
  set(srcs_ "${CMAKE_CURRENT_SOURCE_DIR}/win/net.cc")
elseif(APPLE)
  set(srcs_ "${CMAKE_CURRENT_SOURCE_DIR}/apple/net.cc")
endif()

set(SOURCES ${common_srcs_} ${srcs_})

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${xsINCLUDE_DIR}
                                                   ${CMAKE_CURRENT_SOURCE_DIR})

xs_set_target_output_dir(${PROJECT_NAME})
