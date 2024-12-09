project(brwcfg)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

add_definitions(-DSHARED_IMPLEMENTATION)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

add_dependencies(${PROJECT_NAME} sys stl)

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

target_include_directories(
  ${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${xsINCLUDE_DIR}
                          ${xs3RDPARTY_DIR}/utfcpp/source/)

target_link_directories(${PROJECT_NAME} PRIVATE ${xsLIBS_DIR})

if(WIN32)
  target_link_libraries(
    ${PROJECT_NAME}
    ${MSYS2_CLANG64_DIR}/lib/libc++.a
    libfmt.a
    libsys.a
    libstl.a
    libpthread.a
    ${MSYS2_CLANG64_DIR}/lib/libz.a
    ${MSYS2_CLANG64_DIR}/lib/libiconv.a
    ${xsOUTPUT_DIR}/zlib/libzlibstatic.a)

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
            ${xsOPENSSL_INCLUDE} ${wxINCLUDES}
            /opt/homebrew/Cellar/fmt/11.0.2/include/)
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
    ${xsOPENSSL_LIBRARY}
    ${wxLIBS})
endif()
# xs_set_common_target_properties(${PROJECT_NAME})
xs_set_target_output_dir(${PROJECT_NAME})

set(EXTNAME "dll")
if(WIN32)
  set(EXTNAME "dll")
elseif(APPLE)
  set(EXTNAME "dylib")
else()
  set(EXTNAME "so")
endif()

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}>
          ${xsBIN_DIR}/plugins/${PROJECT_NAME}.${EXTNAME})
