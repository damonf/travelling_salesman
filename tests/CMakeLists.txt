Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.7
  )

FetchContent_Declare(
  Trompeloeil
  GIT_REPOSITORY https://github.com/rollbear/trompeloeil.git
  GIT_TAG        v41
  )

FetchContent_MakeAvailable(Catch2 Trompeloeil)

# Here, Boost must be installed locally (see notes.rst)
find_package(Boost 1.79 COMPONENTS program_options REQUIRED)

include_directories(
  SYSTEM
  ${Boost_INCLUDE_DIR}
  ${trompeloeil_SOURCE_DIR}/include 
  )

add_executable(test_tsp
  graph_test.cpp
  brute_force_test.cpp
  config_test.cpp
  random_numbers_test.cpp
  graph_gen_test.cpp
  )

add_subdirectory(genetic)

target_link_libraries(test_tsp
  PRIVATE
  tsp
  Catch2::Catch2
  trompeloeil::trompeloeil
  Boost::program_options
  )

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)

include(CTest)
include(Catch)

# Run the function defined by the Catch2 CMake module
catch_discover_tests(test_tsp)

#message(STATUS "catch2_SOURCE_DIR=${catch2_SOURCE_DIR}")
#It's here: build/_deps/catch2-src

#message(STATUS "trompeloeil_SOURCE_DIR=${trompeloeil_SOURCE_DIR}")
#It's here: build/_deps/trompeloeil-src
