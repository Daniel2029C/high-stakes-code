#pragma once

#include "main.h"
#include "components/MotorGroup.h"
#include "components/WallStakeMech.h"
#include "utility/Misc.h"


struct EchoHangComponents {

    MotorGroup* driveMotors = nullptr;
    vex::motor* liftMotor = nullptr;
    vex::digital_out* ptoPiston = nullptr;
    vex::digital_out* hangClamp = nullptr;

    EchoHangComponents(MotorGroup* driveMotors, vex::motor* liftMotor, vex::digital_out* ptoPiston, vex::digital_out* hangClamp)
        : driveMotors(driveMotors)
        , liftMotor(liftMotor)
        , ptoPiston(ptoPiston)
        , hangClamp(hangClamp)
    {}
};


class EchoHang {


    private:

        EchoHangComponents* components = nullptr;
        float hangExtendedPosition = 0;


    public:

        EchoHang(EchoHangComponents* components, float hangExtendedPosition);
        
        void hangMacro();
};