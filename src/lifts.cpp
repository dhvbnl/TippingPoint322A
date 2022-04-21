#include "vex.h"

const int lowerBound = 1450;
//const int ringHeight = 1650;
//const int seasawHeight = 2285;
const int upperBound = 2520;

const int armBoundsDeg = 650;
const int ringHeightDiff = 150;
const int seasawHeightDiff = 500;

int armPos;

int pnumaticDelayRear = 0;
int pnumaticDelayFront = 0;
int pnumaticDelayCover = 0;
int intakeDelay = 0;
int previousTarget = lowerBound;
int lastPos = lowerBound;
int holdDelayFourBar = 0;
int macroDelay;

int bottomBoundFourBar = -1;
int topBoundFourBar;
int ringHeightDeg;
int seesawHeightDeg;

thread macro;
bool macroRun = false;
bool intakeOverride = false;
int intakeState = 0;
int runIntake = 0;
bool calibrated = false;
int intakeSpeed = 0;

int calibrateDelay = 0;

int liftControl() {
  fourBar.setBrake(coast);
  //findBottomBound();
  if (bottomBoundFourBar == -1){
    findBottomBound();
  }
  lastPos = getFourBarCurPos();
  while (true) {
    setFourBarSpeedHolding(getFourBarSpeed());
    setIntakeSpeed();
    setRearClamp();
    setFrontClamp();
    setGoalCover();
    wait(20, msec);
  }
}

void setFourBarSpeed(double speed) {
  fourBar.spin(fwd, speed / voltageConverstion, volt);
}

void setFourBarSpeedHolding(double speed) {
  if (getBPos()) {
    lastPos = bottomBoundFourBar;
  } else if (getAPos()) {
    lastPos = ringHeightDeg;
  } else if (getXPos()) {
    lastPos = seesawHeightDeg;
  }
  if(getUpPos() && calibrateDelay){
    findBottomBound();
    calibrateDelay = 0;
  } else{
    calibrateDelay++;
  }
  speed = speed + (speed * voltageConverstion - fourBar.velocity(pct));
  if (speed > 0) {
    
    setFourBarSpeed(speed);
    lastPos = getFourBarCurPos();
  } else if(speed < 0) {
    setFourBarSpeed(speed);
    lastPos = getFourBarCurPos();
  } else {
    setFourBarPosition(lastPos);
  }
}

void setFourBarPosition(int pos) {
  setFourBarSpeed(1 * (pos - getFourBarCurPos()));
}

void setFourBarIntakeAuton() {
  while (taskStop()) {
    setFourBarPosition(armPos);
    if (runIntake == 1) {
      intake.spin(fwd, 12, volt);
      if (intakeDelay > 15 && intake.velocity(pct) < 10) {
        runIntake = 0;
      }
      intakeDelay++;
    } else if (runIntake == 2) {
      intake.spin(fwd, -12, volt);
      wait(300, msec);
      runIntake = 3;
    } else if (runIntake == 3) {
      while(intakeLineTracker.value(pct) > 40){
        intake.spin(fwd, 12, volt);
        wait(20, msec);
      }
      runIntake = 0;
    } else {
      intake.stop();
    }
    wait(30, msec);
  }
}

void changeArmPos(int pos) { armPos = pos + bottomBoundFourBar; }

void intakeMove(int start) {
  runIntake = start;
  intakeDelay = 0;
}

void fourBarGround() {
  macroRun = true;
  while ((getFourBarCurPos() < bottomBoundFourBar ||
          getFourBarCurPos() > bottomBoundFourBar + 8) &&
         getAxis2Pos() == 0 && !buttonPressed()) {
    setFourBarSpeed(1.25 * (bottomBoundFourBar - getFourBarCurPos()));
    wait(20, msec);
  }
  lastPos = getFourBarCurPos();
  macroRun = false;
}

void fourBarRing() {
  macroRun = true;
  while ((getFourBarCurPos() < ringHeightDeg - 5 ||
          getFourBarCurPos() > ringHeightDeg + 5) &&
         getAxis2Pos() == 0 && !buttonPressed()) {
    setFourBarSpeed(1.25 * (ringHeightDeg - getFourBarCurPos()));
    wait(20, msec);
  }
  lastPos = getFourBarCurPos();
  macroRun = false;
}

