#include "mainBody.h"


// INITIALIZE DRIVETRAIN

    MotorGroup leftMotors({    // LEFT SIDE OF DRIVETRAIN
        Motor("fl", &fl),      // FRONT LEFT MOTOR
        Motor("ml", &ml),      // MIDDLE LEFT MOTOR
        Motor("bl", &bl)       // BACK LEFT MOTOR
    });

    MotorGroup rightMotors({   // RIGHT SIDE OF DRIVETRAIN
        Motor("fr", &fr),      // FRONT RIGHT MOTOR
        Motor("mr", &mr),      // MIDDLE RIGHT MOTOR
        Motor("br", &br)       // BACK RIGHT MOTOR
    });

    MotorGroup driveMotors({   // ENTIRE DRIVETRAIN
        Motor("fl", &fl),      // FRONT LEFT MOTOR
        Motor("ml", &ml),      // MIDDLE LEFT MOTOR
        Motor("bl", &bl),      // BACK LFET MOTOR
        Motor("fr", &fr),      // FRONT RIGHT MOTOR
        Motor("mr", &mr),      // MIDDLE RIGHT MOTOR
        Motor("br", &br)       // BACK RIGHT MOTOR
    });

    ChassisGeometry chassisGeometry(   // DRIVETRAIN GEOMETRY
        &leftMotors,                   // LEFT DRIVETRAIN MOTOR GROUP
        &rightMotors,                  // RIGHT DRIVETRAIN MOTOR GROUP
        -1                             // DRIVETRAIN TRACK WIDTH
    );

    ChassisDriverSettings chassisDriverSettings(   // DRIVER SETTINGS
        &controller,                               // CONTROLLER OBJECT
        1,                                         // EXPONENTIAL JOYSTICK SCALE
        0,                                         // MAX OUTPUT THRESHOLD
        800,                                       // MILLIVOLTS OF FEEDFORWARD/STATIC FRICTION CANCELLATION
        true                                       // HALF-CIRCLE OUTPUT SCALING (TRUE = ENABLED)
    );

    Tank chassis(              // DRIVETRAIN OBJECT
        chassisGeometry,       // DRIVETRAIN GEOMETRY CONFIGURATION
        chassisDriverSettings  // DRIVER SETTINGS
    );


// INITIALIZE INTAKE

    MotorGroup intakeMotors({      // INTAKE MOTOR GROUP
        Motor("intake1", &intake1) // FIRST INTAKE MOTOR
    });

    Intake intake(     // INTAKE OBJECT
        &intakeMotors, // INTAKE MOTOR GROUP
        &colorSensor,  // COLOR SENSOR OBJECT
        &controller,   // CONTROLLER OBJECT
        false,         // TEAM COLOR (RED = TRUE)
        105,           // COLOR SORT DELAY AFTER DETECTION (MOTOR TICKS)
        200            // COLOR SORT REVERSAL DURATION (MILLISECONDS)
    );


// INITIALIZE WALLSTAKE MECH

    MotorGroup lbMotors({      // LADY BROWN MOTOR GROUP
        Motor("ladyB1", &lb1), // FIRST LADY BROWN MOTOR
    });

    AsymptoticGains lbKp = AsymptoticGains( // LADY BROWN P-CONTROLLER GAIN SCHEDULING
        0.14,                               // INITIAL: KP AT ZERO ERROR
        0.14,                               // FINAL: KP AT INFINITE ERROR
        1,                                  // K
        1                                   // P
    );

    PID lbPID = PID(   // LADY BROWN PID SETTINGS
        lbKp,          // GAIN-SCHEDULED PROPORTIONAL
        0.01,          // INTEGRAL CONSTANT
        0.0015,        // DERIVATIVE CONSTANT
        120,           // INTEGRAL BOUND (TICKS)
        true           // INTEGRAL SIGN RESET (TRUE = ENABLED)
    );

    WallStakeMech ladyBrown(   // LADY BROWN OBJECT
        &lbMotors,             // LADY BROWN MOTOR GROUP
        &lbPID,                // LADY BROWN PID SETTINGS
        0                      // LADY BROWN FEEDFORWARD (VOLTS)
    );


// INITIALIZE MOBILE GOAL CLAMP

    Clamp backClamp(   // MOBILE GOAL CLAMP OBJECT
        &clamp,        // PISTON OBJECT
        &clampSensor,  // DISTANCE SENSOR OBJECT
        &controller    // CONTROLLER OBJECT
    );


// INITIALIZE DOINKER

    Doinker doinkerMech(  // DOINKER OBJECT
        &doinker          // PISTON OBJECT
    );


// INITIALIZE ODOMETRY

    Odometry odometry(    // ODOMETRY OBJECT
        0.125,            // PARALLEL OFFSET
        0.225,            // PERPENDICULAR OFFSET
        0                 // TRACK WIDTH
    );


