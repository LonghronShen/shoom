
cmake_minimum_required(VERSION 3.1)
project(${project_name}-test C CXX)

enable_testing()

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.cc)

add_executable(${project_name}-test ${SOURCES})

target_link_libraries(${project_name}-test shoom)

add_test(NAME ${project_name}-test COMMAND ${project_name}-test)