set(CMAKE_C_COMPILER    "/usr/bin/clang")
set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")

cmake_minimum_required(VERSION 3.14)
project(example_app VERSION 0.1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(util)

add_executable(example_app main.cpp)

# need to install libfmt-dev
find_package(fmt REQUIRED)

find_package(Boost COMPONENTS program_options REQUIRED)
target_include_directories(example_app PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(example_app LINK_PUBLIC util)
target_link_libraries(example_app PRIVATE fmt::fmt ${Boost_PROGRAM_OPTIONS_LIBRARY})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "playground")
