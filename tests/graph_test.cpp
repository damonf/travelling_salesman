#include "graph.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include <stdexcept>
#include <vector>

using namespace Catch::literals; 

TEST_CASE("graph test", "[graph]")
{

    SECTION("a triangle can be parsed")
    {
        auto triangle =
            "0.0  4.1 16.5 \n"
            "4.1  0.0 8.0  \n"
            "16.5 8.0 0.0  \n";
    
        tsp::Graph sut(triangle);
    
        REQUIRE(sut.num_vertices() == 3);
    
        REQUIRE(sut.edge(0,0) == 0.0_a);
        REQUIRE(sut.edge(0,1) == 4.1_a);
        REQUIRE(sut.edge(0,2) == 16.5_a);
    
        REQUIRE(sut.edge(1,0) == 4.1_a);
        REQUIRE(sut.edge(1,1) == 0.0_a);
        REQUIRE(sut.edge(1,2) == 8.0_a);
    
        REQUIRE(sut.edge(2,0) == 16.5_a);
        REQUIRE(sut.edge(2,1) == 8.0_a);
        REQUIRE(sut.edge(2,2) == 0.0_a);
    }
    
    SECTION("dashes represent no path between vertices")
    {
        auto triangle =
            "0.0  -   16.0 \n"
            "4.0  0.0 8.0  \n"
            "16.0 8.0 0.0  \n";
    
        tsp::Graph sut(triangle);
    
        REQUIRE(sut.num_vertices() == 3);
    
        REQUIRE(sut.edge(0,0) == 0.0_a);
        REQUIRE(sut.edge(0,1) == Approx( tsp::Graph::NoEdgeVal ));
        REQUIRE(sut.edge(0,2) == 16.0_a);
    
        REQUIRE(sut.edge(1,0) == 4.0_a);
        REQUIRE(sut.edge(1,1) == 0.0_a);
        REQUIRE(sut.edge(1,2) == 8.0_a);
    
        REQUIRE(sut.edge(2,0) == 16.0_a);
        REQUIRE(sut.edge(2,1) == 8.0_a);
        REQUIRE(sut.edge(2,2) == 0.0_a);
    }
    
    SECTION("throws for invalid characters")
    {
        auto invalid =
            "0.0 4.0 16 \n"
            "X   Y   Z  \n"
            "A   B   c  \n";
     
        REQUIRE_THROWS_WITH(
                tsp::Graph(invalid),
                Catch::Contains( "invalid characters" )
                );
    }
    
    SECTION("throws when rows are different lengths")
    {
        auto invalid =
            "1.0 2.0 3.0     \n"
            "1.0 2.0 3.0 4.0 \n"
            "1.0 2.0 3.0     \n";
    
        REQUIRE_THROWS_WITH(
                tsp::Graph(invalid),
                Catch::Contains( "malformed" )
                );
    }
    
    SECTION("throws when number of rows does does not equal number of columns")
    {
        auto invalid =
            "1.0 2.0 3.0 \n"
            "1.0 2.0 3.0 \n";
    
        REQUIRE_THROWS_WITH(
                tsp::Graph(invalid),
                Catch::Contains( "malformed" )
                );
    }
    
    SECTION("throws for empty graph")
    {
        auto invalid = "";
    
        REQUIRE_THROWS_WITH(
                tsp::Graph(invalid),
                Catch::Contains( "malformed" )
                );
    }
    
    SECTION("throws for only one point")
    {
        auto invalid = "1.0";
    
        REQUIRE_THROWS_WITH(
                tsp::Graph(invalid),
                Catch::Contains( "malformed" )
                );
    }
    
    SECTION("throws for invalid edge")
    {
        auto line =
            "0.0  4.0 \n"
            "4.0  0.0 \n";
    
        tsp::Graph sut(line);
    
        REQUIRE(sut.num_vertices() == 2);
    
        REQUIRE_THROWS_AS(
                sut.edge(3, 3),
                std::out_of_range
                );
    }
    
    SECTION("throws for negative numbers")
    {
        auto invalid =
            "0.0  -4.0 \n"
            "-4.0  0.0 \n";
    
        REQUIRE_THROWS_WITH(
                tsp::Graph(invalid),
                Catch::Contains( "-4.0 is not a valid positive number" )
                );
    }
    
    SECTION("throws for multiple dashes")
    {
        auto invalid =
            "0.0  -- \n"
            "--   0.0 \n";
    
        REQUIRE_THROWS_WITH(
                tsp::Graph(invalid),
                Catch::Contains( "-- is not a valid positive number" )
                );
    }
    
    SECTION("throws for multiple dots")
    {
        auto invalid =
            "0.0.0  -- \n"
            "--     0.0 \n";
    
        REQUIRE_THROWS_WITH(
                tsp::Graph(invalid),
                Catch::Contains( "0.0.0 is not a valid number" )
                );
    }
    
    SECTION("computes length of a path")
    {
        auto triangle =
            "0.0  4.0 16.0 \n"
            "4.0  0.0 8.0  \n"
            "16.0 8.0 0.0  \n";
    
        tsp::Graph sut(triangle);
    
        tsp::Path path{0, 1, 2, 0};
    
        REQUIRE(sut.length(path) == 28.0_a);
    }
    
    SECTION("throws for invalid path")
    {
        auto triangle =
            "0.0  4.0 16.0 \n"
            "4.0  0.0 8.0  \n"
            "16.0 8.0 0.0  \n";
    
        tsp::Graph sut(triangle);
    
        tsp::Path path{0, 1, 2, 3, 0};
    
        REQUIRE_THROWS_AS(
                sut.length(path),
                std::out_of_range
                );
    }

}
