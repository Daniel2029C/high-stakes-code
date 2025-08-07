#include "autons/positiveRedQuals.h"


void positiveRedQuals(vex::task& lbResetTask, vex::task& colorSortTask, vex::task& colorStopTask, Odometry& odometry, MotorGroup& intakeMotors, Intake& intake, MotorGroup& lbMotors, WallStakeMech& ladyBrown, Motion& motion) {
        odometry.setPos(0, 0);
        odometry.setHeading(-71);
        imu.setRotation(-71, vex::deg);
        lbMotors.setPosition(0);
        motion.turnHeading(-71, 0, 0, 0, 0);
        lbResetTask.resume();
    
        intakeMotors.spin(8.5);
        colorStopTask.resume();
    motion.moveDist(0.8, 1, 1000);
    while (!intake.getDetected()) wait(10, vex::msec);
        colorStopTask.suspend();
        intakeMotors.spin(1.2);
    motion.moveDist(-0.4, 1, 1000);
    motion.turnHeading(-150, 2, 0, 1, 1000);
    motion.moveDist(-2.7, 0.6, 2000);
        clamp = true;
        wait(130, vex::msec);
    motion.turnHeading(90, 2, 0, 0.75, 800);
        colorSortTask.resume();
    motion.moveDist(2, 1, 2000);
    motion.moveDist(-2.65, 0.7, 2000);
    motion.turnHeading(135, 2, 0, 1, 1000);
    motion.moveDist(2.7, 1, 1000);
    motion.moveDist(1.8, 1, 800);
        drivetrain.spin(vex::fwd, 9, vex::volt);
        wait(400, vex::msec);
    motion.moveDist(-0.72, 0.7, 2000);
    motion.turnHeading(-45, 2, 0, 1, 1000);
    motion.moveDist(4, 1, 2000);
        colorSortTask.suspend();
        intakeMotors.stop();
    motion.turnHeading(-25, 2, 0, 1, 1000);
    motion.moveDist(0.82, 1, 1000);
        doinker = true;
        wait(300, vex::msec);
    motion.moveDist(-1.8, 0.4, 2500);
        doinker = false;
        wait(100, vex::msec);
    motion.turnHeading(-40, 2, 0, 1, 400);
        colorSortTask.resume();
        ladyBrown.setResetSetpoint(1350);
        lbResetTask.resume();
    motion.moveDist(1, 1, 1000);
}