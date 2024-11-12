cmake_minimum_required(VERSION 3.5)

project(stl)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${xsINCLUDE_DIR}
                                                   ${CMAKE_CURRENT_SOURCE_DIR})

xs_set_target_output_dir(${PROJECT_NAME})
