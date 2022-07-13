#ifndef __STOP_WATCH_H
#define __STOP_WATCH_H

#include <chrono>

class StopWatch
{
    public:
        StopWatch()
            :
                start_{std::chrono::high_resolution_clock::now()}
        {}

        // Returns elapsed milliseconds
        long elapsed() const {
            return std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::high_resolution_clock::now() - start_).count();
        }

    private:
        const std::chrono::_V2::system_clock::time_point start_;
};

#endif

