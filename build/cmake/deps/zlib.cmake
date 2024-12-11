set(ZLIB_PROJECT_NAME "zlib")

set(ZLIB_BUILD_EXAMPLES
    OFF
    CACHE BOOL "disabled zlib build examples." FORCE)
add_subdirectory(${xs3RDPARTY_DIR}/zlib/ ${ZLIB_PROJECT_NAME})
