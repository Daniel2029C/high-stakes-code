#include "autons/negativeBlueQuals.h"


void negativeBlueQuals(vex::task& lbResetTask, vex::task& colorSortTask, Odometry& odometry, MotorGroup& intakeMotors, MotorGroup& lbMotors, WallStakeMech& ladyBrown, Motion& motion) {
        odometry.setPos(0, 0);
        odometry.setHeading(-130);
        imu.setRotation(-130, vex::deg);
        lbMotors.setPosition(350);
        motion.turnHeading(-130, 0, 0, 0, 0);
        lbResetTask.resume();
        ladyBrown.setResetSetpoint(1960);
    while (fabs(lbMotors.getPosition()) < 1900) wait(10, vex::msec);
    motion.moveDist(-0.4, 1, 600);
        ladyBrown.setResetSetpoint(0);
    motion.turnHeading(-170, 2, 0, 1, 2000);
    motion.moveDist2(-1, 1, 1200);
    motion.moveDist(-1.75, 0.6, 1200);
        clamp = true;
        wait(130, vex::msec);
        colorSortTask.resume();
    motion.turnHeading(47, 2, 0, 1, 1200);
    motion.moveDist(1.65, 1, 1000);
    motion.turnHeading(75, 2, 0, 1, 1000);
    motion.moveDist(0.6, 0.55, 1200);
    motion.turnHeading(180, 2, 0, 1, 800);
    motion.moveDist(0.75, 1, 700);
    motion.turnHeading(-145, 2, 0, 1, 400);
    motion.moveDist(1.75, 1, 1200);
    motion.turnHeading(135, 2, 0, 1, 1000);
    motion.moveDist2(2, 1, 1000);
    motion.moveDist2(1.15, 0.4, 1200);
        wait(300, vex::msec);
    motion.moveDist(-1.6, 1, 1200);
        doinker = true;
    motion.turnHeading(-90, 2, 0, 1, 1000);
        doinker = false;
    motion.moveDist(2.8, 1, 2000);
    motion.moveDist(2.8, 0.6, 1500);
        ladyBrown.setResetSetpoint(1550);
    motion.turnHeading(34, 2, 0, 1, 1200);
    motion.moveDist(2.2, 0.55, 10000);
        lbResetTask.suspend();
        colorSortTask.suspend();
        intakeMotors.stop();
}