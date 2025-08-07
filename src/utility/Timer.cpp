#include "utility/Timer.h"


uint64_t Timer::timer;

void Timer::resetTimer() {
    //starts the global timer

    timer = vex::timer::systemHighResolution();
}


uint64_t Timer::getTime() {
    //gets the global time in seconds

    return (vex::timer::systemHighResolution() - timer) / 1000000.0;
}