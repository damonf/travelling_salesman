#ifndef __IPARENTSELECTOR_H
#define __IPARENTSELECTOR_H

#include "graph.h"
#include "candidate.h"

namespace tsp {

    class IParentSelector {
        public:
            virtual ~IParentSelector() noexcept = default;

            [[nodiscard]] virtual std::vector<Candidate> select(
                    const std::vector<Candidate>& candidates
                    ,std::size_t num_parents
                    ) const = 0;
    };

}

#endif // __IPARENTSELECTOR_H
