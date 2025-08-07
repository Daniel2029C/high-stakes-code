// #include "auton.h"


// Odometry odometry(0.125, 0.225, 0);

// AsymptoticGains lateralKp = AsymptoticGains(15000, 13000, 1, 1);
// AsymptoticGains angularKp = AsymptoticGains(550, 200, 28, 1.7);
// AsymptoticGains correctKp = AsymptoticGains(200, 200, 1, 1);

// PID lateralPID = PID(lateralKp, 25000, 500, 0.25, true);
// PID angularPID = PID(angularKp, 2500, 15, 5, true);
// PID correctPID = PID(correctKp, 0, 40, 0, false);

// Motion motion(
//   lateralPID,
//   angularPID,
//   correctPID,
//   odometry
// );

// vex::task odom(nullptr);
// vex::task clrSrt(nullptr);
// vex::task lbResetTask(nullptr);
// vex::task clrStp(nullptr);

// MotorGroup intakeMtrs({
//   Motor("intake1", &intake1),
// });

// Intake intakeAuto(&intakeMtrs, &colorSensor, &controller, false, 30, 200);

// MotorGroup lbMotor({
//   Motor("ladyBrown1", &lb1),
//   Motor("ladyBrown2", &lb2)
// });
// AsymptoticGains lbKpp = AsymptoticGains(0.12, 0.12, 1, 1);
// PID ladyBrownPID = PID(lbKpp, 0.02, 0.004, 120, true);
// WallStakeMech ladyB(&lbMotor, &ladyBrownPID, 0);


// void initialize() {
//   //resets the readings of all sensors and updates the drivetrain mode

//   imu.resetRotation();
//   parallel.resetPosition();
//   sideways.resetPosition();

//   drivetrain.setStopping(vex::brake);

//   motion.setUnit(foot);
//   motion.setPursuitSettings(1, 1, 0.2, 0.4, 0, 5);
//   odometry.setUnit(foot);

//   odometry.setPos(0, 0);
//   taskHandler(false);
// }


// int updateOdom() {

//   int count = 0;
  
//   while (1) {
//     uint64_t timestamp = vex::timer::systemHighResolution();

//     odometry.tick();
    
//     if (count % 10 == 0) printf("%f | %f | %f\n", odometry.getPosX(), odometry.getPosY(), Misc::getHeading(false));
//     count++;
  
//     wait((timestamp + 11000.0 - vex::timer::systemHighResolution()) / 1000.0, vex::msec);
//   }

//   return 0;
// }


// int lbReset() {

//   while (1) {
//     uint64_t timestamp = vex::timer::systemHighResolution();

//     ladyB.resetAuto();

//     wait((timestamp + 11000.0 - vex::timer::systemHighResolution()) / 1000.0, vex::msec);
//   }
// }


// int colorSort() {

//   while (1) {

//     intakeAuto.runIntake(12);

//     wait(10, vex::msec);
//   }
// }


// int colorStop() {
  
//   while (1) {

//     if (intakeAuto.getDetected()) intakeMtrs.stop();

//     wait(10, vex::msec);
//   }
// }


// void scoreOnce() {
  
//   int timecount = 0;

//   ladyB.setResetSetpoint(650);

//   while (timecount < 650 && lbMotor.getPosition() < 575) {
//     timecount += 10;
    
//     wait(10, vex::msec);
//   }
// }


// void scoreTwice() {

//   int timecount = 0;

//   ladyB.setResetSetpoint(650); //wall stake 1

//   while (timecount < 650 && lbMotor.getPosition() < 575) {
//     timecount += 10;

//     wait(10, vex::msec);
//   }

//   ladyB.setResetSetpoint(140);
//   wait(200, vex::msec);
  
//   intakeMtrs.spin(12);
//   wait(350, vex::msec);

//   timecount = 0;

//   while (timecount < 600 && intake1.velocity(vex::rpm) > 20) {
//     timecount += 10;

//     wait(10, vex::msec);
//   }
//   intakeMtrs.stop();

//   timecount = 0;

