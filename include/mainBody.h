#pragma once

#include "main.h"
#include "components/Chassis.h"
#include "components/RotationalArm.h"
#include "components/MotorGroup.h"
#include "components/PistonGroup.h"
#include "motionControl/Settler.h"
#include "components/Intake.h"
#include "components/WallStakeMech.h"
#include "components/Clamp.h"
#include "components/Doinker.h"
#include "components/EchoHang.h"
#include "motionControl/PID.h"
#include "motionControl/Odometry.h"
#include "motionControl/Odom.h"
#include "motionControl/Motion.h"
#include "motionControl/MotionAlgorithms.h"
#include "utility/Path.h"
#include "PathStorage/testPath.h"

#include "autons/negativeBlueElims.h"
#include "autons/negativeBlueQuals.h"
#include "autons/negativeRedElims.h"
#include "autons/negativeRedQuals.h"
#include "autons/positiveBlueElims.h"
#include "autons/positiveRedQuals.h"
#include "autons/positiveRedElims.h"
#include "autons/skills.h"
#include "autons/soloAWPBlue.h"
#include "autons/soloAWPRed.h"

void auton();
void driverControl();