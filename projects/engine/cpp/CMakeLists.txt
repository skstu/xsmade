project(cpp)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

add_definitions(-DSHARED_IMPLEMENTATION)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

add_dependencies(${PROJECT_NAME} sys stl zipcc)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${xsINCLUDE_DIR}
          ${xs3RDPARTY_DIR}/utfcpp/source ${xsOPENSSL_INCLUDE}
          ${MSYS2_CLANG64_DIR}/include)

target_link_directories(${PROJECT_NAME} PRIVATE ${xsLIBS_DIR} ${xsLIBS_LIB_DIR}
                        ${xsBUILD_INSTALLED_LIB_DIR})

if(WIN32)
  target_link_libraries(
    ${PROJECT_NAME}
    ${MSYS2_CLANG64_DIR}/lib/libc++.a
    libfmt.a
    libsys.a
    libstl.a
    libzipcc.a
    libpthread.a
    libzlibstatic.a
    ${xsOPENSSL_LIBRARY})

  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-mwindows"
                                                   WIN32_EXECUTABLE YES)
  set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE
                                                   TRUE)
  target_compile_definitions(${PROJECT_NAME} PRIVATE wxUSE_GUI=1 wxUSE_BASE=0)

  add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}>
      C:/Users/k34ub/AppData/Roaming/MarsProjects/plugins/${PROJECT_NAME}.dll)
elseif(APPLE)
  target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${xsINCLUDE_DIR} ${xs3RDPARTY_DIR}/utfcpp/source/
            ${xsOPENSSL_INCLUDE} /opt/homebrew/Cellar/fmt/11.0.2/include/)
  target_link_directories(${PROJECT_NAME} PRIVATE ${xsLIBS_DIR})
  target_link_libraries(
    ${PROJECT_NAME}
    "-framework CoreFoundation"
    "-framework Cocoa"
    "-framework CoreServices"
    # "-lCarbon.framework"
    "-framework ApplicationServices"
    "-framework Carbon"
    "-framework CoreGraphics"
    "-framework IOKit"
    "-framework QuartzCore"
    "-liconv"
    libsys.a
    libstl.a
    libzipcc.a
    libpthread.a
    /opt/homebrew/Cellar/fmt/11.0.2/lib/libfmt.a
    /opt/homebrew/Cellar/libuv/1.49.2/lib/libuv.a
    /opt/homebrew/Cellar/zlib/1.3.1/lib/libz.a
    ${xsOPENSSL_LIBRARY})
endif()
# xs_set_common_target_properties(${PROJECT_NAME})
# xs_set_target_output_dir(${PROJECT_NAME})
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND
    echo
    "Output file: ${xsOUTPUT_ENGINE_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}>
          ${xsOUTPUT_ENGINE_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>
  COMMENT "Printing output file path and copying file")