//   ladyB.setResetSetpoint(650); //wall stake 2

//   while (timecount < 650 && lbMotor.getPosition() < 575) {
//     timecount += 10;

//     wait(10, vex::msec);
//   }
// }

// void taskHandler(bool driverMode) {
//   //function callback to automatically cancel all tasks in driver control mode

//   if (!driverMode) {
//     //initializes autonomous background tasks and suspends them

//     odom = vex::task(updateOdom);
//     clrSrt = vex::task(colorSort);
//     lbResetTask = vex::task(lbReset);
//     clrStp = vex::task(colorStop);

//     clrSrt.suspend();
//     lbResetTask.suspend();
//     clrStp.suspend();
//   }

//   else {
//     //kills all autonomous mode background tasks when driver control starts

//     clrSrt.stop();
//     lbResetTask.stop();
//     clrStp.stop();
//   }
// }


// void soloAWPRed() {  
//     odometry.setPos(0.362, -0.310);
//     odometry.setHeading(129.2);
//     imu.setRotation(129.2, vex::deg);
//     lbMotor.setPosition(94);

//     lbResetTask.resume();
//     ladyB.setResetSetpoint(670);
//     wait(550, vex::msec);

//   motion.movePose(0.016, -0.028, 130, 0, 0, -0.05, -1, 700, -1, false);
//     lbResetTask.suspend();
//     lbMotor.spin(-12);
//     drivetrain.stop();
//     wait(150, vex::msec);
//   motion.turnHeading(170, 2, 0, 1, 500);
//   motion.movePose(-0.45, 2, 170, 0.5, 0, -0.3, -0.5, 2000, -1, false);

//   motion.moveDist(-0.3, 0.3, 150, 0.3);
//     clamp = true; //picks up mogo
//   motion.moveDist(-2000, 0.15, 200, 0.3);
//     wait(150, vex::msec);

//     lbMotor.setPosition(0);
//     ladyB.setResetSetpoint(0);
//     lbResetTask.resume();
//     odometry.setTrackWidths(0.09, 0.15);
//     clrSrt.resume();
//   motion.movePose(-1, 3.45, -30, 0.2, 0, 0.05, 0.65, 2000, 15, false);
//   motion.turnHeading(-45, 2, 0.35, 1, 500);
//   motion.movePose(-3.0, 3.9, -90, 1.9, 0, 0.05, 0.5, 2000, 15); //1st/2nd rings
//   motion.movePose(-1, 2.6, -30, 1, 0, -0.05, -0.65, 2000, 15);
//   motion.movePose(-2.35, 2.3, -90, 1, 0, 0.05, 0.65, 2000, 15); //3rd ring
//   motion.movePose(-1.9, 2.3, -90, 0, 0, -0.3, -0.65, 2000, 15);
//   motion.movePose(0.65, 0.375, 90, 2.85, 0, 0.05, 0.75, 500, 15);
//     clamp = false;
//     intakeLift = true;
//     clrSrt.suspend();
//     intakeMtrs.spin(7);
//     clrStp.resume();
//   motion.movePose(0.8, 0.45, 90, 2.5, 0, 0, 0.75, 2000, 15);
//   motion.movePose(1.3, 0.45, 90, 0, 0, 0.05, 0.75, 2000, 15);
//     wait(200, vex::msec);
//     intakeLift = false;
//   motion.movePose(2.95, 2.15, -120, 0.3, 0, -0.4, -0.5, 3000);
  
//   motion.moveDist(-0.3, 0.4, 150, 0.4);
//     clamp = true; //picks up mogo
//   motion.moveDist(-2000, 0.15, 200, 0.4);

//     clrStp.suspend();
//     clrSrt.resume();
//     drivetrain.stop();
//     wait(200, vex::msec);

//   motion.movePose(5.2, 2.3, 90, 1.2, 0, 0.05, 0.7, 1200); //5th ring
//   motion.movePose(3.8, 2.3, 90, 0, 0, -0, -0.7, 2000);
//     drivetrain.setStopping(vex::coast);
//   motion.movePose(3.8, 3.7, 0, 1.3, 0, 0, 0.7, 2000);
//   motion.moveDist(2000, 0.15, 2000, 0.15);
// }


