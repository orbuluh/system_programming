set(CMAKE_C_COMPILER    "/usr/bin/clang")
set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")

cmake_minimum_required(VERSION 3.14)
project(system_programming VERSION 0.1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#add_definitions(-DRW=1)
#add_definitions(-DWR=1)

include_directories("demo")

add_executable(system_programming main.cpp)

target_link_libraries(system_programming LINK_PUBLIC ${EXTRA_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "playground")

#set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "rw")
#set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "wr")
