#pragma once

#include "main.h"


class Timer {


    private:

        static uint64_t timer;

    
    public:

        static void resetTimer();
        static uint64_t getTime();
};