project(test_settings)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S}
            ${xs3RDPARTY_DIR}/wxWidgets/include/wx/msw/wx.rc)

add_executable(${PROJECT_NAME} ${SOURCES})

if(xsSYSTYPE_WINDOWS)
  target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${xsROOT_DIR} ${xsINCLUDE_DIR} ${xs3RDPARTY_DIR}/utfcpp/source/
            ${xs3RDPARTY_DIR}/wxWidgets/include/
            ${xsROOT_DIR}/projects/chromium/include/)

  target_link_directories(${PROJECT_NAME} PRIVATE ${xsLIBS_DIR})

  target_link_libraries(
    ${PROJECT_NAME}
    wldap32.lib
    winmm.lib
    Crypt32.lib
    Normaliz.lib
    ws2_32.lib
    IPHLPAPI.lib
    Userenv.lib
    Dbghelp.lib
    UxTheme.lib
    Comctl32.lib
    Shlwapi.lib
    Version.lib
    Rpcrt4.lib
    Gdiplus.lib
    Msimg32.lib
    ${xsOUTPUT_DIR}/base/sys/libsys.a
    ${xsOUTPUT_DIR}/base/stl/libstl.a
    ${xsOUTPUT_DIR}/base/zipcc/libzipcc.a
    ${MSYS2_CLANG64_DIR}/lib/libdl.a
    ${MSYS2_CLANG64_DIR}/lib/libc++.a
    ${MSYS2_CLANG64_DIR}/lib/libssl.a
    ${MSYS2_CLANG64_DIR}/lib/libcrypto.a
    ${MSYS2_CLANG64_DIR}/lib/libfmt.a
    ${MSYS2_CLANG64_DIR}/lib/libuv.a)

  add_dependencies(${PROJECT_NAME} sys stl)
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
  target_link_directories(${PROJECT_NAME} PRIVATE ${xsLIBS_DIR}
                          ${xsLIBS_LIB_DIR} ${xsBUILD_INSTALLED_LIB_DIR})

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
    libsys.a
    libstl.a
    libzipcc.a
    libpthread.a
    libz.a)
elseif(xsSYSTYPE_APPLE)
  target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${xsROOT_DIR}
            ${xsINCLUDE_DIR}
            ${xs3RDPARTY_DIR}/utfcpp/source/
            ${xs3RDPARTY_DIR}/cpp-httplib/
            /opt/homebrew/opt/openssl@3/include/
            /opt/homebrew/Cellar/fmt/11.0.2/include/
            /opt/homebrew/Cellar/libuv/1.49.2/include/)

  # target_link_directories(${PROJECT_NAME} PRIVATE
  # ${xsOUTPUT_DIR}/wxWidgets/lib/)
  target_link_directories(${PROJECT_NAME} PRIVATE ${xsLIBS_DIR})

  target_link_libraries(
    ${PROJECT_NAME}
    "-framework CoreFoundation"
    "-framework Cocoa"
    "-liconv"
    libsys.a
    libstl.a
    /opt/homebrew/opt/openssl@3/lib/libcrypto.a
    /opt/homebrew/opt/openssl@3/lib/libssl.a
    /opt/homebrew/Cellar/fmt/11.0.2/lib/libfmt.a
    /opt/homebrew/Cellar/libuv/1.49.2/lib/libuv.a)
endif()

# xs_set_target_output_dir(${PROJECT_NAME})
# target_compile_definitions(${PROJECT_NAME} PRIVATE wxUSE_GUI=0 wxUSE_BASE=1)
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND echo "Output file: ${xsBIN_DIR}/${PROJECT_NAME}.exe"
  COMMAND
    ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}>
    # ${xsOUTPUT_PLUGINS_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>
    ${xsBIN_DIR}/${PROJECT_NAME}.exe
  COMMENT "Printing output file path and copying file")
