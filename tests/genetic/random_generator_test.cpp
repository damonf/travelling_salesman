#include "random_generator.h"
#include "graph.h"
#include "candidate.h"

#include <catch2/catch.hpp>

#include <vector>
#include <string>

using namespace tsp;

TEST_CASE("random_generator tests", "[random_generator]")
{
    //         0
    //        / \
    //     16/   \4
    //      /     \
    //     /       \
    //    2---------1
    //         8
    //
    //     0   1   2    
    //   ---------------    
    // 0 | 0  | 4 | 16 |    
    //   |--------------    
    // 1 | 4  | 0 | 8  |    
    //   |--------------    
    // 2 | 16 | 8 | 0  |     
    //   |--------------    
    //
    SECTION("generates candidates")
    {
        const auto triangle =
            "0.0  4.0 16.0 \n"
            "4.0  0.0 8.0  \n"
            "16.0 8.0 0.0  \n";

        tsp::RandomGenerator sut{};

        tsp::Graph triangle_graph{triangle};

        auto result = sut.candidates(triangle_graph, 10);

        REQUIRE(result.size() == 10);

        const tsp::Path first{0, 1, 2, 0};
        const tsp::Path second{0, 2, 1, 0};

        for (const auto& c : result) {

            REQUIRE(c.path_len() == 28.0);

            const auto& path = c.path();
            REQUIRE(path.size() == 4);

            const auto is_equal_first =
                std::equal(path.cbegin(), path.cend(), first.cbegin());
            const auto is_equal_second =
                std::equal(path.cbegin(), path.cend(), second.cbegin());

            const auto is_equal_first_or_second =
                is_equal_first || is_equal_second;

            REQUIRE(is_equal_first_or_second);
        }
    }

    //           0
    //          /|\
    //        -/ | \1
    //        / 4|  \
    //       / 2 |   \
    //      3---------1
    //       \   |   /
    //        \  |  /
    //        3\ | /-
    //          \|/
    //           2
    //
    //     0   1   2   3
    //   -----------------
    // 0 | 0 | 1 | 4 | - |
    //   |---------------|
    // 1 | 1 | 0 | - | 2 |
    //   |---------------|
    // 2 | 4 | - | 0 | 3 | 
    //   |---------------|
    // 3 | - | 2 | 3 | 0 |
    //   -----------------
    //
    SECTION("generates candidates when not all paths are valid")
    {
        const auto diamond =
            "0.0  1.0  4.0  - \n"
            "1.0  0.0  -    2.0 \n"
            "4.0  -    0.0  3.0 \n"
            "-    2.0  3.0  0.0 \n";
        
        tsp::RandomGenerator sut{};
    
        tsp::Graph diamond_graph{diamond};
    
        auto result = sut.candidates(diamond_graph, 10);
    
        REQUIRE(result.size() == 10);
    
        const tsp::Path first{0, 1, 3, 2, 0};
        const tsp::Path second{0, 2, 3, 1, 0};

        for (const auto& c : result) {

            REQUIRE(c.path_len() == 10.0);

            const auto& path = c.path();
            REQUIRE(path.size() == 5);

            const auto is_equal_first =
                std::equal(path.cbegin(), path.cend(), first.cbegin());
            const auto is_equal_second =
                std::equal(path.cbegin(), path.cend(), second.cbegin());

            const auto is_equal_first_or_second =
                is_equal_first || is_equal_second;

            REQUIRE(is_equal_first_or_second);
        }
    }
}
