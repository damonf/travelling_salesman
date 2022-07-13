#ifndef __RANDOM_GENERATOR_H
#define __RANDOM_GENERATOR_H

#include "irandom_generator.h"
#include "graph.h"
#include "candidate.h"

#include <stddef.h>

namespace tsp {

    class RandomGenerator : public IRandomGenerator {
        public:
            [[nodiscard]] std::vector<Candidate> candidates(
                    const Graph& graph
                  , size_t num
            ) const override;
    };

}

#endif // __RANDOM_GENERATOR_H

