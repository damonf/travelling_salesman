#include "breeder.h"

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp> 

#include <stdexcept>

using namespace tsp;
using trompeloeil::_;

namespace breeder_tests {

// Mocks
class RandomNumbersMockInt : public IRandomNumbers<size_t> {
    public:
        MAKE_CONST_MOCK2(
                generator,
                std::function<size_t ()>(
                    size_t start
                    ,size_t end
                    )
                );
};

TEST_CASE("breeder tests", "[breeder]")
{
    SECTION("breeds 1 child from 2 parents")
    {
        auto random_numbers_mock = std::make_unique<RandomNumbersMockInt>();

        auto& random_numbers = *random_numbers_mock;

        // lambda to return parent indexes
        // return parent 1, then parent 2
        std::vector parent_idxs{0, 1};
        int p_idx = 0;
        auto fn1 = [p_idx, &parent_idxs] () mutable {
            return parent_idxs.at(p_idx++);
        };

        REQUIRE_CALL(random_numbers, generator(0, 1))
            .RETURN(fn1);

        // lambda to return cut point indexes
        // cut the half open range [2, 4)
        std::vector cut_pts{2, 4};
        auto c_idx = 0;
        auto fn2 = [c_idx, &cut_pts] () mutable {
            return cut_pts.at(c_idx++);
        };

        REQUIRE_CALL(random_numbers, generator(1, 6))
            .RETURN(fn2);

        // Create candidates with a path_len we can use as an Id
        std::vector<tsp::Candidate> parents = {
            { {0, 1, 2, 3, 4, 5, 0}, 1.0 }, //  path, path_len
            { {0, 5, 4, 3, 2, 1, 0}, 2.0 }
        };

        tsp::Breeder sut{
            std::move(random_numbers_mock)
        };

        auto children = sut.breed(parents, 1);

        // expecting 1 child
        REQUIRE(children.size() == 1);
        // with path len of 7
        REQUIRE(children[0].size() == 7);

        // cut range [2, 4) from parent 1
        REQUIRE_THAT(
                children[0],
                Catch::Matchers::Equals(tsp::Path{ 0, 4, 2, 3, 1, 5, 0 })
                );
    }

    SECTION("breeds 2 children from 2 parents")
    {
        auto random_numbers_mock = std::make_unique<RandomNumbersMockInt>();

        auto& random_numbers = *random_numbers_mock;

        // lambda to return parent indexes
        std::vector parent_idxs{0, 1, 0, 1};
        int p_idx = 0;
        auto fn1 = [p_idx, &parent_idxs] () mutable {
            return parent_idxs.at(p_idx++);
        };

        REQUIRE_CALL(random_numbers, generator(0, 1))
            .RETURN(fn1);

        // lambda to return cut point indexes
        // cut the half open range [2, 4), then [1, 5)
        std::vector cut_pts{2, 4, 1, 6};
        auto c_idx = 0;
        auto fn2 = [c_idx, &cut_pts] () mutable {
            return cut_pts.at(c_idx++);
        };

        REQUIRE_CALL(random_numbers, generator(1, 6))
            .RETURN(fn2);

        // Create candidates with a path_len we can use as an Id
        std::vector<tsp::Candidate> parents = {
            { {0, 1, 2, 3, 4, 5, 0}, 1.0 }, //  path, path_len
            { {0, 5, 4, 3, 2, 1, 0}, 2.0 }
        };

        tsp::Breeder sut{
            std::move(random_numbers_mock)
        };

        auto children = sut.breed(parents, 2);

        // expecting 2 child
        REQUIRE(children.size() == 2);
        // with path len of 7
        REQUIRE(children[0].size() == 7);
        REQUIRE(children[1].size() == 7);

        // cut range [2, 4) from parent 1
        REQUIRE_THAT(
                children[0],
                Catch::Matchers::Equals(tsp::Path{ 0, 4, 2, 3, 1, 5, 0 })
                );

        // cut range [1, 5) from parent 1
        REQUIRE_THAT(
                children[1],
                Catch::Matchers::Equals(tsp::Path{ 0, 1, 2, 3, 4, 5, 0 })
                );
    }

    SECTION("reorders cut point indexes when first is greater than second")
    {
        auto random_numbers_mock = std::make_unique<RandomNumbersMockInt>();

        auto& random_numbers = *random_numbers_mock;

        // lambda to return parent indexes
        // return parent 1, then parent 2
        std::vector parent_idxs{0, 1};
        int p_idx = 0;
        auto fn1 = [p_idx, &parent_idxs] () mutable {
            return parent_idxs.at(p_idx++);
        };

        REQUIRE_CALL(random_numbers, generator(0, 1))
            .RETURN(fn1);

        // lambda to return cut point indexes
        // cut the half open range [2, 4)
        // but these will need reordering
        std::vector cut_pts{4, 2};
        auto c_idx = 0;
        auto fn2 = [c_idx, &cut_pts] () mutable {
            return cut_pts.at(c_idx++);
        };

        REQUIRE_CALL(random_numbers, generator(1, 6))
            .RETURN(fn2);

        // Create candidates with a path_len we can use as an Id
        std::vector<tsp::Candidate> parents = {
            { {0, 1, 2, 3, 4, 5, 0}, 1.0 }, //  path, path_len
            { {0, 5, 4, 3, 2, 1, 0}, 2.0 }
        };

        tsp::Breeder sut{
            std::move(random_numbers_mock)
        };

        auto children = sut.breed(parents, 1);

        // expecting 1 child
        REQUIRE(children.size() == 1);
        // with path len of 7
        REQUIRE(children[0].size() == 7);

        // cut range [2, 4) from parent 1
        REQUIRE_THAT(
                children[0],
                Catch::Matchers::Equals(tsp::Path{ 0, 4, 2, 3, 1, 5, 0 })
                );
    }
}

}
