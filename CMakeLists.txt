cmake_minimum_required(VERSION 3.16)

project(
    CMakeTemplateProject
    VERSION 1.0
    DESCRIPTION "tsp"
    LANGUAGES CXX
    )

# generate the test target
enable_testing()

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wwrite-strings -Wno-parentheses -Wno-comment -Wpedantic -Warray-bounds -Weffc++ -Werror)

set(INCLUDE_BASE
    "${PROJECT_SOURCE_DIR}/include")

add_subdirectory(apps)
add_subdirectory(src)
add_subdirectory(tests)

# install(TARGETS main_app DESTINATION "${PROJECT_SOURCE_DIR}/bin/")
