#include "components/Doinker.h"


Doinker::Doinker(vex::digital_out* dnkr)
    //constructor for clamp without sensor

    : dnkr(dnkr)
{}


void Doinker::toggleState(bool button) {
    //toggles clamp between on and off

    if (!prevPressing && button && !dnkrState) {
        dnkr->set(true);
        dnkrState = true;
    }
    else if (!prevPressing && button && dnkrState) {
        dnkr->set(false);
        dnkrState = false;
    }

    prevPressing = button;
}