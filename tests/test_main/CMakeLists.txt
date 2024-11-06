project(test_main)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

add_definitions(-DCPPHTTPLIB_OPENSSL_SUPPORT)
add_executable(${PROJECT_NAME} ${SOURCES})

if(MSVC)
  # add_compile_options(/wd4996 /wd4267)
  add_compile_options(/utf-8)
endif()

if(xsSYSTYPE_APPLE)
  target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${xsINCLUDE_DIR} ${xs3RDPARTY_DIR}/utfcpp/source/
            ${xs3RDPARTY_DIR}/cpp-httplib/ /opt/homebrew/opt/openssl@3/include/ /opt/homebrew/Cellar/fmt/11.0.2/include/)

  target_link_libraries(
    ${PROJECT_NAME} /opt/homebrew/opt/openssl@3/lib/libcrypto.a
    /opt/homebrew/opt/openssl@3/lib/libssl.a
    /opt/homebrew/Cellar/fmt/11.0.2/lib/libfmt.a)
elseif(xsSYSTYPE_WINDOWS)
  target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${xsINCLUDE_DIR} ${xs3RDPARTY_DIR}/utfcpp/source/
            ${xs3RDPARTY_DIR}/cpp-httplib/ c:/msys64/clang64/include/)

  target_link_libraries(
    ${PROJECT_NAME}
    wldap32.lib
    winmm.lib
    Crypt32.lib
    Normaliz.lib
    ws2_32.lib
    c:/msys64/clang64/lib/libssl.a
    c:/msys64/clang64/lib/libcrypto.a
    c:/msys64/clang64/lib/libfmt.a)
endif()