// INITIALIZE DRIVETRAIN PID CONTROLLERS

    AsymptoticGains lateralKp(18000,
        15000,
        1, 
        1
    );

    AsymptoticGains angularKp(
        550,
        200,
        28,
        1.7
    );

    AsymptoticGains correctKp(
        200,
        200, 
        1, 
        1
    );

    PID lateralPID(
        lateralKp,
        25000,
        500,
        0.25,
        true
    );

    PID angularPID(
        angularKp,
        2500,
        15,
        5,
        true
    );

    PID correctPID(
        correctKp,
        0,
        40,
        0,
        false
    );


// INITIALIZE MOTION ALGORITHM OBJECT

    Motion motion(
        lateralPID,
        angularPID,
        correctPID,
        odometry
    );


// INITIALIZE GLOBAL VARIABLES

    bool stopAll = false; // STOPS ALL STATE MACHINES FROM RUNNING WHEN A MACRO IS RUNNING


// INITIALIZE GLOBAL TASKS

    vex::task odometryTask(nullptr);
    vex::task colorSortTask(nullptr);
    vex::task lbResetTask(nullptr);
    vex::task colorStopTask(nullptr);
    vex::task colorStopTask2(nullptr);
    vex::task printTask(nullptr);
    vex::task killTask(nullptr);


// TASK HANDLER FUNCTION FOR AUTOMATIC TASK DISABLING IN DRIVER CONTROL PERIOD

    void taskHandler(bool driverMode) {
    
        if (!driverMode) {
    
            odometryTask = vex::task(
                []() {
  
                    while (1) {
                        
                        uint64_t timestamp = vex::timer::systemHighResolution();
                    
                        odometry.tick();
                        
                        wait((timestamp + 11000.0 - vex::timer::systemHighResolution()) / 1000.0, vex::msec);
                    }
                  
                    return 0;
                }
            );

            colorSortTask = vex::task(
                []() {

                    while (1) {
                  
                      intake.runIntake(12);
                  
                      wait(10, vex::msec);
                    }

                    return 0;
                }

            );

            lbResetTask = vex::task(
                []() {
                    
                    while (1) {
                    
                        ladyBrown.resetAuto();
                    
                        wait(10, vex::msec);
                    }

                    return 0;
                }
            );

            colorStopTask = vex::task(
                []() {

                    bool recentlyStopped = false;
                    int count = 0;

                    while (1) {

                        if (recentlyStopped) count += 10;
                        if (count == 200) {
                            recentlyStopped = false;
                            count = 0;
                            intakeMotors.stop();
                        }
                        else if (count != 0) intakeMotors.spin(12);

                        if (intake.getDetectedOpp()) recentlyStopped = true;
                    
                        wait(10, vex::msec);
                    }

                    return 0;
                }
            );

            colorStopTask2 = vex::task(
                []() {

                    bool recentlyStopped = false;
                    int count = 0;

                    while (1) {

                        if (recentlyStopped) count += 10;
                        if (count == 200) {
                            recentlyStopped = false;
                            count = 0;
                            intakeMotors.stop();
                        }
                        else if (count != 0) intakeMotors.spin(-7.5);

                        if (intake.getDetected()) recentlyStopped = true;
                    
                        wait(10, vex::msec);
                    }

                    return 0;
                }
            );

            printTask = vex::task(
                []() {

                    while (1) {

                        printf("%f | %f | %f\n", odometry.getPosX(), odometry.getPosY(), Misc::getHeading(false));

                        wait(10, vex::msec);
                    }

                    return 0;
                }
            );

            killTask = vex::task(
                []() {

                    while (1) {
                        
                        if (controller.ButtonDown.pressing()) {
                            motion.cancelMotions();
                            drivetrain.stop();
                        }

                        wait(10, vex::msec);
                    }

                    return 0;
                }
            );
        
            colorSortTask.suspend();
            lbResetTask.suspend();
            colorStopTask.suspend();
            colorStopTask2.suspend();
            printTask.suspend();
        }
    
        else {
    
            colorSortTask.stop();
            lbResetTask.stop();
            colorStopTask.stop();
            colorStopTask2.stop();
            killTask.stop();
        }
    }


// INITIALIZE AUTONOMOUS PERIOD FUNCTION

    void auton() {

        imu.resetRotation();
        parallel.resetPosition();
        sideways.resetPosition();
      
        drivetrain.setStopping(vex::brake);
      
        motion.setUnit(foot);
        motion.setPursuitSettings(1, 1, 0.2, 0.4, 0, 5);
        
        odometry.setUnit(foot);
        odometry.setPos(0, 0);
        odometryTask.resume();

        taskHandler(false);

        //motion.turnHeading(40, 2, 0, 1, 3000); //setup for negative red elims/quals and red solo awp
        //motion.moveDist(0.5, 0.5, 3000);

        //motion.turnHeading(-40, 2, 0, 1, 3000); //setup for negative blue elims/quals and blue solo awp
        //motion.moveDist(0.5, 0.5, 3000);

        //negativeRedElims(lbResetTask, colorSortTask, colorStopTask, odometry, intakeMotors, lbMotors, ladyBrown, motion);
        //negativeRedQuals(lbResetTask, colorSortTask, odometry, intakeMotors, lbMotors, ladyBrown, motion);
        //negativeBlueElims(lbResetTask, colorSortTask, colorStopTask, odometry, intakeMotors, lbMotors, ladyBrown, motion);
        //negativeBlueQuals(lbResetTask, colorSortTask, odometry, intakeMotors, lbMotors, ladyBrown, motion);
        //soloAWPRed(lbResetTask, colorSortTask, colorStopTask, odometry, intakeMotors, lbMotors, ladyBrown, motion);
        //soloAWPBlue(lbResetTask, colorSortTask, colorStopTask, odometry, intakeMotors, lbMotors, ladyBrown, motion);

        //motion.turnHeading(19, 2, 0, 1, 3000); //setup for positive red elims

        //motion.turnHeading(-19, 2, 0, 1, 3000); //setup for positive blue elims

        //positiveRedElims(lbResetTask, colorSortTask, colorStopTask, colorStopTask2, odometry, intakeMotors, intake, lbMotors, ladyBrown, motion);
        positiveBlueElims(lbResetTask, colorSortTask, colorStopTask, colorStopTask2, odometry, intakeMotors, intake, lbMotors, ladyBrown, motion);
    }

    void aPressed() {
        ladyBrown.setResetSetpoint(1310);
    }


