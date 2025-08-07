#include "components/Intake.h"


Intake::Intake(MotorGroup* motorGroup)
    : motorGroup(motorGroup)
{}


Intake::Intake(MotorGroup* motorGroup, vex::optical* clr, vex::controller* cntrlr, bool red, float colorDelay, float stopDuration)
    : motorGroup(motorGroup)
    , clr(clr)
    , cntrlr(cntrlr)
    , red(red)
    , colorDelay(colorDelay)
    , stopDuration(stopDuration)
{}


Intake::Intake(vex::motor* frontStage, vex::motor* rearStage)
    : frontStage(frontStage)
    , rearStage(rearStage)
{}


Intake::Intake(vex::motor* frontStage, vex::motor* rearStage, vex::optical* clr, vex::controller* cntrlr, bool red, float colorDelay, float stopDuration)
    : frontStage(frontStage)
    , rearStage(rearStage)
    , clr(clr)
    , cntrlr(cntrlr)
    , red(red)
    , colorDelay(colorDelay)
    , stopDuration(stopDuration)
{}


void Intake::updateCount() {
    
    count += 10;
    if (count == stopDuration) {
        count = 0;
        colorRingDetected= false;
    }
}


bool Intake::blueDetected() {

    return red && clr->hue() > 185 && clr->hue() < 245;
}


bool Intake::redDetected() {

    return !red && (clr->hue() > 343 || clr->hue() < 43);
}


bool Intake::blueDetectedOpp() {

    return red && (clr->hue() > 343 || clr->hue() < 43);
}


bool Intake::redDetectedOpp() {

    return !red && clr->hue() > 185 && clr->hue() < 245;
}


void Intake::controllerFeedbackSpin(bool button1, bool button2) {

    if (button1) {

        clr->setLight(vex::ledState::on);
        
        if (clr == nullptr || !colorOn) motorGroup->spin(12);
        else {

            if (blueDetected() && !colorRingDetected) {
                colorRingDetected = true;
                intakeStopPos = motorGroup->getPosition();
            }
            else if (redDetected() && !colorRingDetected) {
                colorRingDetected = true;
                intakeStopPos = motorGroup->getPosition();
            }

            (fabs(motorGroup->getPosition() - intakeStopPos) >= colorDelay && colorRingDetected) ? motorGroup->spin(-12) : motorGroup->spin(12);
            if (colorRingDetected && fabs(motorGroup->getPosition() - intakeStopPos) >= colorDelay) updateCount();
        }
    }
    else if (button2) {

        motorGroup->spin(-12);
        clr->setLight(vex::ledState::off);
    }
    else {

        motorGroup->stop();
        clr->setLight(vex::ledState::off);
    }
}


void Intake::controllerFeedbackSpinEcho(bool button1, bool button2, int stage) {

    if (button1) {
        
        frontStage->spin(vex::fwd, 12, vex::volt);
        if (clr == nullptr) (stage == 0) ? rearStage->spin(vex::fwd, 12, vex::volt) : rearStage->spin(vex::fwd, -12, vex::volt);
        else {

            if (redDetected() && !colorRingDetected && stage == 0) colorRingDetected = true;
            else if (blueDetected() && !colorRingDetected && stage == 0) colorRingDetected = true;

            bool stoppingRingColor = count > colorDelay && colorRingDetected;

            if (stoppingRingColor && stage == 0) {
                frontStage->spin(vex::fwd, -12, vex::volt);
                rearStage->spin(vex::fwd, -12, vex::volt);
            }
            else if (stage == 0) {
                frontStage->spin(vex::fwd, 12, vex::volt);
                rearStage->spin(vex::fwd, 12, vex::volt);
            }
            else {
                frontStage->spin(vex::fwd, 12, vex::volt);
                rearStage->spin(vex::fwd, -12, vex::volt);
            }

            if (colorRingDetected) updateCount();
        }
    }
    else if (button2) {
        frontStage->spin(vex::fwd, -12, vex::volt);
        (stage == 0) ? rearStage->spin(vex::fwd, -12, vex::volt) : rearStage->spin(vex::fwd, 12, vex::volt);
    }
    else {
        frontStage->stop();
        rearStage->stop();
    };
}


void Intake::controllerFeedbackToggleColor(bool button) {
   
    if (!toggleOnCooldown && button) {
        colorOn = !colorOn;
        cntrlr->rumble("-");
    }
    
    toggleOnCooldown = button;
}


void Intake::runIntake(float power) {

    if ((redDetected() || blueDetected()) && !colorRingDetected) {
        colorRingDetected = true;
        intakeStopPos = motorGroup->getPosition();
    }

    (fabs(motorGroup->getPosition() - intakeStopPos) >= colorDelay && colorRingDetected) ? motorGroup->spin(-12) : motorGroup->spin(12);
    if (colorRingDetected && fabs(motorGroup->getPosition() - intakeStopPos) >= colorDelay) updateCount();
}


bool Intake::getDetected() {

    if ((redDetectedOpp() || blueDetectedOpp()) && clr->isNearObject()) return true;

    return false;
}


bool Intake::getDetectedOpp() {

    if (clr->isNearObject()) return true;

    return false;
}


void Intake::toggleColor() {
    colorOn = !colorOn;
}