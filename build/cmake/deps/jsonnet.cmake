set(JSONNET_PROJECT_NAME "jsonnet")

set(BUILD_TESTS
    OFF
    CACHE BOOL "" FORCE)

add_subdirectory(${xs3RDPARTY_DIR}/jsonnet/ ${JSONNET_PROJECT_NAME})
