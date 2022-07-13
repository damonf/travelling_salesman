#include "breeder.h"

#include <cassert>

namespace tsp {

    std::vector<Path> Breeder::breed(
            const std::vector<Candidate>& parents
            ,size_t num_children
            ) const {

        // Implementation of 2 points crossover:
        // https://en.wikipedia.org/wiki/Crossover_(genetic_algorithm)

        std::vector<Path> children;
        children.reserve(num_children);

        const auto num_parents = parents.size();
        assert(num_parents > 1);

        auto parent_fn = random_numbers_->generator(0, num_parents - 1);

        const auto path_len = parents.at(0).path().size();
        assert(path_len > 2);

        // Choose 2 random cut points, which we use the cut the half open
        // range [cut1, cut2) from the first parent.
        // Note: Our paths must always have 0 at start and end.
        auto cut_fn = random_numbers_->generator(1, path_len - 1);

        while (children.size() < num_children) {

            auto child_path = make_child(parent_fn, cut_fn, parents, path_len);
            children.push_back(std::move(child_path));
        }

        return children;
    }

    Path Breeder::make_child(
            std::function<size_t ()>& parent_fn
            ,std::function<size_t ()>& cut_fn
            ,const std::vector<Candidate>& parents
            ,size_t path_len
            ) const {

        auto [parent1, parent2] = get_parents(parent_fn, parents); 
        auto [cut1, cut2] = get_cut_points(cut_fn);

        Path child_path(path_len, 0);

        // copy a slice from first parent
        for (auto i = cut1; i < cut2; i++) {
            child_path.at(i) = parent1.path().at(i);
        }

        // copy the rest from the second parent 
        auto src = cut2;
        auto dst = cut2;
        const auto num_to_copy = path_len - 2;

        for (size_t i = 0; i < num_to_copy; i++) {

            if (src > path_len - 2) {
                src = 1;
            }
            if (dst > path_len - 2) {
                dst = 1;
            }

            auto elem = parent2.path().at(src);

            // if its not already there, copy to child
            const auto start = child_path.cbegin() + cut1;
            const auto end = child_path.cbegin() + cut2; 

            if (std::find(start, end, elem) == end) {
                child_path.at(dst) = elem;
                dst += 1;
            }

            src += 1;
        }

        return child_path;
    }

    Breeder::Parents Breeder::get_parents(
            const std::function<size_t ()>& selector
            ,const std::vector<Candidate>& parents
            ) {

        const auto p1 = selector();
        auto p2 = selector();

        if (p1 == p2) {
            p2 = (p2 + 1) % parents.size();
        }

        const auto& parent1 = parents.at(p1);
        const auto& parent2 = parents.at(p2);

        return std::tie(parent1, parent2);
    }

    std::pair<size_t, size_t> Breeder::get_cut_points(
            const std::function<size_t ()>& selector
            ) const {

        auto cut1 = selector();
        auto cut2 = selector();

        if (cut1 > cut2) {
            std::swap(cut1, cut2);
        }

        if (cut1 == cut2) {
            if (cut1 > 1) {
                cut1 -= 1;
            }
            else {
                cut2 += 1;
            }
        }

        return std::make_pair(cut1, cut2);
    }
}
