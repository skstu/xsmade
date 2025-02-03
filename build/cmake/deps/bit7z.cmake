set(BIT7Z_PROJECT_NAME "bit7z")

# set(ZLIB_BUILD_EXAMPLES OFF CACHE BOOL "disabled zlib build examples." FORCE)
add_subdirectory(${xs3RDPARTY_DIR}/bit7z/ ${BIT7Z_PROJECT_NAME})

# target_add_options(${BIT7Z_PROJECT_NAME} PRIVATE
#                    -Wno-cast-function-type-mismatch)