// INITIAlIZE DRIVER CONTROL FUNCTION

    void driverControl() {

        taskHandler(true);                     // DISABLES ALL AUTONOMOUS TASKS AT THE BEGINNING OF DRIVER CONTROL
        //auton();

        leftMotors.setStopping(true);          // SETS LEFT DRIVETRAIN MOTORS TO COAST
        rightMotors.setStopping(true);         // SETS RIGHT DRIVETRAIN MOTORS TO COAST

        ladyBrown.setMogoIntakePosition(0);    // LADY BROWN POSITION TO INTAKE ONTO MOBILE GOAL
        ladyBrown.setStakeIntakePosition(350); // LADY BROWN POSITION TO INTAKE INTO COMPRESSION CHAMBER 
        ladyBrown.setStakeScorePosition(2200); // LADY BROWN POSITION TO SCORE ON WALL STAKES

        backClamp.setClampSensorRange(1.6);    // MOBILE GOAL CLAMP DISTANCE SENSOR THRESHOLD

        controller.ButtonUp.pressed(           // LAMBDA FUNCTION: DRIVER MACRO TO SCORE ON ALLIANCE STAKES
            []() {
                if (!stopAll) {
                    
                    stopAll = true;
                    driveMotors.setStopping(false);
                    
                    motion.turnHeading(Misc::getHeading(false), 0, 0, 0, 0);
                    ladyBrown.setResetSetpoint(1960);
                    motion.moveDist(-0.7, 1, 2000);
                    driveMotors.stop();
                    wait(200, vex::msec);
                    
                    driveMotors.setStopping(true);
                    stopAll = false;
                }
            }
        );

        intakeLift = false;                    // AUTOMATICALLY DISABLES INTAKE LIFTER BEFORE DRIVER CONTROL
        ladyBrown.setResetSetpoint(0);         // AUTOMATICALLY RETRACTS LADY BROWN AT BEGINNING OF DRIVER CONTROL

        while (1) {

            uint64_t timestamp = vex::timer::systemHighResolution(); 

            ladyBrown.reset(                           // STATE MACHINE FOR LADY BROWN POSITION
                controller.ButtonR1.pressing(),        // BUTTON TO GO UP A STAGE
                controller.ButtonR2.pressing(),        // BUTTON TO GO DOWN A STAGE
                false,                                 // BUTTON TO INTAKE (FOR ECHO HANG)
                false,                                 // BUTTON TO HANG (FOR ECHO HANG)
                2                                      // DRIVER CONTROL CONFIGURATION TYPE
            );

            if (!stopAll) {
                
                chassis.controllerFeedbackSpin();      // STATE MACHINE FOR JOYSTICK-DRIVETRAIN CONTROL
                    
                intake.controllerFeedbackSpin(         // STATE MACHINE FOR INTAKE MECHANISM CONTROL
                    controller.ButtonL1.pressing(),    // BUTTON TO INTAKE
                    controller.ButtonL2.pressing()     // BUTTON TO OUTTAKE
                );
                intake.controllerFeedbackToggleColor(  // COLOR SORT TOGGLE
                    controller.ButtonX.pressing()      // BUTTON TO TOGGLE COLOR SORTING
                );
                    
                backClamp.toggleState(                 // BACK CLAMP TOGGLE
                    controller.ButtonY.pressing()      // BUTTON TO TOGGLE BACK CLAMP
                );
                backClamp.vibrateState();              // STATE MACHINE FOR VIBRATING BACK CLAMP BASED ON DISTANCE SENSOR

                doinkerMech.toggleState(               // DOINKER TOGGLE
                    controller.ButtonRight.pressing()  // BUTTON TO TOGGLE DOINKER
                );

                controller.ButtonA.pressed(aPressed);
            }
            
            if (vex::timer::systemHighResolution() / 1000.0 < timestamp + 11000.0) wait((timestamp + 11000.0 - vex::timer::systemHighResolution()) / 1000.0, vex::msec);
        }
    }