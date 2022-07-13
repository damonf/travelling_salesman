#include "mutator.h"

#include <memory>

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp> 

using namespace tsp;
using trompeloeil::_;

namespace mutator_tests {

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

struct TestCase {
    std::vector<int> indexes;
    std::vector<size_t> expected_path;
};

TEST_CASE("mutator tests", "[mutator]")
{
    SECTION("mutates correctly for various swap indexes")
    {
        auto test_case = GENERATE(
            TestCase{
                { 1, 3 },
                { 0, 3, 2, 1, 4, 5, 0 }
            },
            TestCase{
                { 5, 5 },
                { 0, 5, 2, 3, 4, 1, 0 }
            },
            TestCase{
                { 1, 1 },
                { 0, 2, 1, 3, 4, 5, 0 }
            }
        );

        auto random_numbers_mock = std::make_unique<RandomNumbersMockInt>();

        auto& random_numbers = *random_numbers_mock;

        // Probability of mutation, returns 1 to always mutate
        auto fn1 = [] () {
            return 1;
        };

        REQUIRE_CALL(random_numbers, generator(1, 99))
            .RETURN(fn1);

        // Indexes to swap for the mutation
        int p_idx = 0;
        auto fn2 = [p_idx, &test_case] () mutable {
            return test_case.indexes.at(p_idx++);
        };

        REQUIRE_CALL(random_numbers, generator(1, 5))
            .RETURN(fn2);

        const tsp::Path original_path = {0, 1, 2, 3, 4, 5, 0};

        vector<tsp::Path> paths = {
            original_path
        };

        tsp::Mutator sut{
            std::move(random_numbers_mock)
        };

        constexpr int mutation_rate = 100;
        sut.mutate(paths, mutation_rate);

        REQUIRE(paths.size() == 1);

        const auto& mutated_path = paths[0];

        REQUIRE_THAT(
                mutated_path,
                Catch::Matchers::Equals(test_case.expected_path)
                );
    }

    SECTION("doesn't mutates if mutation rate is not met")
    {
        auto random_numbers_mock = std::make_unique<RandomNumbersMockInt>();

        auto& random_numbers = *random_numbers_mock;

        // Probability of mutation, returns 99 to not mutate
        auto fn1 = [] () {
            return 99;
        };

        REQUIRE_CALL(random_numbers, generator(1, 99))
            .RETURN(fn1);

        // Indexes to swap for the mutation
        auto fn2 = [] () {
            throw std::logic_error("functor should not be called");
            return 0;
        };

        REQUIRE_CALL(random_numbers, generator(1, 5))
            .RETURN(fn2);

        const tsp::Path original_path = {0, 1, 2, 3, 4, 5, 0};

        vector<tsp::Path> paths = {
            original_path
        };

        tsp::Mutator sut{
            std::move(random_numbers_mock)
        };

        constexpr int mutation_rate = 1;
        sut.mutate(paths, mutation_rate);

        REQUIRE(paths.size() == 1);

        const auto& unaltered_path = paths[0];

        REQUIRE_THAT(
                unaltered_path,
                Catch::Matchers::Equals(tsp::Path{ 0, 1, 2, 3, 4, 5, 0 })
                );
    }
}

}
