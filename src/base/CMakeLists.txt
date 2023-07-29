cmake_minimum_required(VERSION 3.26)
project(base)

set(base_sources
    "concepts/callable.h"
    "functional/bind.h"
    "functional/callback.h"
    "functional/functor_holder.h"
    "functional/functor_traits.h"
    )

add_library(base ${base_sources})
set_target_properties(base PROPERTIES LINKER_LANGUAGE CXX)

set(base_unittests_sources
    "functional/callback_unittest.cc"
    )

project(base_unittests)
set_target_properties(base_unittests PROPERTIES LINKER_LANGUAGE CXX)

add_executable(base_unittests ${base_unittests_sources})
target_link_libraries(base_unittests base gtest gmock gtest_main)
