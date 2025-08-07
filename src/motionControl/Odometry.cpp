#include "motionControl/Odometry.h"


void Odometry::tick() {
  //updates odometry information: position, speed, velocities

  float deltaHorizontal = 0;//Units::tickToUnit(sideways.position(vex::deg) - lastHorizontal, 2, unit);
  float deltaLateral = Units::tickToUnit((bl.position(vex::deg) + br.position(vex::deg)) / 2.0 - lastLateral, 2.75, unit);//Units::tickToUnit(parallel.position(vex::deg) - lastLateral, 2.75, unit);
  float deltaTheta = Units::degToRad(imu.rotation(vex::deg)) - lastTheta;

  float xOffset = (deltaTheta == 0) ? deltaHorizontal : 2.0 * sin(deltaTheta / 2.0) * (deltaHorizontal / deltaTheta + horizontalTrackWidth);
  float yOffset = (deltaTheta == 0) ? deltaLateral : 2.0 * sin(deltaTheta / 2.0) * (deltaLateral / deltaTheta + lateralTrackWidth);
  
  posX += sqrt(pow(xOffset, 2.0) + pow(yOffset, 2.0)) * cos(atan2(yOffset, xOffset) - (lastTheta + deltaTheta / 2.0));
  posY += sqrt(pow(xOffset, 2.0) + pow(yOffset, 2.0)) * sin(atan2(yOffset, xOffset) - (lastTheta + deltaTheta / 2.0));

  //lastHorizontal = sideways.position(vex::deg);
  lastLateral = (bl.position(vex::deg) + br.position(vex::deg)) / 2.0;//parallel.position(vex::deg);
  lastTheta = Units::degToRad(imu.rotation(vex::deg));

  updateDerivative();
}


void Odometry::setPos(float posX, float posY) {
  //updates the current robot positional information based on user input

  this->posX = posX;
  this->posY = posY;
}


void Odometry::setX(float x) {

  this->posX = x;
}


void Odometry::setTrackWidths(float lateralTrackWidth, float horizontalTrackWidth) {
  //updates the tracking wheel offsets of the robot

  this->lateralTrackWidth = lateralTrackWidth;
  this->horizontalTrackWidth  = horizontalTrackWidth;
}


void Odometry::setTrackWidths(std::pair<float, float> offsets) {

  this->lateralTrackWidth = offsets.first;
  this->horizontalTrackWidth = offsets.second;
}


void Odometry::setUnit(float unit) {
  //changes the length unit of the odometry

  this->unit = unit;
}


void Odometry::setHeading(float theta) {
  //changes the initial heading of the odometry

  lastTheta = Units::degToRad(theta);
  imu.setRotation(theta, vex::deg);
}


float Odometry::getTrackWidth() {
  //gets the track width of the robot

  return trackWidth;
}


float Odometry::getLateralOffset() {

  return lateralTrackWidth;
}


float Odometry::getHorizontalOffset() {

  return horizontalTrackWidth;
}


float Odometry::getPosX() {
  //returns the current x position

  return posX;
}


float Odometry::getPosY() {
  //returns the current y position

  return posY;
}


void Odometry::updateDerivative() {

  std::pair<float, float> pos = std::make_pair(posX, posY);
  positions.push_back(pos);
  if (positions.size() > 5) positions.erase(positions.begin());
  
  angles.push_back(imu.rotation(vex::deg));
  if (angles.size() > 4) angles.erase(angles.begin());
}


float Odometry::getSpeed() {

  return sqrt(pow(getVelocityX(), 2) + pow(getVelocityY(), 2));
}


float Odometry::getVelocityTheta() {

  return (getSpeed() < 0.1) ? 0 : Units::radToDeg(atan2(getVelocityX(), getVelocityY()));
}


float Odometry::getVelocityX() {

  return (!positions.empty()) ? (positions.back().first - positions.front().first) * (100.0 / positions.size()) : 0;
}


float Odometry::getVelocityY() {

  return (!positions.empty()) ? (positions.back().second - positions.front().second) * (100.0 / positions.size()) : 0;
}


float Odometry::getAngularVelocity(){

  return (!angles.empty()) ? (angles.back() - angles.front()) * (100.0 / angles.size()) : 0;
}