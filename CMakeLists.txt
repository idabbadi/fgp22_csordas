cmake_minimum_required(VERSION 3.5.1)
project(fgp CXX)
enable_testing()
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/out")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_definitions("-DWORKING_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/\"")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

link_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib")

file(GLOB student "src/student/*.cpp" "src/helper/*.cpp")

add_library(student SHARED "${student}")
target_include_directories(student PUBLIC src/helper PUBLIC src/student)

add_executable(fgp src/main.cpp)
target_link_libraries(fgp student)
