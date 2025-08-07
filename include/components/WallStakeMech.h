#pragma once

#include "main.h"
#include "components/MotorGroup.h"
#include "motionControl/PID.h"
#include "utility/Misc.h"


class WallStakeMech {


    private:

        MotorGroup* motorGroup = nullptr;
        PID* pid = nullptr;
        vex::digital_out* hangClamp = nullptr;
        float resetSetpoint = 0, mogoIntakePosition = 0, stakeIntakePosition = 0, stakeScorePosition = 0, hangPosition = 0, feedforward = 0;
        bool prevPressing = false, prevStopped = false, prevIntake = false, fwd = true;
        int stageState = 0;

        void updateStatusOne(bool button1, bool button2);
        void updateStatusTwo(bool button1, bool button2);
        void updateStatusThree(bool button1, bool button2);
        void updateStatusEcho(bool upButton, bool downButton, bool intakeButton, bool hangButton);

    
    public:

        WallStakeMech(MotorGroup* motorGroup, PID* pid, float feedforward = 0);

        void setMogoIntakePosition(float mogoIntakePosition);
        void setStakeIntakePosition(float stakeIntakePosition);
        void setStakeScorePosition(float stakeScorePosition);
        void setHangPosition(float hangPosition);
        void setResetSetpoint(float resetSetpoint);
        void setHangClampPiston(vex::digital_out* hangClamp);
        void reset(bool button1, bool button2, bool intakeButton = false, bool hangButton = false, int config = 3);
        void resetAuto();
        void scoreOnce();
        void scoreTwice();
        int getStage();
        float getHangPosition();
};