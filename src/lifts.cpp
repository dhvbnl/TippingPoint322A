#include "vex.h"

int pnumaticDelayRear = 0;
int pnumaticDelayFront = 0;
int intakeDelay = 0;
int previousTarget = 0;

bool intakeState = false;

int liftControl() {
  wait(100, msec);
  previousTarget = getFourBarPot();
  while (true) {
    //setFourBarSpeed(getFourBarSpeed());
    setIntakeSpeed();
    setRearClamp();
    setFrontClamp();
    //Controller.Screen.clearLine();
    //Controller.Screen.print(getFourBarPos());
    setFourBarPosition(getFourBarPos());
    wait(10, msec);
  }
}

void setFourBarSpeed(int speed) {
  fourBar.spin(fwd, speed / voltageConverstion, volt);
}

void setFourBarPosition(int pos){
  setFourBarSpeed(3 * (pos - getFourBarPot()));
}

void setIntakeSpeed() {
  if (getAPos() && intakeDelay > 20) {
    if (!intakeState) {
      intake.spin(fwd, 12, volt);
      intakeState = true;
    } else {
      intake.stop();
      intakeState = false;
    }
    intakeDelay = 0;
  } else {
    intakeDelay++;   
  }
}

void setRearClamp() {
  if (getRightPos() && pnumaticDelayRear > 20) {
    rearClamp.set(!rearClamp.value());
    pnumaticDelayRear = 0;
  } else {
    pnumaticDelayRear++;
  }
}

void setFrontClamp() {
  if (getYPos() && pnumaticDelayFront > 20) {
    frontClamp.set(!frontClamp.value());
    pnumaticDelayFront = 0;
  } else {
    pnumaticDelayFront++;
  }
}

int getFourBarSpeed() {
  int potVal = getFourBarPot();
  int returnVal = getAxis2Pos();
  if (returnVal > 0)
    return returnVal > 345 - potVal ? 1.5 * (345 - potVal) : returnVal;
  else if (returnVal < 0)
    return returnVal < 126 - potVal ? 3 * (128 - potVal) : returnVal;
  else
    return 0;
}

int getFourBarPos() {
  int axisPos = getAxis2Pos()/ 50;
  int currentPos = getFourBarPot();
  if (axisPos > 0){
    currentPos = axisPos + previousTarget > 345 ? 345 : axisPos + previousTarget; 
    previousTarget = currentPos;
  } else if (axisPos < 0) {
    currentPos = axisPos + previousTarget < 126 ? 126 : axisPos + previousTarget;
    previousTarget = currentPos;
  } else{
    currentPos = previousTarget;
  }
  return currentPos;
}

int getFourBarPot() { return fourBarPot.value(range10bit); }