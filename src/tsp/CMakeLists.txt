target_sources(tsp
    PRIVATE
        graph.cpp
        brute_force.cpp
        config.cpp
)

target_include_directories(tsp PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(genetic)


# message(STATUS "CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")
# message(STATUS "CMAKE_CURRENT_LIST_DIR=${CMAKE_CURRENT_LIST_DIR}")

