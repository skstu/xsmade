project(test_icucc)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_directories(${PROJECT_NAME} PRIVATE ${xsLIBS_DIR} ${xsLIBS_LIB_DIR}
                        ${xsBUILD_INSTALLED_LIB_DIR})

if(WIN32)
  target_include_directories(
    ${PROJECT_NAME} PRIVATE ${xsROOT_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
                            ${xsINCLUDE_DIR} ${xsBUILD_INSTALLED_INCLUDE_DIR})
  target_link_libraries(
    ${PROJECT_NAME}
    wldap32.lib
    libfmt.a
    libsys.a
    libstl.a
    ${MSYS2_CLANG64_DIR}/lib/libdl.a
    ${MSYS2_CLANG64_DIR}/lib/libc++.a
    ${MSYS2_CLANG64_DIR}/lib/libfmt.a)
elseif(APPLE)
  target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${xsINCLUDE_DIR}
            ${xs3RDPARTY_DIR}/utfcpp/source/
            ${xs3RDPARTY_DIR}/cpp-httplib/
            /opt/homebrew/opt/openssl@3/include/
            /opt/homebrew/Cellar/fmt/11.0.2/include/
            /opt/homebrew/Cellar/libuv/1.49.2/include/)

  # target_link_directories(${PROJECT_NAME} PRIVATE
  # ${xsOUTPUT_DIR}/wxWidgets/lib/)

  target_link_libraries(
    ${PROJECT_NAME}
    "-framework CoreFoundation"
    "-framework Cocoa"
    "-liconv"
    /opt/homebrew/opt/openssl@3/lib/libcrypto.a
    /opt/homebrew/opt/openssl@3/lib/libssl.a
    /opt/homebrew/Cellar/fmt/11.0.2/lib/libfmt.a
    /opt/homebrew/Cellar/libuv/1.49.2/lib/libuv.a)
endif()

xs_set_target_output_dir(${PROJECT_NAME})
