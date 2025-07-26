project(test_curlcc)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_directories(${PROJECT_NAME} PRIVATE ${xsLIBS_LIB_DIR}
                        ${xsBUILD_INSTALLED_LIB_DIR})
if(WIN32)
  target_include_directories(
    ${PROJECT_NAME} PRIVATE ${xsINCLUDE_DIR} ${xsSOURCE_DIR}
                            ${xs3RDPARTY_DIR}/utfcpp/source/)
  target_link_libraries(
    ${PROJECT_NAME}
    libz.a
    libfmt.a
    libpthread.a
    libhttp_parser.a
    ${xsOUTPUT_DIR}/base/sys/libsys.a
    ${xsOUTPUT_DIR}/base/stl/libstl.a
    ${xsOUTPUT_DIR}/base/base/libbase.a
    ${xsOUTPUT_DIR}/base/zipcc/libzipcc.a
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

# xs_set_target_output_dir(${PROJECT_NAME})
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND echo
          "Output file: ${xsBIN_TESTS_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}>
          ${xsBIN_TESTS_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>
  COMMENT "Printing output file path and copying file")
