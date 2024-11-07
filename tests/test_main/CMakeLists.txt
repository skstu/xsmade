project(test_main)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

add_definitions(-DCPPHTTPLIB_OPENSSL_SUPPORT)
add_definitions(-DUNICODE -D_UNICODE)
add_executable(${PROJECT_NAME} ${SOURCES})

if(MSVC)
  # add_compile_options(/wd4996 /wd4267)
  add_compile_options(/utf-8)
endif()

if(xsSYSTYPE_APPLE)
  target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${xsINCLUDE_DIR}
            ${xs3RDPARTY_DIR}/utfcpp/source/
            ${xs3RDPARTY_DIR}/cpp-httplib/
            /opt/homebrew/opt/openssl@3/include/
            /opt/homebrew/Cellar/fmt/11.0.2/include/
            /opt/homebrew/Cellar/libuv/1.49.2/include/)

  target_link_libraries(
    ${PROJECT_NAME}
    /opt/homebrew/opt/openssl@3/lib/libcrypto.a
    /opt/homebrew/opt/openssl@3/lib/libssl.a
    /opt/homebrew/Cellar/fmt/11.0.2/lib/libfmt.a
    /opt/homebrew/Cellar/libuv/1.49.2/lib/libuv.a)
elseif(xsSYSTYPE_WINDOWS)
  # target_link_options(${PROJECT_NAME} PRIVATE -Wl,--allow-multiple-definition)
  # set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS
  # "-Wl,--allow-multiple-definition")
  target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${xsINCLUDE_DIR}
            ${xs3RDPARTY_DIR}/utfcpp/source/
            ${xs3RDPARTY_DIR}/cpp-httplib/
            c:/msys64/clang64/include/
            c:/msys64/clang64/include/wx-3.0/
            c:/msys64/clang64/lib/wx/include/msw-unicode-static-3.0/)

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
    Oleacc.lib
    c:/msys64/clang64/lib/libssl.a
    c:/msys64/clang64/lib/libcrypto.a
    c:/msys64/clang64/lib/libfmt.a
    c:/msys64/clang64/lib/libuv.a
    c:/msys64/clang64/lib/libwx_baseu_net-3.0.a
    c:/msys64/clang64/lib/libwx_baseu_xml-3.0.a
    c:/msys64/clang64/lib/libwx_baseu-3.0.a
    c:/msys64/clang64/lib/libwx_mswu_adv-3.0.a
    c:/msys64/clang64/lib/libwx_mswu_aui-3.0.a
    c:/msys64/clang64/lib/libwx_mswu_core-3.0.a
    c:/msys64/clang64/lib/libwx_mswu_richtext-3.0.a
    c:/msys64/clang64/lib/libwx_mswu_stc-3.0.a
    c:/msys64/clang64/lib/libwx_mswu_webview-3.0.a
    c:/msys64/clang64/lib/libwx_mswu_xrc-3.0.a
    c:/msys64/clang64/lib/libwxexpat-3.0.a
    c:/msys64/clang64/lib/libwxjpeg-3.0.a
    c:/msys64/clang64/lib/libwxpng-3.0.a
    c:/msys64/clang64/lib/libwxzlib-3.0.a
    c:/msys64/clang64/lib/libwx_mswu_gl-3.0.a
    c:/msys64/clang64/lib/libwx_mswu_html-3.0.a
    c:/msys64/clang64/lib/libwx_mswu_media-3.0.a
    c:/msys64/clang64/lib/libwx_mswu_propgrid-3.0.a
    c:/msys64/clang64/lib/libwx_mswu_qa-3.0.a
    c:/msys64/clang64/lib/libwx_mswu_ribbon-3.0.a
    c:/msys64/clang64/lib/libwxregexu-3.0.a
    c:/msys64/clang64/lib/libwxscintilla-3.0.a
    c:/msys64/clang64/lib/libwxtiff-3.0.a)
endif()
