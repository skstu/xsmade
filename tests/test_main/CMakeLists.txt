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

if(APPLE)
  target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
      ${xsINCLUDE_DIR}
      ${xs3RDPARTY_DIR}/utfcpp/source/
      ${xs3RDPARTY_DIR}/cpp-httplib/
      /opt/homebrew/opt/openssl@3/include/
      /opt/homebrew/Cellar/fmt/11.0.2/include/
      /opt/homebrew/Cellar/libuv/1.49.2/include/)

 # target_link_directories(${PROJECT_NAME} PRIVATE
  #                        ${xsOUTPUT_DIR}/wxWidgets/lib/)


  target_link_libraries(
    ${PROJECT_NAME}
    "-framework CoreFoundation"
    "-framework Cocoa"
    "-liconv"
    /opt/homebrew/opt/openssl@3/lib/libcrypto.a
    /opt/homebrew/opt/openssl@3/lib/libssl.a
    /opt/homebrew/Cellar/fmt/11.0.2/lib/libfmt.a
    /opt/homebrew/Cellar/libuv/1.49.2/lib/libuv.a)
elseif(WIN32)
  # target_link_options(${PROJECT_NAME} PRIVATE -Wl,--allow-multiple-definition)
  # set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS
  # "-Wl,--allow-multiple-definition")
  target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${xsINCLUDE_DIR}
            ${xs3RDPARTY_DIR}/utfcpp/source/
            ${xs3RDPARTY_DIR}/cpp-httplib/
            c:/msys64/clang64/include/
  )

  #target_link_directories(${PROJECT_NAME} PRIVATE
  #                        ${xsOUTPUT_DIR}/wxWidgets/lib/)
  
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
    Gdiplus.lib
    Msimg32.lib
    c:/msys64/clang64/lib/libc++.a
    c:/msys64/clang64/lib/libssl.a
    c:/msys64/clang64/lib/libcrypto.a
    c:/msys64/clang64/lib/libfmt.a
    c:/msys64/clang64/lib/libuv.a
    ${WX_LIBS})
endif()

#target_compile_definitions(${PROJECT_NAME} PRIVATE wxUSE_GUI=0 wxUSE_BASE=1)
