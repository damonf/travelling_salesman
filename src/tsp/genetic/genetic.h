#ifndef __GENETIC_H
#define __GENETIC_H

#include "inatural_selector.h"
#include "irandom_generator.h"
#include "graph.h"
#include "candidate.h"

#include <memory>
#include <vector>
#include <utility>

namespace tsp {

    struct PopSize {
        size_t value;
        constexpr operator size_t() const { return value; }
    };

    using Solution = std::pair<Path, Distance>;

    class Genetic {
        public:
            Genetic(
                std::unique_ptr<IRandomGenerator> random_generator
              , std::unique_ptr<INaturalSelector> natural_selector
              , PopSize pop_size
                )
            :
                random_generator_(std::move(random_generator))
              , natural_selector_(std::move(natural_selector))
              , pop_size_(pop_size)
            {}

            [[nodiscard]] Solution shortest_path(const Graph& graph) const;

        private:
            void assign_fitness(
                    std::vector<Candidate>& candidates
                    ) const;

            void sort_by_fitness(
                    std::vector<Candidate>& candidates
                    ) const;

        private:
            std::unique_ptr<IRandomGenerator> random_generator_;
            std::unique_ptr<INaturalSelector> natural_selector_;
            const PopSize pop_size_;
    };

}

#endif // __GENETIC_H


