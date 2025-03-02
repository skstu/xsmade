#############################################################################
# Name:        build/cmake/main.cmake
# Purpose:     Main CMake file
# Author:      Martell
# Created:     2024-11-03
# Copyright:   (c) 2024 skstu development team
# Licence:     skstu licence
#############################################################################

# INPUT_TOOLCHAIN_NAME => 'gcc' or 'clang' or 'msvc' or (''==default)
macro(GFN_TOOLCHAIN_SET INPUT_TOOLCHAIN_NAME)
  if("${INPUT_TOOLCHAIN_NAME}" STREQUAL "")
    set(INPUT_TOOLCHAIN_NAME "gcc")
  else()
    string(TOLOWER ${INPUT_TOOLCHAIN_NAME} ${INPUT_TOOLCHAIN_NAME})
  endif()
  
  set(CMAKE_CXX_STANDARD 17)

  if("${INPUT_TOOLCHAIN_NAME}" STREQUAL "clang")
    set(CMAKE_C_COMPILER "clang")
    set(CMAKE_CXX_COMPILER "clang++")
    
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -v -std=c99 -Wall -Wno-unused-function")
    set(CMAKE_C_FLAGS_DEBUG "-g")
    set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")
    set(CMAKE_C_FLAGS_RELEASE "-O4 -DNDEBUG")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")
    
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -stdlib=libc++ -Wall -Wno-unused-function")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
    
    set (CMAKE_AR "llvm-ar")
    set (CMAKE_LINKER "lld")
    set(CMAKE_NM "llvm-nm")
    set(CMAKE_OBJDUMP "llvm-objdump")
    set(CMAKE_RANLIB "llvm-ranlib")
  elseif("${INPUT_TOOLCHAIN_NAME}" STREQUAL "gcc")
    set(CMAKE_C_COMPILER "gcc")
    set(CMAKE_CXX_COMPILER "g++")
    
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -v -std=c99 -Wall -Wno-unused-function")
    set(CMAKE_C_FLAGS_DEBUG "-g")
    set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")
    set(CMAKE_C_FLAGS_RELEASE "-O4 -DNDEBUG")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")
    
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -stdlib=libc++ -Wall -Wno-unused-function")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
    
    set (CMAKE_AR "ar")
    set (CMAKE_LINKER "ld")
    set(CMAKE_NM "nm")
    set(CMAKE_OBJDUMP "objdump")
    set(CMAKE_RANLIB "ranlib")
  elseif("${INPUT_TOOLCHAIN_NAME}" STREQUAL "msvc")

  endif()
endmacro(GFN_TOOLCHAIN_SET)

macro(GFN_GET_TARGET_PROJECT_FOLDER_NAME INPUT_FULLPATH OUTPUT_PROJECT_FOLDER_NAME)
# 获取父目录的路径
get_filename_component(temp_dir_name ${INPUT_FULLPATH} DIRECTORY)
#message(STATUS "Directory: ${temp_dir_name}")
# 获取从 devkit_last 开始的相对路径
get_filename_component(base_path ${temp_dir_name} DIRECTORY)
#message(STATUS "Base Path: ${base_path}")
# 最终想要的基准路径是 devkit_last 目录
set(root_path "C:/Users/k34ub/source/skstu/devkit_last")
# 计算相对于 root_path 的相对路径
file(RELATIVE_PATH ${OUTPUT_PROJECT_FOLDER_NAME} ${root_path} ${temp_dir_name})
#message(STATUS "Relative Path: ${final_path}")
endmacro(GFN_GET_TARGET_PROJECT_FOLDER_NAME)

macro(GFN_GET_TARGET_PROJECT_RELATIVE_PATHNAME INPUT_FULLPATH OUTPUT_PROJECT_PATHNAME)
get_filename_component(temp_dir_name ${INPUT_FULLPATH} DIRECTORY)
get_filename_component(base_path ${temp_dir_name} DIRECTORY)
get_filename_component(base_path ${base_path} DIRECTORY)
file(RELATIVE_PATH ${OUTPUT_PROJECT_PATHNAME} ${base_path} ${temp_dir_name})
endmacro(GFN_GET_TARGET_PROJECT_RELATIVE_PATHNAME)

