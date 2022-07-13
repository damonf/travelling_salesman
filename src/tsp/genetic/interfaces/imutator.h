#ifndef __IMUTATOR_H
#define __IMUTATOR_H

#include "graph.h"
#include "candidate.h"

#include <stddef.h>

namespace tsp {

    class IMutator {
        public:
            virtual ~IMutator() noexcept = default;

            virtual void mutate(
                    std::vector<Path>& paths
                    ,size_t mutation_rate
                    ) const = 0;
    };

}

#endif // __IMUTATOR_H
