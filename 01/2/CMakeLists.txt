cmake_minimum_required(VERSION 3.26)
project(SqlSelectQueryBuilder2)

set(CMAKE_CXX_STANDARD 17)
include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    source/sql_query_builder.cc
)

add_library(builder ${SOURCES})
add_executable(SqlSelectQueryBuilder2 main.cc)
target_link_libraries(SqlSelectQueryBuilder2 builder)