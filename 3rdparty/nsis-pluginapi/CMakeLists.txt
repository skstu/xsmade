project(nsis-pluginapi)

set(SOURCES pluginapi.c pluginapi.h nsis_tchar.h api.h)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} NSISPLUGINAPI_HDRS
                       OUTPUT_SOURCES)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

install(
  TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
  LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(FILES ${NSISPLUGINAPI_HDRS}
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}")
