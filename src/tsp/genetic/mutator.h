#ifndef __MUTATOR_H
#define __MUTATOR_H

#include "imutator.h"
#include "irandom_numbers.h"
#include "graph.h"

#include <stddef.h>
#include <memory>

namespace tsp {

    class Mutator : public IMutator {
        public:
            Mutator(std::unique_ptr<IRandomNumbers<size_t>> random_numbers)
                :
                random_numbers_(std::move(random_numbers))
            {}

            void mutate(
                    std::vector<Path>& paths
                    ,size_t mutation_rate
                    ) const override;

        private:
            std::unique_ptr<IRandomNumbers<size_t>> random_numbers_;
    };

}

#endif // __MUTATOR_H 
