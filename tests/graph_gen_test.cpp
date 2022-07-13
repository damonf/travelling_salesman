#include "graph_gen.h"

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp> 

using namespace tsp;
using trompeloeil::_;

namespace graph_gen_test {

// Mocks
class RandomNumbersMock : public IRandomNumbers<size_t> {
    public:
        MAKE_CONST_MOCK2(
                generator,
                std::function<size_t ()>(
                    size_t start
                    ,size_t end
                    )
                );
};

TEST_CASE("graph_gen test", "[graph_gen]")
{
    SECTION("generates a graph with specified number of nodes")
    {
        auto random_numbers_mock = std::make_unique<RandomNumbersMock>();

        const auto& random_numbers = *random_numbers_mock;

        // "random" number will always be 1
        auto fn1 = [] () {
            return 1;
        };

        REQUIRE_CALL(random_numbers, generator(1, 100))
            .RETURN(fn1);

        tsp::GraphGen sut{std::move(random_numbers_mock)};
        
        const auto result = sut.Generate(5);

        const char* expected =
            "0 1 1 1 1 \n"
            "1 0 1 1 1 \n"
            "1 1 0 1 1 \n"
            "1 1 1 0 1 \n"
            "1 1 1 1 0 \n"
            ;

        REQUIRE(result == expected);
    }
}

}
