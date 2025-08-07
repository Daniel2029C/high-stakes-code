#include "components/WallStakeMech.h"


WallStakeMech::WallStakeMech(MotorGroup* motorGroup, PID* pid, float feedforward)
    //constructor for wall stake mech object

    : motorGroup(motorGroup)
    , pid(pid)
    , feedforward(feedforward)
{}


void WallStakeMech::setMogoIntakePosition(float mogoIntakePosition) {
    //sets mogo intake target position

    this->mogoIntakePosition = mogoIntakePosition;
}


void WallStakeMech::setStakeIntakePosition(float stakeIntakePosition) {
    //sets stake intake target position

    this->stakeIntakePosition = stakeIntakePosition;
}


void WallStakeMech::setStakeScorePosition(float stakeScorePosition) {
  //sets stake scoring target position

  this->stakeScorePosition = stakeScorePosition;
}


void WallStakeMech::setHangPosition(float hangPosition) {
  //sets lift position when about to hang

  this->hangPosition = hangPosition;
}


void WallStakeMech::setHangClampPiston(vex::digital_out* hangClamp) {
  //initializes the hang clamp piston for echo hang
  
  this->hangClamp = hangClamp;
}


void WallStakeMech::setResetSetpoint(float resetSetpoint)  {
  //sets reset setpoint directly

  this->resetSetpoint = resetSetpoint;
}


void WallStakeMech::updateStatusOne(bool button1, bool button2) {
    //updates the state of the wall stake mech based on button presses

    if (button1) {

      if (!prevPressing) {
        resetSetpoint = (fwd) ? stakeScorePosition : mogoIntakePosition;
        fwd = !fwd;
      }

      prevPressing = true;
      prevStopped = false;
    }
    else if (button2) {
        
      resetSetpoint = stakeIntakePosition;
      fwd = true;

      prevPressing = false;
      prevStopped = false;
    }
    else {
        
      if (!prevStopped) resetSetpoint = motorGroup->getPosition();

      prevPressing = false;
      prevStopped = true;
    }
}


void WallStakeMech::updateStatusTwo(bool button1, bool button2) {
    //updates the state of the wall stake mech based on button presses

    if (button1) {

      if (stageState != 2 && !prevPressing) stageState += 1;

      if (!prevPressing) resetSetpoint = (stageState == 2) ? stakeScorePosition : stakeIntakePosition;

      prevPressing = true;
      prevStopped = false;
    }
    else if (button2) {
      
      if (stageState != 0 && !prevStopped) stageState -= 1;

      if (!prevStopped) resetSetpoint = (stageState == 0) ? mogoIntakePosition : stakeIntakePosition;

      prevPressing = false;
      prevStopped = true;
    }
    else {
        
      if (prevPressing || prevStopped) resetSetpoint = motorGroup->getPosition();

      prevPressing = false;
      prevStopped = false;
    }
}


void WallStakeMech::updateStatusThree(bool button1, bool button2) {
  //updates the state of the wall stake mech based on button presses

  if (button1) {

    if (!prevPressing) {
      fwd = !fwd;
      resetSetpoint = (fwd) ? mogoIntakePosition : stakeIntakePosition;
    }

    prevPressing = true;
    prevStopped = false;
  }
  else if (button2) {
      
    resetSetpoint = stakeScorePosition;
    fwd = false;

    prevPressing = false;
    prevStopped = false;
  }
  else {
      
    if (!prevStopped) resetSetpoint = (fwd) ? mogoIntakePosition : stakeIntakePosition;

    prevPressing = false;
    prevStopped = true;
  }
}


void WallStakeMech::updateStatusEcho(bool upButton, bool downButton, bool intakeButton, bool hangButton) {
  //updates the state of the wall stake mech based on button presses

  if (stageState == 3) resetSetpoint = hangPosition;
  else if (stageState == 2 && (upButton || downButton)) resetSetpoint = stakeScorePosition;
  else if (stageState == 1 && (upButton || downButton)) resetSetpoint = stakeIntakePosition;
  else if (stageState == 0 && intakeButton) resetSetpoint = mogoIntakePosition;
  else if (stageState == 0 && downButton) resetSetpoint = 0.0;
  else if ((prevPressing || prevStopped || prevIntake) && !upButton && !downButton && !intakeButton) resetSetpoint = motorGroup->getPosition();

  if (upButton) {

    if (stageState <= 1 && !prevPressing) stageState += 1;

    prevPressing = true;
    prevStopped = false;
  }
  
  else if (downButton) {
      
    if (stageState != 0 && !prevStopped) stageState -= 1;

    prevPressing = false;
    prevStopped = true;

    hangClamp->set(false);
  }

  else if (hangButton) {

    stageState = 3;

    prevPressing = false;
    prevStopped = false;

    hangClamp->set(true);
  }
  
  else {
    
    prevPressing = false;
    prevStopped = false;
  }

  prevIntake = intakeButton;
}


void WallStakeMech::reset(bool button1, bool button2, bool intakeButton, bool hangButton, int config) {
    //pid for the wall stake mech
    
    if (config == 1) updateStatusOne(button1, button2);
    else if (config == 2) updateStatusTwo(button1, button2);
    else if (config == 3) updateStatusThree(button1, button2);
    else updateStatusEcho(button1, button2, intakeButton, hangButton);
    
    float output;
    output = pid->tick(resetSetpoint - motorGroup->getPosition());
    output = Misc::clamp(output + feedforward, -12, 12);

    motorGroup->spin(output, true);
}


void WallStakeMech::resetAuto() {
    //runs motor for auto
  
    float output;
    output = pid->tick(resetSetpoint - motorGroup->getPosition());
    output = Misc::clamp(output, -12, 12);

    motorGroup->spin(output, true);
}


void WallStakeMech::scoreOnce() {
  //function to score on a wall stake once in autonomous
  
  int timecount = 0;
  
  setResetSetpoint(650);
  
  while (timecount < 650 && motorGroup->getPosition() < 575) {
    
    resetAuto();

    timecount += 10;  
    
    wait(10, vex::msec);
  }
}


void WallStakeMech::scoreTwice() {
  //function to score on a wall stake twice in autonomous

  int timecount = 0;
  
  scoreOnce();

  setResetSetpoint(140);
  while (timecount < 200) {
    
    resetAuto();

    timecount += 10;  
    
    wait(10, vex::msec);
  }
  
  motorGroup->spin(12);
  wait(350, vex::msec);

  timecount = 0;
  while (timecount < 600 && motorGroup->getVelocity() > 20) {
    
    timecount += 10;

    wait(10, vex::msec);
  }
  motorGroup->stop();

  scoreOnce();
}


int WallStakeMech::getStage() {
  //returns stage of lift

  return stageState;
}


float WallStakeMech::getHangPosition() {
  //returns position of lift
  
  return hangPosition;
}