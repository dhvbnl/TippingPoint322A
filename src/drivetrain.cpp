#include "vex.h"

bool mBackDriveLiftTransmissionState = false;
bool MFrontLiftCylinderState = false;

//thread for drivetrain to respond to joystick movements
void drivetrainControl() {
  while (true) {
    //set speed based on inputs
    setDrivetrainSpeed(getLeftSpeedInLinear(), getRightSpeedInLinear());
    if( getYPos()){
      setMFrontLiftCylinder();
    } else if (getRightPos()){
      setMBackDriveLiftTranmission();
    }
    
    wait(10, msec);
  }
}

// setters

//sets speed of drivetrain based on left and right velocity inputs
void setDrivetrainSpeed(int leftSpeed, int rightSpeed) {
  lFrontDrive.spin(fwd, leftSpeed, volt);
  lMiddleDrive.spin(fwd, leftSpeed, volt);
  rMiddleDrive.spin(fwd, rightSpeed, volt);
  rFrontDrive.spin(fwd, rightSpeed, volt);
  if(!mBackDriveLift.value() && lBackTransmission.value() && rBackTransmission.value()){
    lBackDriveBackLift.spin(reverse, leftSpeed, volt);
    rBackDriveCascadeLift.spin(reverse, rightSpeed, volt);
    }
}

void setMBackDriveLiftTranmission(){
    mBackDriveLiftTransmissionState ^= true; 
    mBackDriveLift.set(mBackDriveLiftTransmissionState);
    rBackDriveCascadeLift.stop();
    wait(200, msec);
}

void setMFrontLiftCylinder(){
    MFrontLiftCylinderState ^= true; 
    mFrontLift.set(MFrontLiftCylinderState);
    wait(200, msec);
}

void setDrivetrainCreep() {
  lFrontDrive.setStopping(coast);
  lMiddleDrive.setStopping(coast);
  rMiddleDrive.setStopping(coast);
  rFrontDrive.setStopping(coast);
}
void setDrivetrainLock() {
  lFrontDrive.setStopping(brake);
  lMiddleDrive.setStopping(brake);
  rMiddleDrive.setStopping(brake);
  rFrontDrive.setStopping(brake);
}

void setDrivetrainHold() {
  lFrontDrive.setStopping(hold);
  lMiddleDrive.setStopping(hold);
  rMiddleDrive.setStopping(hold);
  rFrontDrive.setStopping(hold);
}

// getters

//gets movement speed based on joystick location and
//converts to voltage evenly
int getLeftSpeedInLinear() {
  return (getAxis3Pos() - getAxis4Pos()) / voltageConverstion;
}

int getRightSpeedInLinear() {
  return (getAxis3Pos() + getAxis4Pos()) / voltageConverstion;
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

int getlFrontDriveSpeed() {return lFrontDrive.velocity(pct);}
int getlMiddleDriveSpeed() {return lMiddleDrive.velocity(pct);}
int getrMiddleDriveSpeed() {return rMiddleDrive.velocity(pct);}
int getrFrontDriveSpeed() {return rFrontDrive.velocity(pct);}

double getInertialRotation() { return mInertial.rotation();}
double getInertialHeading() { return mInertial.heading();}

double getLeftEncoderRotation() { return lTraker.rotation(deg); }
double getRightEncoderRotation() { return rTracker.rotation(deg); }

int getlFrontDriveTemp() {return lFrontDrive.temperature(celsius);}
int getlMiddleDriveTemp() {return lMiddleDrive.temperature(celsius);}
int getrMiddleDriveTemp() {return rMiddleDrive.temperature(celsius);}
int getrFrontDriveTemp() {return rFrontDrive.temperature(celsius);}

// control

//reset all Motors
void resetDrivetrain() {
  lFrontDrive.resetRotation();
  lMiddleDrive.resetRotation();
  rMiddleDrive.resetRotation();
  rFrontDrive.resetRotation();
}

void resetEncoders() {
  lTraker.resetRotation();
  rTracker.resetRotation();
  encoderH.resetRotation();
}

//calibrate inertial sensor for preauton
void calibrateInertial() {
  mInertial.calibrate();
  while(mInertial.isCalibrating())
    wait(100, msec);
}

//checks tempeatures of all drive motors are returns in a string which motors are hot
std::string tempInfoDrive() {
  std::string tempReturn;
  int loopCounter = 0;
  if (getlFrontDriveTemp() > tempLimit)
    tempReturn = "LF ";
    loopCounter++;
  if (getlMiddleDriveTemp() > tempLimit)
    tempReturn += "LR ";
    loopCounter++;
  if (getrMiddleDriveTemp() > tempLimit)
    tempReturn += "RB ";
    loopCounter++;
  if (getrFrontDriveTemp() > tempLimit)
    tempReturn += "RF ";
    loopCounter++;
  if(loopCounter == 0)
    tempReturn = "All Good";
  return tempReturn;
}


// turn the robot based on absolute position from the original point of the robot
void drivetrainTurn(double targetdeg) {
   // proportionality constants
  double kP = 0.42;
  double kI = 0.0012;
  double kD = 0.6;

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
      lFrontDrive.spin(fwd, motorPower, pct);
      lMiddleDrive.spin(fwd, motorPower, pct);
      rMiddleDrive.spin(fwd, -motorPower, pct);
      rFrontDrive.spin(fwd, -motorPower, pct);
    } else {
      lFrontDrive.spin(fwd, -motorPower, pct);
      lMiddleDrive.spin(fwd, -motorPower, pct);
      rMiddleDrive.spin(fwd, motorPower, pct);
      rFrontDrive.spin(fwd, motorPower, pct);
    }
  }
  lMiddleDrive.stop();
  rMiddleDrive.stop();
  lFrontDrive.stop();
  rFrontDrive.stop();
}

//drive movement based on time
void timeDrive(double speed, int timeLength) {
  lFrontDrive.spin(fwd, speed, volt);
  rFrontDrive.spin(fwd, speed, volt);
  lMiddleDrive.spin(fwd, speed, volt);
  rMiddleDrive.spin(fwd, speed, volt);
  wait(timeLength, msec);
  lFrontDrive.stop();
  rFrontDrive.stop();
  lMiddleDrive.stop();
  rMiddleDrive.stop();
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
}