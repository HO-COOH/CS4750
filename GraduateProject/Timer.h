#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
    std::chrono::time_point<std::chrono::steady_clock> time = std::chrono::steady_clock::now();
public:
//    struct time duration()
//    {
//        auto now = std::chrono::steady_clock::now();
//        auto seconds=std::chrono::duration_cast<std::chrono::seconds>(now-time);
//        auto millis=std::chrono::duration_cast<std::chrono::milliseconds>(now-time-seconds);
//        auto micros=std::chrono::duration_cast<std::chrono::microseconds>(now-time-seconds-millis);
//        return { static_cast<size_t>(seconds.count()), static_cast<unsigned short>(millis.count()), static_cast<unsigned short>(micros.count()) };
//    }
    auto duration()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-time);
    }
};

#endif // TIMER_H
