#ifndef __BRUTE_FORCE_H
#define __BRUTE_FORCE_H

#include "graph.h"

#include <vector>

namespace tsp {

    using Solution = std::pair<Path, Distance>;

    class BruteForce {
        public:
            [[nodiscard]] Solution shortest_path(const Graph& graph) const;
    };

}

#endif // __BRUTE_FORCE_H