// void soloAWPBlue() {
//     odometry.setPos(-0.362, -0.310);
//     odometry.setHeading(-129.2);
//     imu.setRotation(-129.2, vex::deg);
//     lbMotor.setPosition(94);

//     lbResetTask.resume();
//     ladyB.setResetSetpoint(670);
//     wait(550, vex::msec);

//   motion.movePose(-0.016, -0.028, -130, 0, 0, -0.05, -1, 700, -1, false);
//     lbResetTask.suspend();
//     lbMotor.spin(-12);
//     drivetrain.stop();
//     wait(150, vex::msec);
//   motion.turnHeading(-170, 2, 0, 1, 500);
//   motion.movePose(0.45, 2, -170, 0.5, 0, -0.3, -0.5, 2000, -1, false);

//   motion.moveDist(-0.3, 0.3, 150, 0.3);
//     clamp = true; //picks up mogo
//   motion.moveDist(-2000, 0.15, 200, 0.3);
//     wait(150, vex::msec);

//     lbMotor.setPosition(0);
//     ladyB.setResetSetpoint(0);
//     lbResetTask.resume();
//     odometry.setTrackWidths(0.09, 0.15);
//     clrSrt.resume();
//   motion.movePose(1.45, 3.45, 40, 0.2, 0, 0.05, 0.65, 2000, 15, false);
//   motion.turnHeading(45, 2, 0.35, 1, 500);
//   motion.movePose(3.0, 3.8, 90, 1.9, 0, 0.05, 0.5, 2000, 15); //1st/2nd rings
//   motion.movePose(1, 2.6, 30, 1, 0, -0.05, -0.65, 2000, 15);
//   motion.movePose(2.35, 2.3, 90, 1, 0, 0.05, 0.65, 2000, 15); //3rd ring
//   motion.movePose(1.9, 2.3, 90, 0, 0, -0.3, -0.65, 2000, 15);
//   motion.movePose(-0.65, 0.375, -90, 2.85, 0, 0.05, 0.75, 500, 15);
//     clamp = false;
//     intakeLift = true;
//     clrSrt.suspend();
//     intakeMtrs.spin(7);
//     clrStp.resume();
//   motion.movePose(-0.8, 0.45, -90, 2.5, 0, 0, 0.75, 2000, 15);
//   motion.movePose(-1.3, 0.45, -90, 0, 0, 0.05, 0.75, 2000, 15);
//     wait(200, vex::msec);
//     intakeLift = false;
//   motion.movePose(-2.95, 2.15, 120, 0.3, 0, -0.4, -0.5, 3000);

//   motion.moveDist(-0.3, 0.4, 150, 0.4);
//     clamp = true; //picks up mogo
//   motion.moveDist(-2000, 0.15, 200, 0.4);

//     clrStp.suspend();
//     clrSrt.resume();
//     drivetrain.stop();
//     wait(200, vex::msec);

//   motion.movePose(-5.2, 2.4, -90, 1.2, 0, 0.05, 0.7, 1200); //5th ring
//   motion.movePose(-3.65, 2.4, -90, 0, 0, -0, -0.7, 2000);
//     drivetrain.setStopping(vex::coast);
//   motion.movePose(-3.65, 3.7, 0, 1.3, 0, 0, 0.7, 2000);
//   motion.moveDist(2000, 0.15, 2000, 0.15);
// }


// void skills() {
//     odometry.setPos(0.58, -0.445);
//     odometry.setHeading(144);
//     imu.setRotation(144, vex::deg);
//     lbMotor.setPosition(94);

//     lbResetTask.resume();
//     ladyB.setResetSetpoint(670);
//     wait(550, vex::msec);

//   motion.movePose(0.369, -0.33, 142, 0, 0, -0.05, -1, 700, -1, false);
//     lbResetTask.suspend();
//     lbMotor.spin(-12);
//     drivetrain.stop();
//     wait(150, vex::msec);
//   motion.turnHeading(110, 2, 0, 1, 380);
//   motion.movePose(0.037, -0.183, 110, 0.1, 0, -0.35, -0.5, 2000);

