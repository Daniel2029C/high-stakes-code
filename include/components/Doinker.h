#pragma once

#include "main.h"


class Doinker {


    private:

        vex::digital_out* dnkr = nullptr;
        bool prevPressing = false, dnkrState = false;

    public:

        Doinker(vex::digital_out* dnkr);

        void toggleState(bool button);
};