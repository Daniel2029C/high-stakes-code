#include "main.h"


vex::brain brain;

vex::controller controller = vex::controller(vex::primary);

vex::motor intake1 = vex::motor(vex::PORT20, vex::ratio6_1, true);

vex::motor lb1 = vex::motor(vex::PORT1, vex::ratio6_1, false);

vex::motor fl = vex::motor(vex::PORT8, vex::ratio6_1, true);
vex::motor fr = vex::motor(vex::PORT2, vex::ratio6_1, false);
vex::motor ml = vex::motor(vex::PORT7, vex::ratio6_1, false);
vex::motor mr = vex::motor(vex::PORT3, vex::ratio6_1, true);
vex::motor bl = vex::motor(vex::PORT9, vex::ratio6_1, true);
vex::motor br = vex::motor(vex::PORT4, vex::ratio6_1, false);

vex::motor_group leftDrivetrain = vex::motor_group(fl, ml, bl);
vex::motor_group rightDrivetrain = vex::motor_group(fr, mr, br);
vex::motor_group drivetrain = vex::motor_group(fl, fr, ml, mr, bl, br);

vex::digital_out clamp = vex::digital_out(brain.ThreeWirePort.A);
vex::digital_out intakeLift = vex::digital_out(brain.ThreeWirePort.C);
vex::digital_out doinker = vex::digital_out(brain.ThreeWirePort.B);

vex::inertial imu = vex::inertial(vex::PORT5);

vex::rotation parallel = vex::rotation(vex::PORT9, true);
vex::rotation sideways = vex::rotation(vex::PORT3, false);

vex::distance clampSensor = vex::distance(vex::PORT19);
vex::distance frontDistance = vex::distance(vex::PORT11);
vex::distance leftDistance = vex::distance(vex::PORT19);
vex::distance rightDistance = vex::distance(vex::PORT15);

vex::optical colorSensor = vex::optical(vex::PORT10);