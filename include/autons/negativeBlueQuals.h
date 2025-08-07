#pragma once

#include "main.h"
#include "components/Intake.h"
#include "components/MotorGroup.h"
#include "components/WallStakeMech.h"
#include "motionControl/Motion.h"
#include "motionControl/Odometry.h"
#include "motionControl/PID.h"
#include "utility/Misc.h"
#include "utility/Pose.h"
#include "utility/Units.h"


void negativeBlueQuals(vex::task& lbResetTask, vex::task& colorSortTask, Odometry& odometry, MotorGroup& intakeMotors, MotorGroup& lbMotors, WallStakeMech& ladyBrown, Motion& motion);