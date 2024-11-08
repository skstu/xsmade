project(services)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

add_executable(${PROJECT_NAME} ${SOURCES})

gfn_find_wxwidgets(wxINCLUDES wxLIBS)
message(STATUS ${wxLIBS})
target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${xsINCLUDE_DIR} ${xs3RDPARTY_DIR}/utfcpp/source/
          ${xs3RDPARTY_DIR}/http-parser/ ${xs3RDPARTY_DIR}/cpp-httplib/
          ${xsOPENSSL_INCLUDE} ${wxINCLUDES})

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
  UxTheme.lib
  Comctl32.lib
  Shlwapi.lib
  Version.lib
  Rpcrt4.lib
  Oleacc.lib
  Gdiplus.lib
  Msimg32.lib
  ${xsOPENSSL_LIBRARY}
  ${wxLIBS})

  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-mwindows"
                                                   WIN32_EXECUTABLE YES)
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
    "-liconv"
    /opt/homebrew/Cellar/fmt/11.0.2/lib/libfmt.a
    /opt/homebrew/Cellar/libuv/1.49.2/lib/libuv.a
    ${xsOPENSSL_LIBRARY}
  ${wxLIBS})
endif()

xs_set_common_target_properties(${PROJECT_NAME})
