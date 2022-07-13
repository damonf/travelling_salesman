target_sources(tsp
    PRIVATE
        genetic.cpp
        random_generator.cpp
        natural_selector.cpp
        parent_selector.cpp
        breeder.cpp
        mutator.cpp
)

target_include_directories(tsp PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(interfaces)
