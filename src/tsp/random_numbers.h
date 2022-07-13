#ifndef __RANDOM_NUMBERS_H
#define __RANDOM_NUMBERS_H

#include "irandom_numbers.h"

#include <random>
#include <functional>

namespace tsp {

    template<class T>
    class RandomNumbers : public IRandomNumbers<T> {
        public:
            [[nodiscard]] std::function<T ()> generator(T start, T end) const override {

                auto generator = get_distribution(start, end);
                std::mt19937_64 rng{std::random_device{}()};

                return [generator, rng ] () mutable {
                    return generator(rng);
                };
            }

        private:
            [[nodiscard]] auto get_distribution(T start, T end) const {

                if constexpr(std::is_floating_point_v<T>) {
                    return std::uniform_real_distribution<T>{ start, end };
                }
                else if constexpr(std::is_integral_v<T>) {
                    return std::uniform_int_distribution<T>{ start, end };
                }

                static_assert(
                        std::is_floating_point_v<T> || std::is_integral_v<T>,
                        "invalid type"
                        );
            }
    };

}

#endif // __RANDOM_NUMBERS_H




