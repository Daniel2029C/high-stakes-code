#pragma once

#include "main.h"
#include "components/MotorGroup.h"


class Intake {


    private:

        MotorGroup* motorGroup = nullptr;
        vex::motor* frontStage = nullptr;
        vex::motor* rearStage = nullptr;
        vex::optical* clr = nullptr;
        vex::distance* rng = nullptr;
        vex::controller* cntrlr = nullptr;
        bool red, colorRingDetected = false, distRingDetected = false, colorOn = true, toggleOnCooldown = false;
        float colorDelay, ringSensorRange, intakeStopPos = 0, stopDuration, count = 0;

        void updateCount();
        bool redDetected();
        bool blueDetected();
        bool redDetectedOpp();
        bool blueDetectedOpp();

    public:

        Intake(MotorGroup* motorGroup);
        Intake(MotorGroup* motorGroup, vex::optical* clr, vex::controller* cntrlr, bool red = true, float colorDelay = 40, float stopDuration = 500);
        Intake(vex::motor* frontStage, vex::motor* rearStage);
        Intake(vex::motor* frontStage, vex::motor* rearStage, vex::optical* clr, vex::controller* cntrlr, bool red = true, float colorDelay = 40, float stopDuration = 500);

        void controllerFeedbackSpin(bool button1, bool button2);
        void controllerFeedbackSpinEcho(bool button1, bool button2, int stage);
        void controllerFeedbackToggleColor(bool button);
        void runIntake(float power = 12);
        bool getDetected();
        bool getDetectedOpp();
        void toggleColor();
};