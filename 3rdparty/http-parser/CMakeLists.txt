cmake_minimum_required(VERSION 3.5)

project(http_parser)

set(SOURCES 
http_parser.c
http_parser_method.cxx
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} 
PRIVATE
${xs3RDPARTY_DIR}/http-parser/
)
