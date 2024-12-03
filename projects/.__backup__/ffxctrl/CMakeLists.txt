project(ffxctrl)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})
# "${MSYS2_CLANG64_DIR}/include/wx-3.2/wx/msw/wx.rc")

add_definitions(-DSHARED_IMPLEMENTATION)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
# "${xs3RDPARTY_DIR}/wxWidgets/include/wx/msw/wx.rc"

gfn_find_wxwidgets(wxINCLUDES wxLIBS)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${xsINCLUDE_DIR} ${xs3RDPARTY_DIR}/utfcpp/source/
          ${xs3RDPARTY_DIR}/http-parser/ ${xs3RDPARTY_DIR}/cpp-httplib/
          ${xsOPENSSL_INCLUDE} ${wxINCLUDES})
target_link_directories(${PROJECT_NAME} PRIVATE ${xsLIBS_DIR})
if(WIN32)
  target_link_libraries(
    ${PROJECT_NAME}
    ${MSYS2_CLANG64_DIR}/lib/libc++.a
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
    libfmt.a
    libsys.a
    libstl.a
    libzipcc.a
    libpthread.a
    uuid.lib
    Oleacc.lib
    ${xsOUTPUT_DIR}/http_parser/libhttp_parser.a
    ${xsOUTPUT_DIR}/zlib/libzlibstatic.a
    ${xsOPENSSL_LIBRARY}
    ${wxLIBS})

  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-mwindows"
                                                   WIN32_EXECUTABLE YES)
  set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE
                                                   TRUE)
  target_compile_definitions(${PROJECT_NAME} PRIVATE wxUSE_GUI=1 wxUSE_BASE=0)
elseif(APPLE)
  target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${xsINCLUDE_DIR} ${xs3RDPARTY_DIR}/utfcpp/source/
            ${xs3RDPARTY_DIR}/http-parser/ ${xs3RDPARTY_DIR}/cpp-httplib/
            ${xsOPENSSL_INCLUDE} ${wxINCLUDES})

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
    /opt/homebrew/Cellar/fmt/11.0.2/lib/libfmt.a
    /opt/homebrew/Cellar/libuv/1.49.2/lib/libuv.a
    /opt/homebrew/Cellar/zlib/1.3.1/lib/libz.a
    ${xsOPENSSL_LIBRARY}
    ${wxLIBS})
endif()
# xs_set_common_target_properties(${PROJECT_NAME})
xs_set_target_output_dir(${PROJECT_NAME})
