#include "genetic.h"
#include "irandom_generator.h"
#include "graph.h"
#include "candidate.h"

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp> 

#include <vector>
#include <string>
#include <memory>

using namespace tsp;
using trompeloeil::_;

namespace genetic_tests {

// Mocks
class RandomGeneratorMock : public IRandomGenerator {
    public:
        MAKE_CONST_MOCK2(
                candidates,
                std::vector<Candidate>(const Graph& graph, const size_t num)
                );
};

class NaturalSelectorMock : public INaturalSelector {
    public:
        MAKE_CONST_MOCK3(
                candidates,
                std::vector<Candidate>(
                    const Graph& graph,
                    const std::vector<Candidate>& current_gen,
                    size_t k
                    )
                );
};

TEST_CASE("genetic tests", "[genetic]")
{
    SECTION("returns fittest candidate after 1 iteration")
    {
        constexpr tsp::PopSize pop_size{4};

        auto random_generator_mock = std::make_unique<RandomGeneratorMock>();
        auto natural_selector_mock = std::make_unique<NaturalSelectorMock>();

        // Need to get a ref to the underlying mock object so
        // we can configure it.
        // Note: mocks have no copy or move ctors
        auto& random_generator = *random_generator_mock;
        auto& natural_selector = *natural_selector_mock;

        REQUIRE_CALL(random_generator, candidates(_, _))
            .RETURN(std::vector<Candidate>{
                {{0, 1, 2, 0}, 6.0},
                {{0, 1, 2, 0}, 6.0},
                {{0, 1, 2, 0}, 6.0},
                {{0, 2, 1, 0}, 3.0}, // most fit
            });

        REQUIRE_CALL(natural_selector, candidates(_, _, _))
            .RETURN(std::vector<Candidate>{
                {{0, 1, 2, 0}, 6.0},
                {{0, 1, 2, 0}, 6.0},
                {{0, 2, 1, 0}, 3.0},
                {{0, 2, 1, 0}, 3.0},
            });

        const Genetic sut{
            std::move(random_generator_mock)
            ,std::move(natural_selector_mock)
            ,pop_size
        };

        tsp::Graph graph(
                "0  2 1\n"
                "1  0 2\n"
                "2  1 0\n"
                );

        auto solution = sut.shortest_path(graph);

        REQUIRE(solution.first.size() == 4);
        REQUIRE(solution.second == 3.0);
    }

    SECTION("returns fittest candidate after 2 iterations")
    {
        trompeloeil::sequence seq;

        constexpr tsp::PopSize pop_size{5};
        auto random_generator_mock = std::make_unique<RandomGeneratorMock>();
        auto natural_selector_mock = std::make_unique<NaturalSelectorMock>();

        // Need to get a ref to the underlying mock object so
        // we can configure it.
        // Note: mocks have no copy or move ctors
        auto& random_generator = *random_generator_mock;
        auto& natural_selector = *natural_selector_mock;

        REQUIRE_CALL(random_generator, candidates(_, _))
            .IN_SEQUENCE(seq)
            .RETURN(std::vector<Candidate>{
                {{0, 1, 2, 0}, 6.0},
                {{0, 1, 2, 0}, 6.0},
                {{0, 1, 2, 0}, 6.0},
                {{0, 1, 2, 0}, 6.0},
                {{0, 2, 1, 0}, 3.0}, // most fit
            });

        REQUIRE_CALL(natural_selector, candidates(_, _, _))
            .IN_SEQUENCE(seq)
            .RETURN(std::vector<Candidate>{
                {{0, 1, 2, 0}, 6.0},
                {{0, 1, 2, 0}, 6.0},
                {{0, 1, 2, 0}, 6.0},
                {{0, 2, 1, 0}, 3.0},
                {{0, 2, 1, 0}, 3.0},
            });

        REQUIRE_CALL(natural_selector, candidates(_, _, _))
            .IN_SEQUENCE(seq)
            .RETURN(std::vector<Candidate>{
                {{0, 1, 2, 0}, 6.0},
                {{0, 1, 2, 0}, 6.0},
                {{0, 2, 1, 0}, 3.0},
                {{0, 2, 1, 0}, 3.0},
                {{0, 2, 1, 0}, 3.0},
            });

        const Genetic sut{
            std::move(random_generator_mock)
            ,std::move(natural_selector_mock)
            ,pop_size
        };

        tsp::Graph graph(
                "0  2 1\n"
                "1  0 2\n"
                "2  1 0\n"
                );

        auto solution = sut.shortest_path(graph);

        REQUIRE(solution.first.size() == 4);
        REQUIRE(solution.second == 3.0);
    }
}

}
