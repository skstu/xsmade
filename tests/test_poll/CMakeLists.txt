project(test_poll)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
          ${CMAKE_CURRENT_SOURCE_DIR}/..
          ${CMAKE_CURRENT_SOURCE_DIR}/../..
          ${xsROOT_DIR}
          ${xsINCLUDE_DIR}
          ${xsBUILD_INSTALLED_INCLUDE_DIR}
          ${xsBUILD_INSTALLED_INCLUDE_DIR}/utf8cpp
          ${xsOPENSSL_INCLUDE})
target_link_directories(${PROJECT_NAME} PRIVATE ${xsLIBS_DIR} ${xsLIBS_LIB_DIR}
                        ${xsBUILD_INSTALLED_LIB_DIR})

if(xsSYSTYPE_WINDOWS)
  target_link_libraries(
    ${PROJECT_NAME}
    ${MSYS2_CLANG64_DIR}/lib/libc++.a
    ${MSYS2_CLANG64_DIR}/lib/libdl.a
    wldap32.lib
    winmm.lib
    Crypt32.lib
    Normaliz.lib
    ws2_32.lib
    IPHLPAPI.lib
    Userenv.lib
    Dbghelp.lib
    Rpcrt4.lib
    Comctl32.lib
    gdiplus.lib
    UxTheme.lib
    version.lib
    Shlwapi.lib
    Msimg32.lib
    uuid.lib
    Oleacc.lib
    libfmt.a
    libsys.a
    libstl.a
    libzipcc.a
    libpthread.a
    libzlibstatic.a
    ${wxLIBS}
    ${xsOPENSSL_LIBRARY})
elseif(xsSYSTYPE_APPLE)
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
elseif(xsSYSTYPE_LINUX)
  target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/..
            ${xsROOT_DIR}
            ${xsINCLUDE_DIR}
            ${xsBUILD_INSTALLED_INCLUDE_DIR}
            ${xsBUILD_INSTALLED_INCLUDE_DIR}/utf8cpp
            ${xsOPENSSL_INCLUDE})
  target_link_directories(${PROJECT_NAME} PRIVATE ${xsLIBS_LIB_DIR}
                          ${xsBUILD_INSTALLED_LIB_DIR})

  target_link_libraries(
    ${PROJECT_NAME}
    fmt.a
    libpthread.a
    libz.a
    ${xsOUTPUT_DIR}/base/sys/libsys.a
    ${xsOUTPUT_DIR}/base/stl/libstl.a
    ${xsOUTPUT_DIR}/base/base/libbase.a
    ${xsOUTPUT_DIR}/base/zipcc/libzipcc.a)
endif()
# xs_set_common_target_properties(${PROJECT_NAME})
# xs_set_target_output_dir(${PROJECT_NAME})

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND echo
          "Output file: ${xsBIN_TESTS_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}>
          ${xsBIN_TESTS_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>
  COMMENT "Printing output file path and copying file")
