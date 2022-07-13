#ifndef __IBREEDER_H
#define __IBREEDER_H

#include "graph.h"
#include "candidate.h"

namespace tsp {

    class IBreeder {
        public:
            virtual ~IBreeder() noexcept = default;

            [[nodiscard]] virtual std::vector<Path> breed(
                    const std::vector<Candidate>& parents
                    ,size_t k
                    ) const = 0;
    };

}

#endif // __IBREEDER_H

