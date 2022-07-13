#ifndef __NATURAL_SELECTOR_H
#define __NATURAL_SELECTOR_H

#include "inatural_selector.h"
#include "iparent_selector.h"
#include "ibreeder.h"
#include "imutator.h"
#include "graph.h"
#include "candidate.h"

#include <memory>
#include <vector>
#include <utility>

namespace tsp {

    class NaturalSelector : public INaturalSelector {
        public:
            NaturalSelector(
                    std::unique_ptr<IParentSelector> parent_selector
                    ,std::unique_ptr<IBreeder> breeder
                    ,std::unique_ptr<IMutator> mutator
                    )
                :
                    parent_selector_(std::move(parent_selector))
                    ,breeder_(std::move(breeder))
                    ,mutator_(std::move(mutator))
                {}

            [[nodiscard]] std::vector<Candidate> candidates(
                    const Graph& graph
                    ,const std::vector<Candidate>& current_gen
                    ,size_t pop_size 
            ) const override;

        private:
            void elitism(
                    std::vector<Candidate>& next_gen
                    ,const std::vector<Candidate>& candidates
                    ) const;

        private:
            std::unique_ptr<IParentSelector> parent_selector_;
            std::unique_ptr<IBreeder> breeder_;
            std::unique_ptr<IMutator> mutator_;

            static inline constexpr int mutation_rate_{10}; 
            static inline constexpr double elite_percent_{0.1};
    };

}

#endif // __NATURAL_SELECTOR_H
