#ifndef __CANDIDATE_H
#define __CANDIDATE_H

#include "graph.h"

#include <utility>
#include <vector>

namespace tsp {

    class Candidate {
        public:
            Candidate(
                    Path path
                  , Distance path_len
                    )
                :
                    path_{std::move(path)}
                  , path_len_{path_len}
                  , fitness_{0.0}
                {}

            [[nodiscard]] const Path& path() const {
                return path_;
            }

            [[nodiscard]] Distance path_len() const {
                return path_len_;
            }

            [[nodiscard]] double fitness() const {
                return fitness_;
            }

            void fitness(double fitness) {
                fitness_ = fitness;
            }

        private:
            Path path_;
            Distance path_len_;
            double fitness_;
    };

}

#endif // __CANDIDATE_H