//   motion.moveDist(-0.3, 0.15, 150, 0.35);
//     clamp = true; //picks up first mogo
//   motion.moveDist(-2000, 0.15, 200, 0.15);
//     wait(150, vex::msec);
    
//     lbMotor.setPosition(0);
//     ladyB.setResetSetpoint(0);
//     lbResetTask.resume();
//     odometry.setTrackWidths(0.09, 0.15);
//     intakeMtrs.spin(12);
//   motion.movePose(-0.442, 1.85, -28, 1, 0, 0.65, 0.65, 2000, -1, false, 25);
//   motion.movePose(-2.7, 5.465, -13, 1.75, 0.5, 0.55, 0.65, 2000, -1, false, 25);
//   motion.movePose(-4.17, 7.425, 15, 0.14, 0, 0, 0.55, 2000, -1);

//   motion.movePose(-2.6, 5.865, -38.5, 0, 0, -0, -0.55, 2000);
//   motion.movePose(-2.454, 2.552, -147, 0.6, 0, 0.70, 0.70, 2000, 25, false);
//   motion.movePose(-3.78, 0.4, 180, 0.75, 0, 0.65, 0.70, 2000, 25, false);
//     intakeMtrs.spin(12);
//   motion.movePose(-1.75, -0.8, 70, 1.3, 0, 0, 0.65, 2000, 25);
//     intakeMtrs.spin(12);
//   motion.movePose(-3.2, -0.9, 63, 0.2, 0, -0, -0.65, 1200);

//     intakeMtrs.stop();
//     clamp = false; //unclamps first mogo
//     wait(200, vex::msec);

//     odometry.setTrackWidths(0.125, 0.225);
//     ladyB.setResetSetpoint(140);
//     intakeMtrs.spin(7);
//     clrStp.resume();
//   motion.movePose(-2.962, -0.665, 36, 0.1, 0, 0.5, 0.5, 2000, 15, false);
//     intakeMtrs.spin(7);
//   motion.movePose(-2.1, 4.18, 0, 0.5, 0, 0, 0.5, 2500, 15, true);
//   motion.turnPoint(-4.2, 4.18, 2, 0, 1, 1000);
//   motion.moveDist(2, 0.35, 450);
//     clrStp.suspend();
//     intakeMtrs.spin(12);
//   motion.push3(-3.5, false, 0.35, 1000, 0.75);
//       intakeMtrs.spin(-12);
//       wait(150, vex::msec);
//       intakeMtrs.stop();
//     intakeMtrs.stop();
//     odometry.setPos(-3.7, odometry.getPosY());
//     drivetrain.stop();

//     scoreTwice(); //wall stake 1 and 2

//     ladyB.setResetSetpoint(140);
//   motion.moveDist(-1, 1, 2000);
//     intakeMtrs.spin(12);
//   motion.movePose(-2.65, 7.7, -45, 1.5, 0, 0, 0.6, 2000, 21);
//   motion.movePose(-0.2, 7.8, -90, 1, 0, -0, -0.7, 2000);
//   motion.turnHeading(-36, 2, 0.1, 1, 800);
//     intakeMtrs.stop();
//   motion.movePose(-3.35, 9.05, -87, 4.25, 0, 0.5, 1, 2500); //pushes goal in corner
//     drivetrain.setStopping(vex::coast);
//     drivetrain.stop();
//     wait(100, vex::msec);
//     drivetrain.setStopping(vex::hold);
//     intakeMtrs.spin(12);
//   motion.movePose(0.65, 8.12, -90, 3, 0, -0.35, -0.5, 3000, -1);

//   motion.moveDist(-0.3, 0.15, 150, 0.35);
//     clamp = true; //picks up 3rd mogo
//   motion.moveDist(-2000, 0.15, 200, 0.15);
//     wait(120, vex::msec);

