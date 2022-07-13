#include "brute_force.h"

#include <algorithm>
#include <numeric>
#include <stdexcept>

namespace tsp {

Solution BruteForce::shortest_path(const Graph& graph) const {

    const auto count = graph.num_vertices();

    if (count < 2) {
        throw std::logic_error("graph must have 2 or more vertices");
    }

    // Create initial path that starts and ends at vertex 0
    Path path(count + 1, 0);
    const auto p1 = path.begin() + 1;
    const auto p2 = path.end() - 1;
    std::iota(p1, p2, 1);

    Solution shortest_path({}, Graph::NoEdgeVal);

    do {
        if (const auto len = graph.length(path); len < shortest_path.second) {
            shortest_path = Solution(path, len);
        }
    }
    while (std::next_permutation(p1, p2));

    return shortest_path;
}

}
