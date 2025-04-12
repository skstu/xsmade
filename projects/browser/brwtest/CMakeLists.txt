project(brwtest)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

add_definitions(-DSHARED_IMPLEMENTATION)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_compile_options(
  ${PROJECT_NAME}
  PRIVATE # Debug 模式下的编译选项
          $<$<CONFIG:Debug>:
          -g
          -O0
          -DDEBUG
          -D_DEBUG
          >
          # Release 模式下的编译选项
          $<$<CONFIG:Release>:
          -O1
          -DNDEBUG
          -fPIC
          -pthread
          -march=x86-64
          -mtune=generic
          -g0
          -fvisibility=hidden
          -std=c++17
          >)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
          ${CMAKE_CURRENT_SOURCE_DIR}/..
          ${xsROOT_DIR}
          ${xsINCLUDE_DIR}
          ${xsBUILD_INSTALLED_INCLUDE_DIR}
          ${xsBUILD_INSTALLED_INCLUDE_DIR}/utf8cpp
          ${xsOPENSSL_INCLUDE}
          ${wxINCLUDES})

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND
    echo
    "Output file: ${xsOUTPUT_COMPONENTS_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}>
          ${xsOUTPUT_COMPONENTS_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>
  COMMENT "Printing output file path and copying file")
