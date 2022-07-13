#ifndef __BREEDER_H
#define __BREEDER_H

#include "ibreeder.h"
#include "irandom_numbers.h"
#include "graph.h"
#include "candidate.h"

#include <memory>

namespace tsp {

    class Breeder : public IBreeder {
        public:
            Breeder(std::unique_ptr<IRandomNumbers<size_t>> random_numbers)
                :
                random_numbers_{std::move(random_numbers)}
            {}

            [[nodiscard]] std::vector<Path> breed(
                    const std::vector<Candidate>& parents
                    ,size_t num_children 
                    ) const override;

        private:
            Path make_child(
                    std::function<size_t ()>& parent_fn
                    ,std::function<size_t ()>& cut_fn
                    ,const std::vector<Candidate>& parents
                    ,size_t path_len
                    ) const;

            using Parents = std::tuple<const tsp::Candidate&, const tsp::Candidate&>;

            static Parents get_parents(
                    const std::function<size_t ()>& selector
                    ,const std::vector<Candidate>& parents
                    );

            std::pair<size_t, size_t> get_cut_points(
                    const std::function<size_t ()>& selector
                    ) const;
        private:
            std::unique_ptr<IRandomNumbers<size_t>> random_numbers_;
    };

}

#endif // __BREEDER_H
