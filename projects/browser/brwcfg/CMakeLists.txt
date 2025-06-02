project(brwcfg)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

gfn_find_ffmpeg(ffxINCLUDES ffxLIBS)

add_definitions(-DSHARED_IMPLEMENTATION)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wno-deprecated-literal-operator)
target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
          ${CMAKE_CURRENT_SOURCE_DIR}/..
          ${CMAKE_CURRENT_SOURCE_DIR}/../../chromium/include
          ${xsROOT_DIR}
          ${xsINCLUDE_DIR}
          ${xsBUILD_INSTALLED_INCLUDE_DIR}
          ${xsBUILD_INSTALLED_INCLUDE_DIR}/utf8cpp
          ${xsBUILD_INSTALLED_INCLUDE_DIR}/http-parser
          ${xs3RDPARTY_DIR}/cpp-httplib
          ${xsOPENSSL_INCLUDE}
          ${wxINCLUDES})
target_link_directories(${PROJECT_NAME} PRIVATE ${xsLIBS_DIR} ${xsLIBS_LIB_DIR}
                        ${xsBUILD_INSTALLED_LIB_DIR} ${ffxINCLUDES})
if(xsSYSTYPE_WINDOWS)
  target_link_libraries(
    ${PROJECT_NAME}
    ${MSYS2_CLANG64_DIR}/lib/libdl.a
    ${MSYS2_CLANG64_DIR}/lib/libc++.a
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
    libfmt.a
    libsys.a
    libstl.a
    libzipcc.a
    libpthread.a
    libzlibstatic.a
    libtinyxml2.a
    libuv.a
    ${ffxLIBS}
    ${xsOPENSSL_LIBRARY})
elseif(xsSYSTYPE_LINUX)
  target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/..
            ${CMAKE_CURRENT_SOURCE_DIR}/../../chromium/include
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
    libtinyxml2.a
    libuv.a
    ${xsOUTPUT_DIR}/base/sys/libsys.a
    ${xsOUTPUT_DIR}/base/stl/libstl.a
    ${xsOUTPUT_DIR}/base/base/libbase.a
    ${xsOUTPUT_DIR}/base/zipcc/libzipcc.a
    libpthread.a)
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

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND
    echo
    "Output file: ${xsOUTPUT_COMPONENTS_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}>
          ${xsOUTPUT_COMPONENTS_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>
  COMMENT "Printing output file path and copying file")
