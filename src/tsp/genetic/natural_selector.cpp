#include "natural_selector.h"
#include "candidate.h"

#include <cmath>
#include <stdexcept>

namespace tsp {

    std::vector<Candidate> NaturalSelector::candidates(
            const Graph& graph
          , const std::vector<Candidate>& current_gen
          , size_t pop_size
            ) const {

        std::vector<Candidate> next_gen;
        next_gen.reserve(pop_size);

        elitism(next_gen, current_gen);

        // Select parents
        auto parent_count = (current_gen.size() + 1) / 2;
        auto parents = parent_selector_->select(current_gen, parent_count);

        // Generate child paths
        if (next_gen.size() > pop_size) {
            throw std::logic_error("requested pop_size is too small");
        }

        const auto child_count = pop_size - next_gen.size();
        auto child_paths = breeder_->breed(parents, child_count);

        // mutate child paths
        mutator_->mutate(child_paths, mutation_rate_);

        // Create candidates from child paths and add to next_gen
        for (auto& child_path: child_paths) {
            auto len = graph.length(child_path);
            next_gen.emplace_back(std::move(child_path), len);
        }

        return next_gen;
    }

    void NaturalSelector::elitism(
            std::vector<Candidate>& next_gen
          , const std::vector<Candidate>& current_gen
            ) const {

        // select top (sorted) candidates
        const auto num = static_cast<int>(
                std::ceil(
                    static_cast<double>(current_gen.size())
                    * elite_percent_
                    )
                );

        next_gen.insert(
                next_gen.begin()
              , current_gen.cbegin()
              , current_gen.cbegin() + num
                );
    }
}
