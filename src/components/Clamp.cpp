#include "components/Clamp.h"


Clamp::Clamp(vex::digital_out* clmp)
    //constructor for clamp without sensor

    : clmp(clmp)
{}


Clamp::Clamp(vex::digital_out* clmp, vex::distance* clmpSensor, vex::controller* cntrlr)
    //constructor for clamp with sensor

    : clmp(clmp)
    , clmpSensor(clmpSensor)
    , cntrlr(cntrlr)
{}


void Clamp::setClampSensorRange(float clampSensorRange) {
    //sets clamp sensor range

    this->clampSensorRange = clampSensorRange;
}


void Clamp::toggleState(bool button) {
    //toggles clamp between on and off

    if (!prevPressing && button && !clampState) {
        clmp->set(true);
        clampState = true;
    }
    else if (!prevPressing && button && clampState) {
        clmp->set(false);
        clampState = false;
    }

    prevPressing = button;
}


void Clamp::vibrateState() {
    //vibrates if distance sensor detects a ring in the clamp

    if (clmpSensor != nullptr) {
        
        if (clmpSensor->objectDistance(vex::inches) < clampSensorRange && !prevDetected && clampState == false) {
        
            cntrlr->rumble("-");
            prevDetected = true;
        }
        else if (clampSensor.objectDistance(vex::inches) >= clampSensorRange) prevDetected = false;
    }
}