macro(GFN_GET_TARGET_PROJECT_RELATIVE_NAME INPUT_FULLPATH OUTPUT_PROJECT_PATHNAME)
get_filename_component(${OUTPUT_PROJECT_PATHNAME} ${INPUT_FULLPATH} NAME)
endmacro(GFN_GET_TARGET_PROJECT_RELATIVE_NAME)

macro(GFN_GET_DIRECTORY_PREV_NAME INPUT_FULLPATH OUTPUT_DIRECTORY_NAME)
get_filename_component(temp_dir_name ${INPUT_FULLPATH} DIRECTORY)
get_filename_component(${OUTPUT_DIRECTORY_NAME} ${temp_dir_name} NAME)
endmacro(GFN_GET_DIRECTORY_PREV_NAME)

macro(GFN_ENV_INIT)
  if(WIN32)
    set(CMAKE_SYSTEM_NAME "Windows")
  elseif(UNIX)
    set(CMAKE_SYSTEM_NAME "Linux")
  else()
    set(CMAKE_SYSTEM_NAME "Unknown System")
  endif()

  if(NOT("${CMAKE_SYSTEM_NAME}" STREQUAL ""))
    message(STATUS "Current system name '${CMAKE_SYSTEM_NAME}'.")
  endif()

  add_definitions(-DUNICODE -D_UNICODE)
  set(CMAKE_CONFIGURATION_TYPES "Debug;Release;" CACHE STRING "info" FORCE)

  GFN_TOOLCHAIN_SET("gcc")
endmacro(GFN_ENV_INIT)

macro(GFN_ENV_UNINIT)
  
endmacro(GFN_ENV_UNINIT)


macro(GFN_RUNTIME_SET)
 if(WIN32)
  if(MSVC)
   option(COMPILE_ENABLE_RUNTIME_RT "If MSVC and set /MT." ON)
   if(COMPILE_ENABLE_RUNTIME_RT)
    add_compile_options(
     $<$<CONFIG:>:/MT>
     $<$<CONFIG:Debug>:/MTd>
     $<$<CONFIG:Release>:/MT>)
   else()
    add_compile_options(
     $<$<CONFIG:>:/MD>
     $<$<CONFIG:Debug>:/MDd>
     $<$<CONFIG:Release>:/MD>)
   endif()
  endif(MSVC)
 elseif(UNIX)


 endif()
endmacro()


