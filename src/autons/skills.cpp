#include "autons/skills.h"


void skills(vex::task& lbResetTask, vex::task& colorSortTask, vex::task& colorStopTask, Odometry& odometry, MotorGroup& intakeMotors, MotorGroup& lbMotors, Intake& intake, WallStakeMech& ladyBrown, Motion& motion) {

    odometry.setPos(0.58, -0.445);
    odometry.setHeading(144);
    imu.setRotation(144, vex::deg);
    lbMotors.setPosition(94);

    lbResetTask.resume();
    ladyBrown.setResetSetpoint(670);
    wait(550, vex::msec);

    motion.movePose(0.369, -0.33, 142, 0, 0, -0.05, -1, 700, -1, false);
        lbResetTask.suspend();
        lbMotors.spin(-12);
        drivetrain.stop();
        wait(150, vex::msec);
    motion.turnHeading(110, 2, 0, 1, 380);
    motion.movePose(0.037, -0.183, 110, 0.1, 0, -0.35, -0.5, 2000);

    motion.moveDist(-0.3, 0.15, 150, 0.35);
        clamp = true; //picks up first mogo
    motion.moveDist(-2000, 0.15, 200, 0.15);
        wait(150, vex::msec);
        
        lbMotors.setPosition(0);
        ladyBrown.setResetSetpoint(0);
        lbResetTask.resume();
        odometry.setTrackWidths(0.09, 0.15);
        intakeMotors.spin(12);
    motion.movePose(-0.442, 1.85, -28, 1, 0, 0.65, 0.65, 2000, -1, false, 25);
    motion.movePose(-2.7, 5.465, -13, 1.75, 0.5, 0.55, 0.65, 2000, -1, false, 25);
    motion.movePose(-4.17, 7.425, 15, 0.14, 0, 0, 0.55, 2000, -1);

    motion.movePose(-2.6, 5.865, -38.5, 0, 0, -0, -0.55, 2000);
    motion.movePose(-2.454, 2.552, -147, 0.6, 0, 0.70, 0.70, 2000, 25, false);
    motion.movePose(-3.78, 0.4, 180, 0.75, 0, 0.65, 0.70, 2000, 25, false);
        intakeMotors.spin(12);
    motion.movePose(-1.75, -0.8, 70, 1.3, 0, 0, 0.65, 2000, 25);
        intakeMotors.spin(12);
    motion.movePose(-3.2, -0.9, 63, 0.2, 0, -0, -0.65, 1200);

        intakeMotors.stop();
        clamp = false; //unclamps first mogo
        wait(200, vex::msec);

        odometry.setTrackWidths(0.125, 0.225);
        ladyBrown.setResetSetpoint(140);
        intakeMotors.spin(7);
        colorStopTask.resume();
    motion.movePose(-2.962, -0.665, 36, 0.1, 0, 0.5, 0.5, 2000, 15, false);
        intakeMotors.spin(7);
    motion.movePose(-2.1, 4.18, 0, 0.5, 0, 0, 0.5, 2500, 15, true);
    motion.turnPoint(-4.2, 4.18, 2, 0, 1, 1000);
    motion.moveDist(2, 0.35, 450);
        colorStopTask.suspend();
        intakeMotors.spin(12);
    motion.push3(-3.5, false, 0.35, 1000, 0.75);
        intakeMotors.spin(-12);
        wait(150, vex::msec);
        intakeMotors.stop();
        intakeMotors.stop();
        odometry.setPos(-3.7, odometry.getPosY());
        drivetrain.stop();

        ladyBrown.scoreTwice(); //wall stake 1 and 2

        ladyBrown.setResetSetpoint(140);
    motion.moveDist(-1, 1, 2000);
        intakeMotors.spin(12);
    motion.movePose(-2.65, 7.7, -45, 1.5, 0, 0, 0.6, 2000, 21);
    motion.movePose(-0.2, 7.8, -90, 1, 0, -0, -0.7, 2000);
    motion.turnHeading(-36, 2, 0.1, 1, 800);
        intakeMotors.stop();
    motion.movePose(-3.35, 9.05, -87, 4.25, 0, 0.5, 1, 2500); //pushes goal in corner
        drivetrain.setStopping(vex::coast);
        drivetrain.stop();
        wait(100, vex::msec);
        drivetrain.setStopping(vex::hold);
        intakeMotors.spin(12);
    motion.movePose(0.65, 8.12, -90, 3, 0, -0.35, -0.5, 3000, -1);

    motion.moveDist(-0.3, 0.15, 150, 0.35);
        clamp = true; //picks up 3rd mogo
    motion.moveDist(-2000, 0.15, 200, 0.15);
        wait(120, vex::msec);

        odometry.setTrackWidths(0.09, 0.15);
    motion.moveDist(odometry.getPosX() - 0.8, 0.5, 2000, 0);
    motion.turnPoint(0.8, 10, 2, 0, 1, 1000);
        intakeMotors.spin(12);
    motion.moveDist(2, 0.35, 450);
    motion.push3(9, true, 0.3, 1200, 0.75);
    motion.moveDist(2, 0.2, 350, 0.12);
        motion.turnHeading(Misc::getHeading(false), 0, 0, 0, 0);
        odometry.setPos(odometry.getPosX(), 9.5);

        motion.moveDist(-0.415, 1, 2000);
        intakeMotors.stop();
        wait(150, vex::msec);

        drivetrain.stop();
        ladyBrown.setResetSetpoint(670); //blue alliance stake
        wait(550, vex::msec);

    motion.moveDist(-0.5, 0.5, 1000);
        ladyBrown.setResetSetpoint(0);
        intakeMotors.spin(5.5);
        colorStopTask.resume();
    motion.movePose(-1.2, 6.25, 157, 3, 0, 0.65, 0.65, 2000, 20, false);
    motion.movePose(1.2, 4.25, 135, 1.5, 0, 0.45, 0.65, 2000, -1, false); //middle of field ring
        colorStopTask.suspend();
        intakeMotors.stop();
    motion.movePose(2.8, 2.7, 135, 0, 0, 0.45, 0.45, 1000, -1, false);
        intakeMotors.spin(12);
    motion.movePose(3.1, 2.55, 135, 0.1, 0, 0.45, 0.45, 600, -1, false);
    motion.movePose(4.85, 0.65, 125, 0, 0, 0.45, 0.45, 2000, 20, false);
    motion.movePose(6.2, 0.7, 80, 0.2, 0, 0.05, 0.45, 2000, -1, false);
    motion.turnHeading(-155, 2, 0.1, 0.4, 1000);
    motion.movePose(5.5, -0.38, -155, 0.1, 0, 0, 0.7, 2000);
        wait(350, vex::msec);
    motion.movePose(6.15, -0.38, -48, 0.7, 0, -0.15, -0.7, 1200);
        intakeMotors.stop();

        clamp = false; //unclamps third mogo
        wait(200, vex::msec);

        odometry.setTrackWidths(0.125, 0.225);
    motion.movePose(5.2, 0.3, -28, 0, 0, 0, 0.65, 2000);
    motion.turnHeading(90, 2, 0.1, 1, 1000);
    motion.movePose(3.6, 0.35, 90, 0.6, 0, -0.15, -0.5, 2000, 20, false);

        motion.moveDist(-2000, 0.15, 150, 0.15);
        clamp = true; //picks up fourth mogo
        motion.moveDist(-2000, 0.15, 200, 0.15);
        wait(150, vex::msec);

        odometry.setTrackWidths(0.09, 0.15);
        intakeMotors.spin(7);
        colorStopTask.resume();
        ladyBrown.setResetSetpoint(140);
    motion.movePose(5.35, 1.943, 0, 1.5, 0, 0.5, 0.5, 2000, -1, false);
        intakeMotors.spin(7);
    motion.movePose(4.8, 4.4, -35, 0, 0, 0, 0.5, 2000);
    motion.turnPoint(6.4, 4.35, 2, 0, 1, 1000);
    motion.moveDist(2, 0.35, 450);
        colorStopTask.suspend();
        intakeMotors.spin(12);
    motion.push3(5.75, false, 0.35, 1400, 0.25);
    motion.moveDist(2, 0.35, 250, 0.35);
        intakeMotors.spin(-12);
    drivetrain.stop();
        wait(150, vex::msec);
        intakeMotors.stop();
        odometry.setPos(5.9, odometry.getPosY());

    ladyBrown.scoreOnce(); //3rd neutral stake

        intakeMotors.spin(12);
        ladyBrown.setResetSetpoint(0);
    motion.moveDist(-1, 0.4, 2000);
        colorSortTask.resume();
    motion.movePose(3.45, 6.05, -60, 0.45, 0, 0.65, 0.65, 2000, 15, false);
    motion.movePose(4.418, 6.55, 117.5, 1.2, 0, 0.65, 0.65, 2000, 12, false);
    motion.movePose(5.7, 8.15, 0, 0.9, 0, 0, 0.65, 2000, 12);
    motion.movePose(5.5, 6.9, 30, 0, 0, -0, -0.65, 2000);
    motion.movePose(5.15, 7.65, -25, 0, 0, 0.40, 0.40, 2000, -1, false);
    motion.movePose(4.5, 9.15, -25, 0, 0, 0, 0.40, 2000);
        wait(600, vex::msec);
    motion.movePose(5.65, 9.25, -135, 0.1, 0, -0.5, -1, 1200);
        colorSortTask.suspend();
        intakeMotors.stop();

        clamp = false; //unclamps fourth mogo
        wait(200, vex::msec);
        
        odometry.setTrackWidths(0.125, 0.225);
        intakeMotors.spin(-12);
    motion.movePose(5.0, 7.5, -135, 0.5, 0, 0, 0.65, 2000);
    motion.movePose(5.65, 9.25, -135, 0.1, 0, -0.5, -1, 2000);
    motion.movePose(5.0, 7.5, -135, 0.5, 0, 0, 0.65, 2000);
        intakeMotors.stop();
}