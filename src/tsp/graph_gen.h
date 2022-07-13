#ifndef __GRAPH_GEN_H
#define __GRAPH_GEN_H

#include "irandom_numbers.h"

#include <string>
#include <sstream>
#include <memory>

namespace tsp {

    class GraphGen {
        public:
            GraphGen(std::unique_ptr<IRandomNumbers<unsigned long>> random_numbers)
                :
                random_numbers_{std::move(random_numbers)}
            {}

            std::string Generate(int num_nodes) {

                auto distance = random_numbers_->generator(MinDist, MaxDist);
                std::ostringstream graph_ss;

                for (auto x = 0; x < num_nodes; x++) {
                    write_line(x, num_nodes, distance, graph_ss);
                }

                return graph_ss.str();
            }

        private:
            static void write_line(
                    int x
                  , int len
                  , const std::function<unsigned long()>& distance
                  , std::ostringstream& oss
                  ) {

                for (auto y = 0; y < len; y++) {

                    if (y == x) {
                        oss << 0;
                    }
                    else {
                        oss << distance();
                    }

                    oss << ' ';
                }

                oss << '\n';
            }

        private:
            std::unique_ptr<IRandomNumbers<unsigned long>> random_numbers_;
            static constexpr std::size_t MinDist{1};
            static constexpr std::size_t MaxDist{100};
    };
}

#endif // __GRAPH_GEN_H