macro(GFN_BUILD_TYPE_SET)
 if("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE "Release")
  if(CMAKE_CXX_FLAGS MATCHES "-g" OR CMAKE_C_FLAGS MATCHES "-g")
   set(CMAKE_BUILD_TYPE "Debug")
  endif()
 endif()
endmacro(GFN_BUILD_TYPE_SET)

macro(GFN_PLATFORM_GET INOUT_PLATFORM)
 set(${INOUT_PLATFORM} "x86")
 if((CMAKE_SIZEOF_VOID_P EQUAL 8) OR ("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64") OR __x86_64__)
  set(${INOUT_PLATFORM} "x64")
 endif()
endmacro(GFN_PLATFORM_GET)


macro(GFN_BUILDTYPE_GET BUILDTYPE)
 set(${BUILDTYPE} "Release")
 if(CMAKE_CXX_FLAGS MATCHES "-g" OR CMAKE_C_FLAGS MATCHES "-g")
  set(${BUILDTYPE} "Debug")
 endif()
endmacro(GFN_BUILDTYPE_GET)

function(GFN_PROJECT_MODULE_SOURCE_GET INPUT_DIR OUTPUT_HEADERS OUTPUT_SOURCES)
 set(NEW_OUTPUT_SOURCES)
 set(NEW_OUTPUT_HEADERS)
 file(GLOB_RECURSE NEW_OUTPUT_HEADERS "${INPUT_DIR}/*.h" "${INPUT_DIR}/*.hpp")
 file(GLOB_RECURSE NEW_OUTPUT_SOURCES 
 "${INPUT_DIR}/*.ixx"
 "${INPUT_DIR}/*.cppm")

 set(${OUTPUT_HEADERS} ${NEW_OUTPUT_HEADERS} PARENT_SCOPE)
 set(${OUTPUT_SOURCES} ${NEW_OUTPUT_SOURCES} PARENT_SCOPE)
endfunction(GFN_PROJECT_MODULE_SOURCE_GET)

function(GFN_PROJECT_SOURCE_GET INPUT_DIR OUTPUT_HEADERS OUTPUT_SOURCES)
 set(NEW_OUTPUT_SOURCES)
 set(NEW_OUTPUT_HEADERS)
 file(GLOB_RECURSE NEW_OUTPUT_HEADERS "${INPUT_DIR}/*.h" "${INPUT_DIR}/*.hpp")
 file(GLOB_RECURSE NEW_OUTPUT_SOURCES 
 "${INPUT_DIR}/*.c" 
 "${INPUT_DIR}/*.cc" 
 "${INPUT_DIR}/*.cpp"
 "${INPUT_DIR}/*.cxx"
 "${INPUT_DIR}/*.ixx"
 "${INPUT_DIR}/*.cppm"
 "${INPUT_DIR}/*.rc" 
 "${INPUT_DIR}/*.def")

 set(${OUTPUT_HEADERS} ${NEW_OUTPUT_HEADERS} PARENT_SCOPE)
 set(${OUTPUT_SOURCES} ${NEW_OUTPUT_SOURCES} PARENT_SCOPE)
endfunction(GFN_PROJECT_SOURCE_GET)

macro(GFN_SET_TARGET_OUTDIR)
 # ARG 0 => 'Benchmark directory'
 # ARG 1 => 'PUBLISH_RUNTIME'
 # ARG 2 => 'PUBLISH_LIBRARY'
 # ARG 3 => 'PUBLISH_ARCHIVE'

 if((${ARGC} GREATER 0) AND (IS_DIRECTORY ${ARGV0}))
  set(BENCHMARK_DIR ${ARGV0})
  set(RUNTIME_DIR ${ARGV1})
  set(LIBRARY_DIR ${ARGV2})
  set(ARCHIVE_DIR ${ARGV3})
  #set(SPECIFIED_DIR ${ARGV4}) # BOOL

  if("${RUNTIME_DIR}" STREQUAL "")
  set(RUNTIME_DIR "bin")
  endif()

  if("${LIBRARY_DIR}" STREQUAL "")
  set(LIBRARY_DIR "libs")
  endif()

  if("${ARCHIVE_DIR}" STREQUAL "")
  set(LIBRARY_DIR "objs")
  endif()

  GFN_BUILDTYPE_GET(BUILDTYPE)
  GFN_PLATFORM_GET(PLATFORM)

  set(PUBLISH_LIBRARY ${BENCHMARK_DIR}/${LIBRARY_DIR})
  set(PUBLISH_RUNTIME ${BENCHMARK_DIR}/${RUNTIME_DIR})
  set(PUBLISH_ARCHIVE ${BENCHMARK_DIR}/${ARCHIVE_DIR})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PUBLISH_LIBRARY})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PUBLISH_RUNTIME})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PUBLISH_ARCHIVE})

  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PUBLISH_RUNTIME}/${PLATFORM}/Debug)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PUBLISH_RUNTIME}/${PLATFORM}/Release)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PUBLISH_LIBRARY}/${PLATFORM}/Debug)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PUBLISH_LIBRARY}/${PLATFORM}/Release)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PUBLISH_ARCHIVE}/${PLATFORM}/Debug)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PUBLISH_ARCHIVE}/${PLATFORM}/Release)
  #message(STATUS "${BENCHMARK_DIR}/${LIBRARY_DIR}/${CURRENT_COMPILE_PLATFORM}/ ${PLATFORM} ${BUILDTYPE}")
 else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "")
 endif()

endmacro(GFN_SET_TARGET_OUTDIR)
