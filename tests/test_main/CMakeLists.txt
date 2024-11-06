project(test_main)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

add_executable(${PROJECT_NAME} ${SOURCES})

if(MSVC)
  # add_compile_options(/wd4996 /wd4267)
  add_compile_options(/utf-8)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${xsINCLUDE_DIR})

if(WIN32)

elseif(UNIX)
target_link_libraries(${PROJECT_NAME} icuuc icui18n icuio icudata)
elseif(APPLE)

endif()