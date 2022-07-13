#include "random_generator.h"
#include "candidate.h"

#include <random>
#include <numeric>

namespace tsp {

    std::vector<Candidate> RandomGenerator::candidates(
            const Graph& graph
          , const size_t num) const {

        const auto count = graph.num_vertices();

        if (count < 2) {
            throw std::logic_error("graph must have 2 or more vertices");
        }

        // Create initial path that starts and ends at vertex 0
        // and keep shuffling the vertices (except start and end)
        // to generate new paths.
        Path path(count + 1, 0);
        const auto p1 = path.begin() + 1;
        const auto p2 = path.end() - 1;
        std::iota(p1, p2, 1);

        std::mt19937_64 urbg{ std::random_device{}() };

        std::vector<Candidate> candidates;
        candidates.reserve(num);

        while (candidates.size() < num) {
            std::shuffle(p1, p2, urbg);

            auto len = graph.length(path);

            // only keep valid paths
            if (len != Graph::NoEdgeVal) {
                candidates.emplace_back(path, len);
            }
        }

        return candidates;
    }

}


