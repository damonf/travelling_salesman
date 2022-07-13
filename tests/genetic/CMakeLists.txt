target_sources(test_tsp
    PRIVATE
      genetic_test.cpp
      random_generator_test.cpp
      natural_selector_test.cpp
      parent_selector_test.cpp
      breeder_test.cpp
      mutator_test.cpp
)

target_include_directories(test_tsp PUBLIC ${CMAKE_CURRENT_LIST_DIR})

