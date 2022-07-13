#include "parent_selector.h"

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp> 

using namespace tsp;
using trompeloeil::_;

namespace parent_selector_tests
{

// Mocks
class RandomNumbersMockDouble : public IRandomNumbers<double> {
    public:
        MAKE_CONST_MOCK2(
                generator,
                std::function<double ()>(
                    double start
                    ,double end
                    )
                );
};

TEST_CASE("parent_selector tests", "[parent_selector]")
{
    SECTION("select_parents selects all parents from even fitness distribution")
    {
        auto random_num = GENERATE(0.0, 9.9);

        auto random_numbers_mock = std::make_unique<RandomNumbersMockDouble>();

        auto& random_numbers = *random_numbers_mock;

        REQUIRE_CALL(random_numbers, generator(_, _))
            .RETURN([random_num] () {
                    return random_num;
                    });

        // Create candidates with a path_len we can use as an Id
        std::vector<tsp::Candidate> candidates = {
            { {0, 1}, 1.0 }, //  path, path_len
            { {0, 1}, 2.0 },
            { {0, 1}, 3.0 }
        };
    
        candidates[0].fitness(10.0);
        candidates[1].fitness(10.0);
        candidates[2].fitness(10.0);
    
        tsp::ParentSelector sut{
            std::move(random_numbers_mock)
        };
    
        auto parents = sut.select(candidates, 3);
    
        REQUIRE(parents.size() == 3);
        REQUIRE(parents[0].path_len() == 1.0);
        REQUIRE(parents[1].path_len() == 2.0);
        REQUIRE(parents[2].path_len() == 3.0);
    }

    SECTION("select_parents selects parents with frequency proportional to fitness")
    {
        auto random_num = GENERATE(0.0, 9.9);

        auto random_numbers_mock = std::make_unique<RandomNumbersMockDouble>();

        auto& random_numbers = *random_numbers_mock;

        REQUIRE_CALL(random_numbers, generator(_, _))
            .RETURN([random_num] () {
                    return random_num;
                    });

        // Create candidates with a path_len we can use as an Id
        std::vector<tsp::Candidate> candidates = {
            { {0, 1}, 1.0 }, //  path, path_len
            { {0, 1}, 2.0 },
            { {0, 1}, 3.0 }
        };
    
        candidates[0].fitness(20.0);
        candidates[1].fitness(10.0);
        candidates[2].fitness(10.0);
    
        tsp::ParentSelector sut{
            std::move(random_numbers_mock)
        };
    
        auto parents = sut.select(candidates, 4);
    
        REQUIRE(parents.size() == 4);
        REQUIRE(parents[0].path_len() == 1.0);
        REQUIRE(parents[1].path_len() == 1.0);
        REQUIRE(parents[2].path_len() == 2.0);
        REQUIRE(parents[3].path_len() == 3.0);
    }
}

}
