#pragma once


#include <vector>
#include <v5.h>
#include <v5_vcs.h>
#include <cstdio>
#include <cmath>
#include <numeric>
#include <memory>
#include <map>


extern vex::controller controller;
extern vex::motor lb1;
extern vex::motor fl;
extern vex::motor fr;
extern vex::motor ml;
extern vex::motor mr;
extern vex::motor bl;
extern vex::motor br;
extern vex::motor intake1;
extern vex::motor_group leftDrivetrain;
extern vex::motor_group rightDrivetrain;
extern vex::motor_group drivetrain;
extern vex::digital_out clamp;
extern vex::digital_out intakeLift;
extern vex::digital_out doinker;
extern vex::brain brain;
extern vex::inertial imu;
extern vex::rotation parallel;
extern vex::rotation sideways;
extern vex::distance clampSensor;
extern vex::distance frontDistance;
extern vex::distance leftDistance;
extern vex::distance rightDistance;
extern vex::optical colorSensor;