//     odometry.setTrackWidths(0.09, 0.15);
//   motion.moveDist(odometry.getPosX() - 0.8, 0.5, 2000, 0);
//   motion.turnPoint(0.8, 10, 2, 0, 1, 1000);
//     intakeMtrs.spin(12);
//   motion.moveDist(2, 0.35, 450);
//   motion.push3(9, true, 0.3, 1200, 0.75);
//   motion.moveDist(2, 0.2, 350, 0.12);
//     motion.turnHeading(Misc::getHeading(false), 0, 0, 0, 0);
//     odometry.setPos(odometry.getPosX(), 9.5);

//     motion.moveDist(-0.415, 1, 2000);
//     intakeMtrs.stop();
//     wait(150, vex::msec);

//     drivetrain.stop();
//     ladyB.setResetSetpoint(670); //blue alliance stake
//     wait(550, vex::msec);

//   motion.moveDist(-0.5, 0.5, 1000);
//     ladyB.setResetSetpoint(0);
//     intakeMtrs.spin(5.5);
//     clrStp.resume();
//   motion.movePose(-1.2, 6.25, 157, 3, 0, 0.65, 0.65, 2000, 20, false);
//   motion.movePose(1.2, 4.25, 135, 1.5, 0, 0.45, 0.65, 2000, -1, false); //middle of field ring
//     clrStp.suspend();
//     intakeMtrs.stop();
//   motion.movePose(2.8, 2.7, 135, 0, 0, 0.45, 0.45, 1000, -1, false);
//     intakeMtrs.spin(12);
//   motion.movePose(3.1, 2.55, 135, 0.1, 0, 0.45, 0.45, 600, -1, false);
//   motion.movePose(4.85, 0.65, 125, 0, 0, 0.45, 0.45, 2000, 20, false);
//   motion.movePose(6.2, 0.7, 80, 0.2, 0, 0.05, 0.45, 2000, -1, false);
//   motion.turnHeading(-155, 2, 0.1, 0.4, 1000);
//   motion.movePose(5.5, -0.38, -155, 0.1, 0, 0, 0.7, 2000);
//     wait(350, vex::msec);
//   motion.movePose(6.15, -0.38, -48, 0.7, 0, -0.15, -0.7, 1200);
//     intakeMtrs.stop();

//     clamp = false; //unclamps third mogo
//     wait(200, vex::msec);

//     odometry.setTrackWidths(0.125, 0.225);
//   motion.movePose(5.2, 0.3, -28, 0, 0, 0, 0.65, 2000);
//   motion.turnHeading(90, 2, 0.1, 1, 1000);
//   motion.movePose(3.6, 0.35, 90, 0.6, 0, -0.15, -0.5, 2000, 20, false);

//     motion.moveDist(-2000, 0.15, 150, 0.15);
//     clamp = true; //picks up fourth mogo
//     motion.moveDist(-2000, 0.15, 200, 0.15);
//     wait(150, vex::msec);

//     odometry.setTrackWidths(0.09, 0.15);
//     intakeMtrs.spin(7);
//     clrStp.resume();
//     ladyB.setResetSetpoint(140);
//   motion.movePose(5.35, 1.943, 0, 1.5, 0, 0.5, 0.5, 2000, -1, false);
//     intakeMtrs.spin(7);
//   motion.movePose(4.8, 4.4, -35, 0, 0, 0, 0.5, 2000);
//   motion.turnPoint(6.4, 4.35, 2, 0, 1, 1000);
//   motion.moveDist(2, 0.35, 450);
//     clrStp.suspend();
//     intakeMtrs.spin(12);
//   motion.push3(5.75, false, 0.35, 1400, 0.25);
//   motion.moveDist(2, 0.35, 250, 0.35);
//     intakeMtrs.spin(-12);
//   drivetrain.stop();
//     wait(150, vex::msec);
//     intakeMtrs.stop();
//     odometry.setPos(5.9, odometry.getPosY());

//   scoreOnce(); //3rd neutral stake

