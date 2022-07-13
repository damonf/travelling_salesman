#include "mutator.h"

#include <stdexcept>
#include <cassert>

namespace tsp {

void Mutator::mutate(
        std::vector<Path>& paths
        ,size_t mutation_rate
        ) const {

    if (paths.empty()) {
        return;
    }

    const auto path_len = paths[0].size();

    if (path_len < 3) {
        throw std::logic_error("path_len must be > 2");
    }

    const auto get_prob = random_numbers_->generator(1, 99);
    const auto get_index = random_numbers_->generator(1, path_len - 2);

    for (auto& path: paths) {

        const auto r = get_prob();

        if (r < mutation_rate) {

            const auto idx1 = get_index();
            auto idx2 = get_index();

            if (idx1 == idx2) {
                idx2 = std::max(1UL, (idx2 + 1) % (path_len - 1));
            }

            assert(idx1 < path.size());
            assert(idx2 < path.size());

            std::swap(path[idx1], path[idx2]);
        }
    }
}

}
