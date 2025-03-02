project(test_wxui)
gfn_find_wxwidgets(wxINCLUDES wxLIBS wxMSWRC)
gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S} ${wxMSWRC})
add_executable(${PROJECT_NAME} ${SOURCES})
# add_dependencies(${PROJECT_NAME} stl sys)

if(WIN32)
  target_include_directories(
    ${PROJECT_NAME} PRIVATE ${xsROOT_DIR} ${xsINCLUDE_DIR}
                            ${xs3RDPARTY_DIR}/utfcpp/source ${wxINCLUDES})

  target_link_directories(${PROJECT_NAME} PRIVATE
                          ${xsLIBS_DIR}/${CMAKE_BUILD_TYPE}/lib/)

  gfn_message_info("${xsLIBS_DIR}/${CMAKE_BUILD_TYPE}/lib/")
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
    libsys.a
    libstl.a
    ${MSYS2_CLANG64_DIR}/lib/libdl.a
    ${MSYS2_CLANG64_DIR}/lib/libc++.a
    ${MSYS2_CLANG64_DIR}/lib/libssl.a
    ${MSYS2_CLANG64_DIR}/lib/libcrypto.a
    ${MSYS2_CLANG64_DIR}/lib/libfmt.a
    ${MSYS2_CLANG64_DIR}/lib/libuv.a)

  # add_dependencies(${PROJECT_NAME} sys stl)
elseif(APPLE)
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

xs_set_target_output_dir(${PROJECT_NAME})
# target_compile_definitions(${PROJECT_NAME} PRIVATE wxUSE_GUI=0 wxUSE_BASE=1)
