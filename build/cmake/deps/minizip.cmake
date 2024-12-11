set(MINIZIP_PROJECT_NAME "minizip")

set(CMAKE_DEBUG_POSTFIX
    ""
    CACHE STRING "..." FORCE)
add_subdirectory(${xs3RDPARTY_DIR}/minizip/ ${MINIZIP_PROJECT_NAME})