//     intakeMtrs.spin(12);
//     ladyB.setResetSetpoint(0);
//   motion.moveDist(-1, 0.4, 2000);
//     clrSrt.resume();
//   motion.movePose(3.45, 6.05, -60, 0.45, 0, 0.65, 0.65, 2000, 15, false);
//   motion.movePose(4.418, 6.55, 117.5, 1.2, 0, 0.65, 0.65, 2000, 12, false);
//   motion.movePose(5.7, 8.15, 0, 0.9, 0, 0, 0.65, 2000, 12);
//   motion.movePose(5.5, 6.9, 30, 0, 0, -0, -0.65, 2000);
//   motion.movePose(5.15, 7.65, -25, 0, 0, 0.40, 0.40, 2000, -1, false);
//   motion.movePose(4.5, 9.15, -25, 0, 0, 0, 0.40, 2000);
//     wait(600, vex::msec);
//   motion.movePose(5.65, 9.25, -135, 0.1, 0, -0.5, -1, 1200);
//     clrSrt.suspend();
//     intakeMtrs.stop();

//     clamp = false; //unclamps fourth mogo
//     wait(200, vex::msec);
    
//     odometry.setTrackWidths(0.125, 0.225);
//     intakeMtrs.spin(-12);
//   motion.movePose(5.0, 7.5, -135, 0.5, 0, 0, 0.65, 2000);
//   motion.movePose(5.65, 9.25, -135, 0.1, 0, -0.5, -1, 2000);
//   motion.movePose(5.0, 7.5, -135, 0.5, 0, 0, 0.65, 2000);
//     intakeMtrs.stop();
//   /*
//   motion.movePose(5.0, 7.5, -135, 0.5, 0, 0.35, 0.85, 2000);
//   motion.turnHeading(30, 2, 0.5, 1, 1000);
//     ladyB.setResetSetpoint(420);
//     intakeMtrs.stop();
//   motion.movePose(2.232, 5.9, 45, 2, 0, -0.55, -0.55, 2000, -1, -false);
//   motion.moveDist(-2, 0.55, 1000, 0.55);
//   */
// }


// void negativeRed() {
//     odometry.setPos(0.362, -0.310);
//     odometry.setHeading(129.2);
//     imu.setRotation(129.2, vex::deg);
//     lbMotor.setPosition(94);

//     lbResetTask.resume();
//     ladyB.setResetSetpoint(670);
//     wait(550, vex::msec);

//   motion.movePose(0.016, -0.028, 130, 0, 0, -0.05, -1, 700, -1, false);
//     lbResetTask.suspend();
//     lbMotor.spin(-12);
//     drivetrain.stop();
//     wait(150, vex::msec);
//   motion.turnHeading(170, 2, 0, 1, 500);
//   motion.movePose(-0.45, 2, 170, 0.5, 0, -0.4, -0.5, 2000, -1, false);

//   motion.moveDist(-0.3, 0.4, 150, 0.4);
//     clamp = true; //picks up mogo
//   motion.moveDist(-2000, 0.15, 200, 0.4);
//     wait(150, vex::msec);

//     lbMotor.setPosition(0);
//     ladyB.setResetSetpoint(0);
//     lbResetTask.resume();
//     odometry.setTrackWidths(0.09, 0.15);
//     clrSrt.resume();
//   motion.movePose(-1.31, 3.2, -28, 0.4, 0, 0.05, 0.65, 2000, 15, false);
//   motion.turnHeading(-51, 2, 0.35, 1, 500);
//   motion.movePose(-2.62, 3.73, -90, 1.75, 0, 0.05, 0.4, 2000, 15); //1st/2nd rings
//   motion.movePose(-1, 2.45, -30, 1, 0, -0.05, -0.65, 2000, 15);
//   motion.movePose(-2.4, 2.4, -90, 0.7, 0, 0.05, 0.65, 2000, 15); //3rd ring
//   motion.movePose(-1.9, 2.4, -90, 0, 0, -0.3, -0.65, 2000, 15);
//   motion.turnPoint(-4.4, -1.4, 2, 0.1, 1, 1000, false);
//   motion.moveDist(2000, 1, 250, 1);
//   motion.push(0.6, 2000, 0.5);
//     wait(600, vex::msec);
//   motion.moveDist(-0.4, 1, 700, 0);
//     intakeLift = true;
//   motion.moveDist(2000, 1, 250, 1);
//   motion.push(0.3, 2000, 0.5);
//     wait(600, vex::msec);
//   motion.movePose(0.65, 0.375, -90, 0, 0, -0.05, -0.75, 500, 15);
//   motion.movePose(0.8, 0.4, 90, 2.5, 0, 0, 0.75, 2000, 15);
//   motion.movePose(1.3, 0.4, 90, 0, 0, 0.05, 0.75, 2000, 15);
//     wait(200, vex::msec);
//   motion.movePose(5, 0, 100, 0.3, 0, 0, 1, 3000);
//     clrSrt.suspend();
// }


