cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)

project(yadb CXX)

add_subdirectory(base)
add_subdirectory(query)
add_subdirectory(server)
add_subdirectory(scheduler)
add_subdirectory(third_party)
