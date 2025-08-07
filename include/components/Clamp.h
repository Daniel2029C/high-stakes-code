#pragma once

#include "main.h"


class Clamp {


    private:

        vex::digital_out* clmp = nullptr;
        vex::distance* clmpSensor = nullptr;
        vex::controller* cntrlr = nullptr;
        float clampSensorRange = 0;
        bool prevPressing = false, clampState = false, prevDetected = false;

    public:

        Clamp(vex::digital_out* clmp);
        Clamp(vex::digital_out* clmp, vex::distance* clmpSensor, vex::controller* cntrlr);

        void setClampSensorRange(float clampSensorRange);
        void toggleState(bool button);
        void vibrateState();

};