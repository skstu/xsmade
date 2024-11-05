project(test_main)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

add_executable(${PROJECT_NAME} ${SOURCES})



if(MSVC)
  # add_compile_options(/wd4996 /wd4267)
  add_compile_options(/utf-8)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${xsINCLUDE_DIR})

target_link_libraries(
  ${PROJECT_NAME} 
  icuuc 
  icui18n 
  icuio 
  icudata
)
#[[
target_link_libraries(
  ${PROJECT_NAME}
  ${SOLUTION_ROOT_DIR}/libs/${CMAKE_VS_PLATFORM_NAME}/${VS_CONFIGURATION_TYPE}/stl.lib
  ${SOLUTION_ROOT_DIR}/libs/${CMAKE_VS_PLATFORM_NAME}/${VS_CONFIGURATION_TYPE}/win32.lib
  ${SOLUTION_ROOT_DIR}/libs/${CMAKE_VS_PLATFORM_NAME}/${VS_CONFIGURATION_TYPE}/fmt.lib
  ${SOLUTION_ROOT_DIR}/libs/${CMAKE_VS_PLATFORM_NAME}/${VS_CONFIGURATION_TYPE}/sqlite3.lib
  ${SOLUTION_ROOT_DIR}/libs/${CMAKE_VS_PLATFORM_NAME}/${VS_CONFIGURATION_TYPE}/zipcc.lib
  ${SOLUTION_ROOT_DIR}/libs/${CMAKE_VS_PLATFORM_NAME}/${VS_CONFIGURATION_TYPE}/minizip.lib
  ${SOLUTION_ROOT_DIR}/libs/${CMAKE_VS_PLATFORM_NAME}/${VS_CONFIGURATION_TYPE}/detours.lib
  ${SOLUTION_ROOT_DIR}/libs/${CMAKE_VS_PLATFORM_NAME}/${VS_CONFIGURATION_TYPE}/libchromium.lib
)

if(MSVC)
  # MSVC_LINK_FLAGS_SET_CONSOLE(${PROJECT_NAME})
  if(ENABLE_MSVC_CRT_MT)
    msvc_crt_set(${PROJECT_NAME} "/MT")
  endif(ENABLE_MSVC_CRT_MT)
  msvc_use_pch(${PROJECT_NAME} ${entry}/stdafx.h ${entry}/stdafx.cc)
endif()
]]
