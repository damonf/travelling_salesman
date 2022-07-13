#include "natural_selector.h"
#include "iparent_selector.h"
#include "breeder.h"
#include "mutator.h"

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp> 

using namespace tsp;
using trompeloeil::_;

namespace natural_selector_tests {

// Mocks
class ParentSelectorMock : public IParentSelector {
    public:
        MAKE_CONST_MOCK2(
                select,
                std::vector<Candidate>(
                    const std::vector<Candidate>& candidates
                    ,std::size_t num_to_keep
                    )
                );
};

class BreederMock : public IBreeder {
    public:
        MAKE_CONST_MOCK2(
                breed,
                std::vector<Path>(
                    const std::vector<Candidate>& parents
                    ,size_t k
                    )
                );
};

class MutatorMock : public IMutator {
    public:
        MAKE_CONST_MOCK2(
                mutate,
                void(
                    std::vector<Path>& paths
                    ,size_t mutation_rate
                    )
                );
};

TEST_CASE("natural_selector tests", "[natural_selector]")
{
    SECTION("elite candidates are added to the result")
    {
        trompeloeil::sequence seq;

        auto parent_selector_mock = std::make_unique<ParentSelectorMock>();
        auto breeder_mock = std::make_unique<BreederMock>();
        auto mutator_mock = std::make_unique<MutatorMock>();

        // Need to get a ref to the underlying mock object so
        // we can configure it.
        // Note: mocks have no copy or move ctors
        auto& parent_selector = *parent_selector_mock;
        auto& breeder = *breeder_mock;
        auto& mutator = *mutator_mock;

        // don't need any parents
        REQUIRE_CALL(parent_selector, select(_, _))
            .IN_SEQUENCE(seq)
            .RETURN(std::vector<Candidate>{});

        // add no children
        REQUIRE_CALL(breeder, breed(_, _))
            .IN_SEQUENCE(seq)
            .RETURN(std::vector<Path>{});

        // do nothing
        REQUIRE_CALL(mutator, mutate(_, _))
            .IN_SEQUENCE(seq);

        const NaturalSelector sut{
            std::move(parent_selector_mock),
            std::move(breeder_mock),
            std::move(mutator_mock),
        };

        // any graph will do
        tsp::Graph graph(
                "0  2 1\n"
                "1  0 2\n"
                "2  1 0\n"
                );

        // candidates are sorted, most fit first
        std::vector<Candidate> current_gen = {
            {{0, 1, 2, 3, 4, 0}, 1.0}, // most fit
            {{0, 2, 1, 3, 4, 0}, 2.0},
            {{0, 2, 3, 1, 4, 0}, 3.0},
            {{0, 2, 3, 4, 1, 0}, 4.0},
            {{0, 3, 2, 4, 1, 0}, 5.0},
            {{0, 3, 4, 2, 1, 0}, 6.0},
            {{0, 3, 4, 1, 2, 0}, 7.0},
            {{0, 4, 3, 1, 2, 0}, 8.0},
            {{0, 4, 1, 3, 2, 0}, 9.0},
            {{0, 4, 1, 2, 3, 0}, 10.0},
        };

        constexpr size_t pop_size = 10;

        auto candidates = sut.candidates(
                graph,
                current_gen,
                pop_size
                );

        REQUIRE(candidates.size() == 1);
        REQUIRE(candidates[0].path_len() == 1.0);
    }

    //           0
    //          /|\
    //        5/ | \1
    //        / 4|  \
    //       / 2 |   \
    //      3---------1
    //       \   |   /
    //        \  |  /
    //        3\ | /6
    //          \|/
    //           2
    //
    //     0   1   2   3
    //   -----------------
    // 0 | 0 | 1 | 4 | 5 |
    //   |---------------|
    // 1 | 1 | 0 | 6 | 2 |
    //   |---------------|
    // 2 | 4 | 6 | 0 | 3 | 
    //   |---------------|
    // 3 | 5 | 2 | 3 | 0 |
    //   -----------------
    //
    SECTION("children are added to the result")
    {
        trompeloeil::sequence seq;

        auto parent_selector_mock = std::make_unique<ParentSelectorMock>();
        auto breeder_mock = std::make_unique<BreederMock>();
        auto mutator_mock = std::make_unique<MutatorMock>();

        // Need to get a ref to the underlying mock object so
        // we can configure it.
        // Note: mocks have no copy or move ctors
        auto& parent_selector = *parent_selector_mock;
        auto& breeder = *breeder_mock;
        auto& mutator = *mutator_mock;

        // don't need any parents
        REQUIRE_CALL(parent_selector, select(_, _))
            .IN_SEQUENCE(seq)
            .RETURN(std::vector<Candidate>{});

        REQUIRE_CALL(breeder, breed(_, _))
            .IN_SEQUENCE(seq)
            .RETURN(std::vector<Path>{
                    {0, 3, 2, 1, 0}, // len 15
                    {0, 3, 1, 2, 0}, // len 17
                    });

        // do nothing
        REQUIRE_CALL(mutator, mutate(_, _))
            .IN_SEQUENCE(seq);

        const NaturalSelector sut{
            std::move(parent_selector_mock),
            std::move(breeder_mock),
            std::move(mutator_mock),
        };

        tsp::Graph graph(
                "0 1 4 5\n"
                "1 0 6 2\n"
                "4 6 0 3\n"
                "5 2 3 0\n"
                );

        // Candidates must be sorted, most fit first
        std::vector<Candidate> current_gen = {
            {{0, 1, 3, 2, 0}, 10.0},
            {{0, 2, 3, 1, 0}, 10.0},
            //{{0, 1, 2, 3, 0}, 15.0},
            //{{0, 3, 2, 1, 0}, 15.0},
            //{{0, 3, 1, 2, 0}, 17.0},
            //{{0, 2, 1, 3, 0}, 17.0},
        };

        constexpr size_t pop_size = 3;

        auto candidates = sut.candidates(
                graph,
                current_gen,
                pop_size
                );

        REQUIRE(candidates.size() == 3);
        REQUIRE(candidates[0].path_len() == 10.0);
        REQUIRE(candidates[1].path_len() == 15.0);
        REQUIRE(candidates[2].path_len() == 17.0);
    }

    SECTION("throws if pop_size is too small")
    {
        trompeloeil::sequence seq;

        auto parent_selector_mock = std::make_unique<ParentSelectorMock>();
        auto breeder_mock = std::make_unique<BreederMock>();
        auto mutator_mock = std::make_unique<MutatorMock>();

        // Need to get a ref to the underlying mock object so
        // we can configure it.
        // Note: mocks have no copy or move ctors
        auto& parent_selector = *parent_selector_mock;

        // don't need any parents
        REQUIRE_CALL(parent_selector, select(_, _))
            .IN_SEQUENCE(seq)
            .RETURN(std::vector<Candidate>{});

        const NaturalSelector sut{
            std::move(parent_selector_mock),
            std::move(breeder_mock),
            std::move(mutator_mock),
        };

        // any graph will do
        tsp::Graph graph(
                "0  2 1\n"
                "1  0 2\n"
                "2  1 0\n"
                );

        // 100 candidates, doesn't matter what they are
        constexpr auto num_candidates = 100;
        std::vector<Candidate> current_gen;
        current_gen.reserve(num_candidates);
        for (auto i = 0; i < num_candidates; i++) {
            current_gen.push_back({{}, static_cast<double>(i)});
        }

        constexpr size_t pop_size = 5;

        REQUIRE_THROWS_AS(
            sut.candidates(
                graph,
                current_gen,
                pop_size
                ),
            std::logic_error 
        );
    }
}

}
