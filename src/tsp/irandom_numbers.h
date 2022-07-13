#ifndef __IRANDOM_NUMBERS_H
#define __IRANDOM_NUMBERS_H

#include <functional>

namespace tsp {

    template<class T>
    class IRandomNumbers {
        public:
            virtual ~IRandomNumbers() noexcept = default;

            [[nodiscard]] virtual std::function<T ()> generator(T start, T end) const = 0;
    };

}

#endif // __IRANDOM_NUMBERS_H
