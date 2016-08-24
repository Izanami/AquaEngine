cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_BUILD_TYPE Release)
PROJECT(AquaEngine)

find_package(GTest)

if(DEVEL)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall --pedantic -pedantic-errors -Wdocumentation --std=c++1z -Weverything -Werror -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -g -fsanitize=address -fsanitize=leak -O0 ")
    else()
        message( FATAL_ERROR "In devel mode, you must use clang." )
    endif()
else()
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall --pedantic -pedantic-errors -Wdocumentation --std=c++1z -Weverything -Werror -Wno-c++98-compat -Wno-padded")

    else()
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall --pedantic -pedantic-errors --std=c++1z -Wno-c++98-compat-pedantic")
    endif()
endif()

###
# MAIN
###
add_library(ae src/ae.cc)
target_link_libraries(ae vulkan xcb)

###
# DEMO
###
add_executable(ae-demo src/demo.cc)
target_link_libraries(ae-demo ae)

###
# DEBUG
###
add_executable(ae-debug src/debug.cc)
target_link_libraries(ae-debug ae)

###
# TEST
###
if(GTEST_FOUND)
    enable_testing()
    include_directories(${GTEST_INCLUDE_DIRS})

    add_executable(ae-test src/test.cc)
    target_link_libraries(ae-test ae ${GTEST_BOTH_LIBRARIES})

    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set_target_properties(ae-test PROPERTIES COMPILE_FLAGS "-Wno-global-constructors -Wno-weak-vtables -Wno-used-but-marked-unused -Wno-missing-prototypes")
    endif()

    add_test(ae-test ae-test)
endif()
