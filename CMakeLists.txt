cmake_minimum_required(VERSION 3.1)
set(project_name "shoom")

if(TARGET ${project_name})
  return()
endif()

project(${project_name} C CXX)

option(SHOOM_BUILD_TESTS "Build tests for shoom" ON)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cc)

add_library(${project_name} STATIC ${SOURCES})

target_include_directories(${project_name} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

set_target_properties(${project_name} PROPERTIES POSITION_INDEPENDENT_CODE ON)

if(MSVC)
  target_compile_options(${project_name} PRIVATE -W3 -EHsc)
else()
  target_compile_features(${project_name} PUBLIC cxx_std_11)
endif()

if(UNIX)
  find_library(LIBRT rt)
  if(LIBRT)
    target_link_libraries(shoom ${LIBRT})
  endif()
endif()

add_library(shoom::shoom ALIAS shoom)

if(SHOOM_BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()
