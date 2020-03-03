cmake_minimum_required(VERSION 3.15)
project(pgfast)

set(CMAKE_CXX_STANDARD 20)


find_package(PostgreSQL REQUIRED)
include_directories (${PostgreSQL_INCLUDE_DIRS})

add_executable(pgfast main.cpp src/postgre_map/PostgreMapper.cpp src/postgre_map/PostgreMapper.h)
target_link_libraries(pgfast ${PostgreSQL_LIBRARIES})


