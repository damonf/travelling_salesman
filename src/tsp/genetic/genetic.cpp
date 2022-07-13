#include "genetic.h"
#include "candidate.h"

#include <algorithm>
#include <cmath>

namespace tsp {

    Solution Genetic::shortest_path(const Graph& graph) const {

        // Generate initial random population of candidates
        auto candidates = random_generator_->candidates(graph, pop_size_);

        assign_fitness(candidates);
        sort_by_fitness(candidates);

        auto top_fitness = candidates[0].fitness();
        const auto same_fitness = [&top_fitness](const auto& c) {
            return c.fitness() == top_fitness;
        };

        const auto limit = (pop_size_ + 1) / 2;

        while (static_cast<size_t>(
                   std::count_if(
                   candidates.cbegin()
                 , candidates.cend()
                 , same_fitness
                   )
               ) < limit) {

            candidates = natural_selector_->candidates(
                    graph
                  , candidates
                  , pop_size_
                    );

            assign_fitness(candidates);
            sort_by_fitness(candidates);

            top_fitness = candidates[0].fitness();
        }

        // return fittest candidate
        auto fittest = candidates[0];

        return { fittest.path(), fittest.path_len() };
    }

    void Genetic::assign_fitness(std::vector<Candidate>& candidates) const {

        auto total_path_len{0.0};

        std::for_each(
                candidates.cbegin(),
                candidates.cend(),
                [&total_path_len](const auto& candidate) {
                    total_path_len += candidate.path_len();
                });

        for (auto& candidate : candidates) {
            const auto fitness = total_path_len / candidate.path_len();
            candidate.fitness(fitness);
        }
    }

    // Sort from most fit to least fit
    void Genetic::sort_by_fitness(std::vector<Candidate>& candidates) const {
        std::sort(
                candidates.begin(),
                candidates.end(),
                [](const auto& lhs, const auto& rhs) {
                    return lhs.fitness() > rhs.fitness();
                });
    }
}

