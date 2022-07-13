#include "random_numbers.h"

#include <catch2/catch.hpp>

#include <vector>
#include <algorithm>

using namespace tsp;

TEST_CASE("random_numbers tests", "[random_numbers]")
{

    SECTION("random_numbers tests with double", "[random_numbers]")
    {
        const RandomNumbers<double> sut;

        const auto generator = sut.generator(0.0, 10.0);

        std::vector<double> nums;

        for (auto i = 0; i < 100; i++) {
            auto num = generator();
            nums.push_back(num);
        }

        auto in_range = std::all_of(
                nums.cbegin(),
                nums.cend(),
                [](const auto& n) {
                    return n >= 0.0 && n < 10.0; // condition is < for double
                });
    
        REQUIRE(in_range);
    }
    
    SECTION("random_numbers tests with int", "[random_numbers]")
    {
        const RandomNumbers<int> sut;

        const auto generator = sut.generator(0, 10);
    
        std::vector<int> nums;

        for (auto i = 0; i < 100; i++) {
            auto num = generator();
            nums.push_back(num);
        }

        auto in_range = std::all_of(
                nums.cbegin(),
                nums.cend(),
                [](const auto& n) {
                    return n >= 0 && n <= 10; // condition is <= for int
                });

        REQUIRE(in_range);
    }

}
