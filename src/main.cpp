#include "mainBody.h"

vex::competition Competition;


int main() {
  
  imu.calibrate();
  while (imu.isCalibrating()) wait(10, vex::msec);

  brain.Screen.print("hello wrold");
  lb1.resetPosition();
  lb1.setStopping(vex::brake);
  colorSensor.setLightPower(100);
  colorSensor.setLight(vex::ledState::on);
  
  //auton();

  Competition.autonomous(auton);
  Competition.drivercontrol(driverControl);
}