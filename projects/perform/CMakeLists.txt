project(perform)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
          ${xsROOT_DIR}
          ${xsINCLUDE_DIR}
          ${xsBUILD_INSTALLED_INCLUDE_DIR}/utf8cpp
          ${xsBUILD_INSTALLED_INCLUDE_DIR}/http-parser
          ${xs3RDPARTY_DIR}/cpp-httplib
          ${xsOPENSSL_INCLUDE}
          ${MSYS2_CLANG64_DIR}/include
          ${xs3RDPARTY_DIR}/tinyxml2/
          ${xs3RDPARTY_DIR}/wxWidgets/include/)

target_link_directories(${PROJECT_NAME} PRIVATE ${xsLIBS_DIR} ${xsLIBS_LIB_DIR}
                        ${xsBUILD_INSTALLED_LIB_DIR})

if(WIN32)
  target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE ${MSYS2_CLANG64_DIR}/lib/libc++.a
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
            # Oleacc.lib
            libfmt.a
            libpthread.a
            libhttp_parser.a
            libzlibstatic.a
            libtinyxml2.a
            ${xsOUTPUT_DIR}/base/sys/libsys.a
            ${xsOUTPUT_DIR}/base/stl/libstl.a
            ${xsOUTPUT_DIR}/base/ssl/libssl.a
            ${xsOUTPUT_DIR}/base/zipcc/libzipcc.a
            ${xsOPENSSL_LIBRARY})

  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-mwindows"
                                                   WIN32_EXECUTABLE YES)
elseif(APPLE)
  target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${xsINCLUDE_DIR}
            ${xs3RDPARTY_DIR}/utfcpp/source/
            ${xs3RDPARTY_DIR}/http-parser/
            ${xs3RDPARTY_DIR}/cpp-httplib/
            ${xsOPENSSL_INCLUDE}
            ${wxINCLUDES}
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
    ${xsOUTPUT_DIR}/tinyxml2/libtinyxml2.a
    /opt/homebrew/Cellar/fmt/11.0.2/lib/libfmt.a
    /opt/homebrew/Cellar/libuv/1.49.2/lib/libuv.a
    /opt/homebrew/Cellar/zlib/1.3.1/lib/libz.a
    ${xsOPENSSL_LIBRARY})
endif()

#xs_set_target_output_dir(${PROJECT_NAME})
  add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND echo "Output file: ${xsBIN_DIR}/perform.exe"
    COMMAND
      ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}>
      # ${xsOUTPUT_PLUGINS_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>
      ${xsBIN_DIR}/perform.exe
    COMMENT "Printing output file path and copying file")