void fourBarSeasaw() {
  macroRun = true;
  while ((getFourBarCurPos() < seesawHeightDeg - 5 ||
          getFourBarCurPos() > seesawHeightDeg + 5) &&
         getAxis2Pos() == 0 && !buttonPressed()) {
    setFourBarSpeed(2 * (seesawHeightDeg - getFourBarCurPos()));
    wait(20, msec);
  }
  lastPos = getFourBarCurPos();
  macroRun = false;
}

void setIntakeSpeed() {
  if (!intakeOverride) {
    if (rearClampLimit.pressing() && (getFourBarCurPos() > bottomBoundFourBar + 100 && !(getFourBarCurPos() > topBoundFourBar - 100 && frontLineTracker.value(pct) < 60))) {
      intakeSpeed = 12;
    } else {
      intakeSpeed = 0;
    }
  } else {
    if (getR1Pos() && intakeDelay > 20) {
      if (intakeState == 0) {
        intakeSpeed = 12;
        intakeState = 1;
      } else if(intakeState == 1){
        intakeSpeed = -12;
        intakeState = 2;
      } else if(intakeState == 2){
        intakeSpeed = 0;
        intakeState = 0;
      }
      intakeDelay = 0;
    } else {
      intakeDelay++;
    }
  }

  if (getR2Pos() && intakeDelay > 20) {
    intakeOverride ^= true;
    intakeSpeed = 0;
    intakeDelay = 0;
    intakeState = 0;
  } else {
    intakeDelay++;
  }
  
  intake.spin(fwd, intakeSpeed, volt);
}

void setRearClamp() {
  if (getL2Pos() && pnumaticDelayRear > 20) {
    rearClamp.set(!rearClamp.value());
    pnumaticDelayRear = 0;
    // thread check(rearClampCheck);

  } else {
    pnumaticDelayRear++;
  }
}

void setRearClampAuton() { rearClamp.set(!rearClamp.value()); }

void rearClampCheck() {
  wait(1000, msec);
  if (rearClamp.value() == 0 && !rearClampLimit.pressing())
    rearClamp.set(!rearClamp.value());
}

void setFrontClamp() {
  if ((getL1Pos() && pnumaticDelayFront > 20)) {
    frontClampStandoff.set(!frontClampStandoff.value());
    wait(50, msec);
    frontClamp.set(!frontClamp.value());
    pnumaticDelayFront = 0;
  } else {
    pnumaticDelayFront++;
  }
}

void setGoalCover(){
  if ((getRightPos() && pnumaticDelayCover > 20)) {
    goalCover.set(!goalCover.value());
    pnumaticDelayCover = 0;
  } else {
    pnumaticDelayCover++;
  }
}

void setFrontClampAuton() { frontClamp.set(!frontClamp.value()); }

int getFourBarSpeed() {
  int armVal = getFourBarCurPos();
  int returnVal = getAxis2Pos();
  if (returnVal > 0)
    return returnVal > topBoundFourBar - armVal
               ? 0.5 * (topBoundFourBar - armVal)
               : returnVal;
  else if (returnVal < 0)
    return returnVal < bottomBoundFourBar - armVal
               ? 0.5 * (bottomBoundFourBar - armVal)
               : returnVal;
  else
    return 0;
}

int getFourBarPos() {
  int axisPos = getAxis2Pos() / 10;
  int currentPos = getFourBarPot();
  if (axisPos > 0) {
    currentPos = axisPos + previousTarget > upperBound
                     ? upperBound
                     : axisPos + previousTarget;
    previousTarget = currentPos;
  } else if (axisPos < 0) {
    currentPos = axisPos + previousTarget < lowerBound
                     ? lowerBound
                     : axisPos + previousTarget;
    previousTarget = currentPos;
  } else {
    currentPos = previousTarget;
  }
  return currentPos;
}

int getFourBarPot() { return fourBarPot.value(range12bit); }

int getFourBarCurPos() { return fourBar.position(deg); }

bool buttonPressed() {
  if (getXPos() || getAPos() || getBPos()) {
    return true;
  }
  return false;
}

void findBottomBound() {
    do {
      fourBar.spin(fwd, -7, volt);
      wait(100, msec);
    } while (fourBar.torque() < 0.8);
    fourBar.stop();
    bottomBoundFourBar = getFourBarCurPos();
    topBoundFourBar = bottomBoundFourBar + armBoundsDeg;
    ringHeightDeg = bottomBoundFourBar + ringHeightDiff;
    seesawHeightDeg = bottomBoundFourBar + seasawHeightDiff;
    lastPos = bottomBoundFourBar;
    armPos = bottomBoundFourBar;
    calibrated = true;
}