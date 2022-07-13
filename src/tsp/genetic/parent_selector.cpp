#include "parent_selector.h"

#include <cassert>

namespace tsp {

    std::vector<Candidate> ParentSelector::select(
            const std::vector<Candidate>& candidates
          , std::size_t num_parents
            ) const {

        assert(!candidates.empty());

        // Get the parents using Stochastic universal sampling:
        // https://en.wikipedia.org/wiki/Stochastic_universal_sampling
        
        const auto points = calc_points(candidates, num_parents);
        return get_parents(candidates, points);
    }

    std::vector<double> ParentSelector::calc_points(
            const std::vector<Candidate>& candidates
          , std::size_t num_parents
            ) const {

        auto total_fitness{0.0};

        std::for_each(
                candidates.cbegin(),
                candidates.cend(),
                [&total_fitness](const auto& candidate) {
                    total_fitness += candidate.fitness();
                });

        const auto dist_between_points =
            total_fitness / static_cast<double>(num_parents);

        const auto gen_start = random_numbers_->generator(0.0, dist_between_points);

        const auto start = gen_start();

        std::vector<double> points;

        for (size_t i = 0; i < num_parents; i++) {
            auto point = start + i * dist_between_points;
            points.push_back(point);
        }

        return points;
    }

    std::vector<Candidate> ParentSelector::get_parents(
            const std::vector<Candidate>& candidates
          , const std::vector<double>& points
            ) {

        std::size_t i = 0;
        auto fitness_sum = candidates.at(0).fitness();

        std::vector<Candidate> parents;

        for (const auto point: points) {
            while (fitness_sum <= point) {
                i++;
                assert(i < candidates.size());
                fitness_sum += candidates.at(i).fitness();
            }
            parents.push_back(candidates.at(i));
        }

        return parents;
    }

}
