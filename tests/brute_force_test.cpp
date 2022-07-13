#include "brute_force.h"

#include <catch2/catch.hpp>

#include <stdexcept>

TEST_CASE("brute_force tests", "[brute_force]")
{
    
    //         0
    //        / \
    //   16.5/   \4
    //      /     \
    //     /       \
    //    2---------1
    //         8
    //
    //     0   1   2    
    //   -------------------
    // 0 | 0    | 4 | 16.5 |
    //   |------------------
    // 1 | 4    | 0 | 8    |
    //   |------------------
    // 2 | 16.5 | 8 | 0    |
    //   |------------------
    //
    SECTION("brute force finds shortest path when it's the first permuation")
    {
        const auto triangle =
            "0.0  4.0 16.5 \n"
            "4.0  0.0 8.0  \n"
            "16.5 8.0 0.0  \n";
        
        tsp::BruteForce sut{};
    
        tsp::Graph triangle_graph{triangle};
    
        auto result = sut.shortest_path(triangle_graph);
    
        REQUIRE(result.second == 28.5);
        REQUIRE(result.first.size() == 4);
        REQUIRE(result.first[0] == 0);
        REQUIRE(result.first[1] == 1);
        REQUIRE(result.first[2] == 2);
        REQUIRE(result.first[3] == 0);
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
    SECTION("brute force finds the shortest path when not all paths are valid")
    {
        const auto square =
            "0.0  1.0  4.0  -   \n"
            "1.0  0.0  -    2.0 \n"
            "4.0  -    0.0  3.0 \n"
            "-    2.0  3.0  0.0 \n";
    
        tsp::BruteForce sut{};
    
        tsp::Graph square_graph{square};
    
        auto result = sut.shortest_path(square_graph);
    
        REQUIRE(result.second == 10.0);
        REQUIRE(result.first.size() == 5);
        REQUIRE(result.first[0] == 0);
        REQUIRE(result.first[1] == 1);
        REQUIRE(result.first[2] == 3);
        REQUIRE(result.first[3] == 2);
        REQUIRE(result.first[4] == 0);
    }
    
    //         0
    //        / \
    //      -/   \2
    //      /     \
    //     /       \
    //    2---------1
    //         4
    //
    //     0   1   2    
    //   -------------    
    // 0 | 0 | 2 | - |    
    //   |------------    
    // 1 | 2 | 0 | 4 |    
    //   |------------    
    // 2 | - | 4 | 0 |     
    //   |------------    
    //
    SECTION("brute force returns no path when none exists")
    {
        const auto square =
            "0.0 2.0  -    \n"
            "2.0 0.0  4.0  \n"
            "-   4.0  0.0  \n";
    
        tsp::BruteForce sut{};
    
        tsp::Graph square_graph{square};
    
        auto result = sut.shortest_path(square_graph);
    
        REQUIRE(result.second == tsp::Graph::NoEdgeVal);
    }
    
    //         0
    //        / \
    //    6/3/   \4/1
    //      /     \
    //     /       \
    //    2---------1
    //        5/2
    //
    //     0   1   2    
    //   -------------    
    // 0 | 0 | 4 | 3 |    
    //   |------------    
    // 1 | 1 | 0 | 5 |    
    //   |------------    
    // 2 | 6 | 2 | 0 |     
    //   |------------    
    //
    SECTION("brute force finds shortest path in an asymmetric graph")
    {
        const auto square =
            "0.0  4.0  3.0  \n"
            "1.0  0.0  5.0  \n"
            "6.0  2.0  0.0  \n";
    
        tsp::BruteForce sut{};
    
        tsp::Graph square_graph{square};
    
        auto result = sut.shortest_path(square_graph);
    
        REQUIRE(result.second == 6.0);
        REQUIRE(result.first.size() == 4);
        REQUIRE(result.first[0] == 0);
        REQUIRE(result.first[1] == 2);
        REQUIRE(result.first[2] == 1);
        REQUIRE(result.first[3] == 0);
    }
    
    //     0    1    2    3
    //   ---------------------
    // 0 | 0  | 10 | 15 | 20 |
    //   |-------------------|
    // 1 | 5  | 0  | 9  | 10 |
    //   |-------------------|
    // 2 | 6  | 13 | 0  | 12 | 
    //   |-------------------|
    // 3 | 8  | 8  | 9  | 0  |
    //   ---------------------
    //
    SECTION("brute force a larger asymmetric graph")
    {
        const auto square =
            "0.0  10.0  15.0  20.0 \n"
            "5.0  0.0   9.0   10.0 \n"
            "6.0  13.0  0.0   12.0 \n"
            "8.0  8.0   9.0   0.0  \n";
    
        tsp::BruteForce sut{};
    
        tsp::Graph square_graph{square};
    
        auto result = sut.shortest_path(square_graph);
    
        REQUIRE(result.second == 35.0);
        REQUIRE(result.first.size() == 5);
        REQUIRE(result.first[0] == 0);
        REQUIRE(result.first[1] == 1);
        REQUIRE(result.first[2] == 3);
        REQUIRE(result.first[3] == 2);
        REQUIRE(result.first[4] == 0);
    }
    
    //     0    1    2    3    4
    //   -------------------------|
    // 0 | 0  | 4  | 20 | 2  | 8  |
    //   |------------------------|
    // 1 | 4  | 0  | 6  | 7  | 19 |
    //   |------------------------|
    // 2 | 20 | 6  | 0  | 3  | 10 |
    //   |------------------------|
    // 3 | 2  | 7  | 3  | 0  | 12 |
    //   |------------------------|
    // 4 | 8  | 19 | 10 | 12 | 0  |
    //   --------------------------
    //
    SECTION("brute force a larger symmetric graph")
    {
        const auto square =
            "0.0  4.0  20.0 2.0  8.0  \n"
            "4.0  0.0  6.0  7.0  19.0 \n"
            "20.0 6.0  0.0  3.0  10.0 \n"
            "2.0  7.0  3.0  0.0  12.0 \n"
            "8.0  19.0 10.0 12.0 0.0  \n";
    
        tsp::BruteForce sut{};
    
        tsp::Graph square_graph{square};
    
        auto result = sut.shortest_path(square_graph);
    
        REQUIRE(result.second == 32.0);
        REQUIRE(result.first.size() == 6);
        REQUIRE(result.first[0] == 0);
        REQUIRE(result.first[1] == 1);
        REQUIRE(result.first[2] == 3);
        REQUIRE(result.first[3] == 2);
        REQUIRE(result.first[4] == 4);
        REQUIRE(result.first[5] == 0);
    }

}
