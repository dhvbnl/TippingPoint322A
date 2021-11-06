#include "vex.h"

//thread for drivetrain to respond to joystick movements
void drivetrainControl() {
  while (true) {
    //set speed based on inputs
    setDrivetrainSpeed(getLeftSpeedInLinear(), getRightSpeedInLinear());
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
  return (getAxis3Pos() + getAxis4Pos()) / voltageConverstion;
}

int getRightSpeedInLinear() {
  return (getAxis3Pos() - getAxis4Pos()) / voltageConverstion;
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