add_library(tsp "")
add_subdirectory(tsp)

find_package(Boost 1.79 COMPONENTS program_options REQUIRED)

include_directories(SYSTEM ${Boost_INCLUDE_DIR} )

target_link_libraries(tsp PRIVATE Boost::program_options)
