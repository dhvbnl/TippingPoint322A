#include "vex.h"

int stopTimer = 0;

//thread for drivetrain to respond to joystick movements
void drivetrainControl() {
  while (true) {
    //set speed based on inputs
    setDrivetrainSpeed(getLeftSpeedInLinear(), getRightSpeedInLinear());
    setDrivetrainStopping();
    stopTimer++;
    startBalance();
    wait(10, msec);
  }
}

//EXPERIMENTAL
void startBalance(){
  double pitch = getInertialPitch();
  if(pitch > 22 && getBPos()){
    while(pitch > 22){
      int speed = pitch / 5;
      setDrivetrainSpeed(speed, speed);
      pitch = getInertialPitch();
      wait(10, msec);
    }
    while(pitch > 3){
      int speed = pitch / 10;
      setDrivetrainSpeed(speed, speed);
      pitch = getInertialPitch();
      wait(10, msec);
    }
  }
}

// setters

//sets speed of drivetrain based on left and right velocity inputs
void setDrivetrainSpeed(int leftSpeed, int rightSpeed) {
  leftFrontDrive.spin(fwd, leftSpeed, volt);
  leftMiddleDrive.spin(fwd, leftSpeed, volt);
  leftBackDrive.spin(fwd, leftSpeed, volt);
  rightFrontDrive.spin(fwd, rightSpeed, volt);
  rightMiddleDrive.spin(fwd, rightSpeed, volt);
  rightBackDrive.spin(fwd, rightSpeed, volt);
}

void setDrivetrainStopping(){
  if(stopTimer > 100 && (abs(getLeftMiddleVelocity()) > 0 || abs(getRightBackVelocity()) > 0)){
    setDrivetrainLock();
    if(getAxis3Pos() != 0)
      stopTimer = 0;
  } else{
    setDrivetrainCreep();
  }
}

void setDrivetrainCreep() {
  leftFrontDrive.setStopping(coast);
  leftMiddleDrive.setStopping(coast);
  leftBackDrive.setStopping(coast);
  rightFrontDrive.setStopping(coast);
  rightMiddleDrive.setStopping(coast);
  rightBackDrive.setStopping(coast);
}
void setDrivetrainLock() {
  leftFrontDrive.setStopping(brake);
  leftMiddleDrive.setStopping(brake);
  leftBackDrive.setStopping(brake);
  rightFrontDrive.setStopping(brake);
  rightMiddleDrive.setStopping(brake);
  rightBackDrive.setStopping(brake);
}

void setDrivetrainHold() {
  leftFrontDrive.setStopping(hold);
  leftMiddleDrive.setStopping(hold);
  leftBackDrive.setStopping(hold);
  rightFrontDrive.setStopping(hold);
  rightMiddleDrive.setStopping(hold);
  rightBackDrive.setStopping(hold);
}

// getters

//gets movement speed based on joystick location and
//converts to voltage evenly
double getLeftSpeedInLinear() {
  double rawSpeed = (getAxis3Pos() + getAxis4Pos());
  return rawSpeed/voltageConverstion;
}

double getRightSpeedInLinear() {
  double rawSpeed = (getAxis3Pos() - getAxis4Pos());
  return rawSpeed/voltageConverstion;
}

//gets movement speed based on joystick location and 
//runs through a quadratic to slew
int getLeftSpeedInSlew() {
  int newVal;
  int rawVal = getAxis3Pos() + getAxis4Pos();
  if(rawVal > 0)
  {
    newVal = quadraticA * pow(rawVal, powerRatioB);
  }
  else
  {
    newVal = quadraticA * pow(rawVal, powerRatioB);
  }
  return newVal;
}
int getRightSpeedInSlew() {
  int newVal;
  int rawVal = getAxis3Pos() - getAxis4Pos();
  if(rawVal > 0)
  {
    newVal = quadraticA * pow(rawVal, powerRatioB);
  }
  else
  {
    newVal = quadraticA * pow(rawVal, powerRatioB);
  }
  return newVal;
}

int getLeftFrontVelocity() {return leftFrontDrive.velocity(rpm);}
int getLeftMiddleVelocity() {return leftMiddleDrive.velocity(rpm);}
int getLeftBackVelocity() {return leftBackDrive.velocity(rpm);}
int getRightFrontVelocity() {return rightFrontDrive.velocity(rpm);}
int getRightMiddleVelocity() {return rightMiddleDrive.velocity(rpm);}
int getRightBackVelocity() {return rightBackDrive.velocity(rpm);}

double getInertialRotation() { return inert.rotation();}
double getInertialHeading() { return inert.heading();}
double getInertialPitch() {return inert.pitch();}

double getVerticalEncoderRotation() { return -1 * verticalTracker.rotation(deg); }
double getHorizontalEncoderRotation() { return -1 * horizontalTracker.rotation(deg); }

double getVerticalEncoderVelocity() { return verticalTracker.velocity(rpm); }
double getHorizontalEncoderVelocity() { return -1 * horizontalTracker.velocity(rpm); }

int getLeftFrontTemp() {return leftFrontDrive.temperature(celsius);}
int getLeftMiddleTemp() {return leftMiddleDrive.temperature(celsius);}
int getLeftBackTemp() {return leftBackDrive.temperature(celsius);}
int getRightFrontTemp() {return rightFrontDrive.temperature(celsius);}
int getRightMiddleTemp() {return rightMiddleDrive.temperature(celsius);}
int getRightBackTemp() {return rightBackDrive.temperature(celsius);}

// control

