project(MediaStreamClient)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

add_executable(${PROJECT_NAME} ${SOURCES})

add_dependencies(${PROJECT_NAME} MediaStreamComm)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${xsROOT_DIR}
          ${xsINCLUDE_DIR}
          ${CMAKE_CURRENT_SOURCE_DIR}
          ${CMAKE_CURRENT_SOURCE_DIR}/..
          ${MSYS2_CLANG64_DIR}/include
          ${xs3RDPARTY_DIR}/utfcpp/source
          ${xs3RDPARTY_DIR}/http-parser
          ${xs3RDPARTY_DIR}/cpp-httplib
          ${xsOPENSSL_INCLUDE}
          ${xs3RDPARTY_DIR}/tinyxml2)

target_link_directories(${PROJECT_NAME} PRIVATE ${xsLIBS_DIR})

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
            libfmt.a
            libsys.a
            libstl.a
            libzipcc.a
            libpthread.a
            libMediaStreamComm.a
            ${xsOUTPUT_DIR}/http_parser/libhttp_parser.a
            ${xsOUTPUT_DIR}/zlib/libzlibstatic.a
            ${xsOUTPUT_DIR}/tinyxml2/libtinyxml2.a
            ${xsOPENSSL_LIBRARY})

  #set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-mwindows"
  #                                                 WIN32_EXECUTABLE YES)

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

xs_set_target_output_dir(${PROJECT_NAME})
