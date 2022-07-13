#ifndef __INATURAL_SELECTOR_H
#define __INATURAL_SELECTOR_H

#include "graph.h"
#include "candidate.h"

namespace tsp {

    class INaturalSelector {
        public:
            virtual ~INaturalSelector() noexcept = default;

            [[nodiscard]] virtual std::vector<Candidate> candidates(
                    const Graph& graph
                    ,const std::vector<Candidate>& current_gen
                    ,size_t k
            ) const = 0;
    };

}

#endif // __INATURAL_SELECTOR_H

