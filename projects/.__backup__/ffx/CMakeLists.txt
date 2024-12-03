project(ffx)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

add_definitions(-DBUILDING_XS_SHARED)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${xsINCLUDE_DIR} ${xs3RDPARTY_DIR}/utfcpp/source/
          ${xsOPENSSL_INCLUDE} ${xsPROJECTS_DIR}/ffx/
          ${xsBUILD_INSTALLED_DIR}/include/)
target_link_directories(${PROJECT_NAME} PRIVATE ${xsLIBS_DIR}
                        ${xsBUILD_INSTALLED_DIR}/lib/)

if(WIN32)
  target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE ${MSYS2_CLANG64_DIR}/lib/libc++.a
            ${MSYS2_CLANG64_DIR}/lib/libiconv.a
            ${MSYS2_CLANG64_DIR}/lib/liblzma.a
            ${MSYS2_CLANG64_DIR}/lib/libbz2.a
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
            ######################ffmpeg
            Msimg32.lib
            Secur32.lib
            Bcrypt.lib
            Mfuuid.lib
            Strmiids.lib
            Mfplat.lib
            # Oleacc.lib
            # ##################################################################
            Vfw32.lib
            libavcodec.a
            libavdevice.a
            libavfilter.a
            libavformat.a
            libavutil.a
            libpostproc.a
            libswresample.a
            libswscale.a
            libx264.a
            libx265.a
            # ##################################################################
            libfmt.a
            libstl.a
            libsys.a
            libzipcc.a
            libpthread.a
            ${xsOUTPUT_DIR}/zlib/libzlibstatic.a
            ${xsOPENSSL_LIBRARY})

  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-mwindows"
                                                   WIN32_EXECUTABLE YES)
  add_dependencies(${PROJECT_NAME} sys stl zipcc)
elseif(APPLE)
  target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${xsINCLUDE_DIR} ${xs3RDPARTY_DIR}/utfcpp/source/
            ${xs3RDPARTY_DIR}/http-parser/ ${xs3RDPARTY_DIR}/cpp-httplib/
            ${xsOPENSSL_INCLUDE} ${wxINCLUDES})

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
    /opt/homebrew/Cellar/fmt/11.0.2/lib/libfmt.a
    /opt/homebrew/Cellar/libuv/1.49.2/lib/libuv.a
    /opt/homebrew/Cellar/zlib/1.3.1/lib/libz.a
    ${xsOPENSSL_LIBRARY})
endif()

xs_set_target_output_dir(${PROJECT_NAME})

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PUBLISH_LIBRARY})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PUBLISH_RUNTIME})
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PUBLISH_ARCHIVE})
#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)       #设置可执行文件的输出目录
#SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../lib)           #设置库文件的输出目录
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin)   
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../bin)
