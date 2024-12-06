cmake_minimum_required(VERSION 3.5)

project(sqlite3)

set(SOURCES shell.c sqlite3.c sqlite3.h sqlite3ext.h)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${xs3RDPARTY_DIR}/sqlite3/)
