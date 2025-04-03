set(FMT_PROJECT_NAME "fmt")
# set(BUILD_TESTING OFF CACHE BOOL "" FORCE) set(LIBUV_BUILD_SHARED OFF CACHE
# BOOL "" FORCE)
set(FMT_DEBUG_POSTFIX
    ""
    CACHE STRING "..." FORCE)
add_subdirectory(${xs3RDPARTY_DIR}/fmt/ ${FMT_PROJECT_NAME})

set_target_properties(${FMT_PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE
                                                     TRUE)
