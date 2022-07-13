#ifndef __IRANDOM_GENERATOR_H
#define __IRANDOM_GENERATOR_H

#include "graph.h"
#include "candidate.h"

#include <stddef.h>

namespace tsp {

    class IRandomGenerator {
        public:
            virtual ~IRandomGenerator() noexcept = default;

            [[nodiscard]] virtual std::vector<Candidate> candidates(
                    const Graph& graph
                  , size_t num
            ) const = 0;
    };

}

#endif // __IRANDOM_GENERATOR_H


