cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_CXX_STANDARD 20)

# Enables modules.
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)

project(base)

set(base_sources
    "concepts/callable.h"
    "functional/bind.h"
    "functional/callback.h"
    "functional/functor_holder.h"
    "functional/functor_traits.h"
    )

set(base_unittests_sources
    "functional/callback_unittest.cc"
    )

add_library(base ${base_sources})
set_target_properties(base PROPERTIES LINKER_LANGUAGE CXX)

project(base_unittests)
set_target_properties(base_unittests PROPERTIES LINKER_LANGUAGE CXX)

include_directories(${CMAKE_SOURCE_DIR}/third_party/googletest/googletest/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/googletest/googlemock/include)
add_executable(base_unittests ${base_unittests_sources})
target_link_libraries(base_unittests base gtest gmock gtest_main)
