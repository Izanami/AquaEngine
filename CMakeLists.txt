cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_BUILD_TYPE Release)
PROJECT(AquaEngine)

# Package cmake
find_package(Threads)
find_package(GTest)
find_package(Doxygen)

# Options
option(DEVEL "Enable devel mode" OFF)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

# Set flags
if(DEVEL)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fsanitize=address -fsanitize=undefined -fsanitize=leak -fno-omit-frame-pointer")
    else()
        message( FATAL_ERROR "In devel mode, you must use clang." )
    endif()
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdocumentation -Weverything")
endif()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall --pedantic -pedantic-errors --std=c++1z -Wno-c++98-compat-pedantic -Werror -Wno-c++98-compat -Wno-padded")

# Extra packages cmake
set(CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
)

##
# Window
##
find_package(GLFW 3.0.0)

if(GLFW_FOUND AND (GLFW_VERSION VERSION_EQUAL 3.0 OR GLFW_VERSION VERSION_GREATER 3.0))
    add_definitions( -DGLFW_VERSION_3 )
endif()

###
# MAIN
###
add_library(ae src/window.cc src/window/glfw.cc src/application.cc src/instance.cc src/error.cc src/error/flags.cc src/error/vulkan.cc)
target_link_libraries(ae vulkan ${GLFW_LIBRARIES})

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

    add_executable(ae-test src/test.cc src/window_test.cc src/window/glfw_test.cc src/application_test.cc src/instance_test.cc src/error_test.cc src/error/flags_test.cc src/error/vulkan_test.cc)
    target_link_libraries(ae-test ae ${CMAKE_THREAD_LIBS_INIT} ${GTEST_BOTH_LIBRARIES})

    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set_target_properties(ae-test PROPERTIES COMPILE_FLAGS "-Wno-global-constructors -Wno-weak-vtables -Wno-used-but-marked-unused -Wno-missing-prototypes")
    endif()

    add_test(ae-test ae-test)
endif()

###
# DOCUMENTATION
###
if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
endif()