// void negativeBlue() {
//     odometry.setPos(-0.362, -0.310);
//     odometry.setHeading(-129.2);
//     imu.setRotation(-129.2, vex::deg);
//     lbMotor.setPosition(94);

//     lbResetTask.resume();
//     ladyB.setResetSetpoint(670);
//     wait(550, vex::msec);

//   motion.movePose(-0.016, -0.028, -130, 0, 0, -0.05, -1, 700, -1, false);
//     lbResetTask.suspend();
//     lbMotor.spin(-12);
//     drivetrain.stop();
//     wait(150, vex::msec);
//   motion.turnHeading(-170, 2, 0, 1, 500);
//   motion.movePose(0.45, 2, -170, 0.5, 0, -0.4, -0.5, 2000, -1, false);

//   motion.moveDist(-0.3, 0.4, 150, 0.4);
//     clamp = true; //picks up mogo
//   motion.moveDist(-2000, 0.15, 200, 0.4);
//     wait(150, vex::msec);

//     lbMotor.setPosition(0);
//     ladyB.setResetSetpoint(0);
//     lbResetTask.resume();
//     odometry.setTrackWidths(0.09, 0.15);
//     clrSrt.resume();
//   motion.movePose(1.31, 3.2, 28, 0.4, 0, 0.05, 0.65, 2000, 15, false);
//   motion.turnHeading(51, 2, 0.35, 1, 500);
//   motion.movePose(2.8, 3.73, 90, 1.95, 0, 0.05, 0.4, 2000, 15); //1st/2nd rings
//   motion.movePose(1, 2.45, 30, 1, 0, -0.05, -0.65, 2000, 15);
//   motion.movePose(2.4, 2.4, 90, 0.7, 0, 0.05, 0.65, 2000, 15); //3rd ring
//   motion.movePose(1.9, 2.4, 90, 0, 0, -0.3, -0.65, 2000, 15);
//   motion.turnPoint(4.38, -1.4, 2, 0.1, 1, 1000, false);
//   motion.moveDist(2000, 1, 250, 1);
//   motion.push(0.42, 2000, 0.2);
//     wait(600, vex::msec);
//   motion.moveDist(-0.4, 1, 700, 0);
//     intakeLift = true;
//   motion.moveDist(2000, 1, 250, 1);
//   motion.push(0.6, 2000, 0.5);
//     wait(600, vex::msec);
//   motion.movePose(-0.65, 0.375, 90, 0, 0, -0.05, -0.75, 500, 15);
//   motion.movePose(-0.8, 0.4, -90, 2.5, 0, 0, 0.75, 2000, 15);
//   motion.movePose(-1.2, 0.4, -90, 0, 0, 0.05, 0.75, 2000, 15);
//     wait(350, vex::msec);
//   motion.movePose(-5, 0, - 100, 0.3, 0, 0, 1, 3000);
//     clrSrt.suspend();
// }


// void auton() {
//   //main body of all autonomous functions

//   initialize();
//   odom.resume();

//   //skills();
//   //negativeRed();
//   negativeBlue();
//   //soloAWPRed();
//   //soloAWPBlue();
//   //positiveRed();
//   //positiveBlue();
// }