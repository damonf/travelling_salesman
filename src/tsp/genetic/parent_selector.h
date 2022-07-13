#ifndef __PARENTSELECTOR_H
#define __PARENTSELECTOR_H

#include "iparent_selector.h"
#include "irandom_numbers.h"
#include "graph.h"
#include "candidate.h"

#include <vector>
#include <memory>

namespace tsp {

    class ParentSelector : public IParentSelector {
        public:
            ParentSelector(
                    std::unique_ptr<IRandomNumbers<double>> random_numbers
                    )
                :
                    random_numbers_(std::move(random_numbers))
                {}

            [[nodiscard]] std::vector<Candidate> select(
                const std::vector<Candidate>& candidates
              , std::size_t num_parents
                ) const override;

        private:
            [[nodiscard]] std::vector<double> calc_points(
                    const std::vector<Candidate>& candidates
                  , std::size_t num_parents
                    ) const;

            [[nodiscard]] static std::vector<Candidate> get_parents(
                    const std::vector<Candidate>& candidates
                  , const std::vector<double>& points
                    );

        private:
            std::unique_ptr<IRandomNumbers<double>> random_numbers_;
    };

}

#endif // __PARENTSELECTOR_H