//reset all Motors
void resetDrivetrain() {
  leftFrontDrive.resetRotation();
  leftMiddleDrive.resetRotation();
  leftBackDrive.resetRotation();
  rightFrontDrive.resetRotation();
  rightMiddleDrive.resetRotation();
  rightBackDrive.resetRotation();
}

void resetEncoders() {
  verticalTracker.resetRotation();
  horizontalTracker.resetRotation();
}

//calibrate inertial sensor for preauton
void calibrateInertial() {
  inert.calibrate();
  while(inert.isCalibrating()) {
    wait(100, msec);
  }
}

void waitCalibrate(){
  while(inert.isCalibrating()) {
    wait(100, msec);
  }
}

//checks tempeatures of all drive motors are returns in a string which motors are hot
std::string tempInfoDrive() {
  std::string tempReturn;
  int loopCounter = 0;
  if (getLeftBackTemp() > tempLimit)
    tempReturn = "LF ";
    loopCounter++;
  if (getLeftMiddleTemp() > tempLimit)
    tempReturn += "LM ";
    loopCounter++;
  if (getLeftBackTemp() > tempLimit)
    tempReturn += "LB ";
    loopCounter++;
  if (getRightFrontTemp() > tempLimit)
    tempReturn += "RF ";
    loopCounter++;
  if (getRightMiddleTemp() > tempLimit)
    tempReturn += "RM ";
    loopCounter++;
  if (getRightBackTemp() > tempLimit)
    tempReturn += "RB ";
    loopCounter++;
  if(loopCounter == 0)
    tempReturn = "All Good";
  return tempReturn;
}


// turn the robot based on absolute position from the original point of the robot
/*void drivetrainTurn(double targetdeg) {

   // proportionality constants
  double kP = 0.45;
  double kI = 0.0001;
  double kD = 0.01;

  // PID loop variables
  double error = 1;
  double integral = 0;
  double derivative = 0;
  double prevError = 0;
  double motorPower = 0;
  bool useright = true;
  while (fabs(targetdeg - getInertialHeading()) > 2) {
    // PID loop to determine motorPower at any given point in time
    double head = getInertialHeading();
    double errorright = targetdeg - head;
    if (targetdeg < head) {
      errorright = 360 - head + targetdeg;
    }
    double errorleft = fabs(targetdeg - head);
    if (targetdeg > head) {
      errorleft = 360 + head - targetdeg;
    }
    if (errorright < errorleft) {
      error = errorright;
      useright = true;
    } else {
      error = errorleft;
      useright = false;
    }
    // pid stuff
    integral = integral + error;
    if (error == 0 or error > targetdeg) {
      integral = 0;
    }
    derivative = error - prevError;
    motorPower = (error * kP + integral * kI + derivative * kD);
    prevError = error;

    wait(15, msec);

    // powering the motors
    if (useright) {
      lFrontDrive.spin(fwd, -motorPower, pct);
      lMiddleDrive.spin(fwd, -motorPower, pct);
      lBackDriveBackLift.spin(fwd, motorPower, pct);
      rMiddleDrive.spin(fwd, motorPower, pct);
      rFrontDrive.spin(fwd, motorPower, pct);
      rBackDriveCascadeLift.spin(fwd, -motorPower, pct);
    } else {
      lFrontDrive.spin(fwd, motorPower, pct);
      lMiddleDrive.spin(fwd, motorPower, pct);
      lBackDriveBackLift.spin(fwd, -motorPower, pct);
      rMiddleDrive.spin(fwd, -motorPower, pct);
      rFrontDrive.spin(fwd, -motorPower, pct);
      rBackDriveCascadeLift.spin(fwd, motorPower, pct);
    }
  }
  lMiddleDrive.stop();
  rMiddleDrive.stop();
  lFrontDrive.stop();
  rFrontDrive.stop();
  rBackDriveCascadeLift.stop();
  lBackDriveBackLift.stop();

}

//drive movement based on time
void timeDrive(double speed, int timeLength) {
  lFrontDrive.spin(fwd, speed, volt);
  rFrontDrive.spin(fwd, speed, volt);
  lMiddleDrive.spin(fwd, speed, volt);
  rMiddleDrive.spin(fwd, speed, volt);
  lBackDriveBackLift.spin(fwd, -speed, volt);
  rBackDriveCascadeLift.spin(fwd, -speed, volt);

  wait(timeLength, msec);

  lFrontDrive.stop();
  rFrontDrive.stop();
  lMiddleDrive.stop();
  rMiddleDrive.stop();
  lBackDriveBackLift.stop();
  rBackDriveCascadeLift.stop();
}

//turn based on different left and right speed to move in a curve
void arcturn (double left, double right, double turnangle) {
  while (getInertialHeading() < turnangle - 2 || getInertialHeading() > turnangle + 2) {
    lFrontDrive.spin(fwd, left, volt);
    lMiddleDrive.spin(fwd, left, volt);
    rFrontDrive.spin(fwd, right, volt);
    rMiddleDrive.spin(fwd, right, volt);
    wait(10, msec);
  }
  lFrontDrive.stop();
  rFrontDrive.stop();
  lMiddleDrive.stop();
  rMiddleDrive.stop();
}

void arcturnTime (double left, double right, int length) {
  lFrontDrive.spin(fwd, left, volt);
  lMiddleDrive.spin(fwd, left, volt);
  rFrontDrive.spin(fwd, right, volt);
  rMiddleDrive.spin(fwd, right, volt);
  wait(length, msec);
  lFrontDrive.stop();
  rFrontDrive.stop();
  lMiddleDrive.stop();
  rMiddleDrive.stop();
}*/