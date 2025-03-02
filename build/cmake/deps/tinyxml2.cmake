set(TINYXML2_PROJECT_NAME "tinyxml2")
# set(CMAKE_INSTALL_PREFIX
# ${xsBUILD_INSTALLED_DIR}/${TINYXML2_PROJECT_NAME}/${CMAKE_BUILD_TYPE} CACHE
# STRING "Install path prefix, prepended onto install directories." FORCE)
add_subdirectory(${xs3RDPARTY_DIR}/tinyxml2/ ${TINYXML2_PROJECT_NAME})
