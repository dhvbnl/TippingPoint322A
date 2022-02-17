#include "vex.h"

const int lowerBound = 1475;
const int upperBound = 2462;

int pnumaticDelayRear = 0;
int pnumaticDelayFront = 0;
int intakeDelay = 0;
int previousTarget = lowerBound;
int lastPos = lowerBound;
int holdDelayFourBar = 0;

bool intakeState = false;

int liftControl() {
  while (true) {
    setFourBarSpeedHolding(getFourBarSpeed());
    setIntakeSpeed();
    setRearClamp();
    setFrontClamp();
    //Controller.Screen.clearLine();
    //Controller.Screen.print(fourBar.velocity(pct));
    //setFourBarPosition(getFourBarPos());
    wait(10, msec);
  }
}

void setFourBarSpeed(int speed) {
  fourBar.spin(fwd, speed / voltageConverstion, volt);
}

void setFourBarSpeedHolding(int speed){
  if (speed != 0) {
    setFourBarSpeed(speed);
    holdDelayFourBar = 0;
  } else if(holdDelayFourBar > 10){
    setFourBarPosition(lastPos);
  } else if(holdDelayFourBar > 0){
    setFourBarSpeed(0);
    lastPos = getFourBarPot();
    holdDelayFourBar++;
  } else{
    holdDelayFourBar++;
  }
}

void setFourBarPosition(int pos){
  setFourBarSpeed(1.25 * (pos - getFourBarPot()));
}

void setIntakeSpeed() {
  if(rearClampLimit.pressing() && getFourBarPot() > lowerBound + 40 && (getFourBarPot() < 2080 || frontClamp.value() == 0)){
    intake.spin(fwd, 12, volt);
  }else{
    intake.stop();
  }
  /*if (getAPos() && intakeDelay > 20) {
    if (!intakeState && rearClampLimit.pressing()) {
      intake.spin(fwd, 12, volt);
      intakeState = true;
    } else {
      intake.stop();
      intakeState = false;
    }
    intakeDelay = 0;
  } else {
    intakeDelay++;   
  }*/
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
  if (getYPos() && pnumaticDelayFront > 50) {
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
    return returnVal > upperBound - potVal ? 1.5 * (upperBound - potVal) : returnVal;
  else if (returnVal < 0)
    return returnVal < lowerBound - potVal ? 2 * (lowerBound - potVal) : returnVal;
  else
    return 0;
}

int getFourBarPos() {
  int axisPos = getAxis2Pos()/ 10;
  int currentPos = getFourBarPot();
  if (axisPos > 0){
    currentPos = axisPos + previousTarget > upperBound ? upperBound : axisPos + previousTarget; 
    previousTarget = currentPos;
  } else if (axisPos < 0) {
    currentPos = axisPos + previousTarget < lowerBound ? lowerBound : axisPos + previousTarget;
    previousTarget = currentPos;
  } else{
    currentPos = previousTarget;
  }
  return currentPos;
}

int getFourBarPot() { return fourBarPot.value(range12bit); }