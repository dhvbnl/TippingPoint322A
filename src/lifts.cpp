#include "vex.h"

const int lowerBound = 1475;
const int ringHeight = 1650;
const int seasawHeight = 2285;
const int upperBound = 2462;

int armPos = lowerBound;

int pnumaticDelayRear = 0;
int pnumaticDelayFront = 0;
int intakeDelay = 0;
int previousTarget = lowerBound;
int lastPos = lowerBound;
int holdDelayFourBar = 0;

thread macro;
bool macroRun = false;
bool intakeOverride = false;
bool intakeState = false;
bool runIntake = false;

int liftControl() {
  fourBar.setBrake(coast);
  while (true) {
    setFourBarSpeedHolding(getFourBarSpeed());
    setIntakeSpeed();
    setRearClamp();
    setFrontClamp();
    wait(30, msec);
  }
}

void setFourBarSpeed(int speed) {
  fourBar.spin(fwd, speed / voltageConverstion, volt);
}

void setFourBarSpeedHolding(int speed) {
  if (getBPos()) {
    macro.interrupt();
    thread macro(fourBarGround);
    wait(200, msec);
    return;
  } else if (getAPos()) {
    macro.interrupt();
    thread macro(fourBarRing);
    wait(200, msec);
    return;
  } else if (getXPos()) {
    macro.interrupt();
    thread macro(fourBarSeasaw);
    wait(200, msec);
    return;
  }
  if (macroRun)
    return;
  if (speed != 0) {
    setFourBarSpeed(speed);
    holdDelayFourBar = 0;
  } else if (holdDelayFourBar > 5) {
    setFourBarPosition(lastPos);
  } else if (holdDelayFourBar > 0) {
    setFourBarSpeed(0);
    lastPos = getFourBarPot();
    holdDelayFourBar++;
  } else {
    holdDelayFourBar++;
  }
}

void setFourBarPosition(int pos) {
  setFourBarSpeed(1.25 * (pos - getFourBarPot()));
}

void setFourBarIntakeAuton() {
  while (taskStop()) {
    setFourBarPosition(armPos);
    if(runIntake){
      intake.spin(fwd, 12, volt);
      if(intakeDelay > 15 && intake.velocity(pct) < 10){
        runIntake = false;
      }
      intakeDelay++;
    } else{
      intake.stop();
    }
    wait(30, msec);
  }
}

void changeArmPos(int pos) { armPos = pos; }

void intakeMove(bool start) {
  runIntake = start;
  intakeDelay = 0;
}

void fourBarGround() {
  macroRun = true;
  while ((getFourBarPot() < lowerBound || getFourBarPot() > lowerBound + 8) &&
         getAxis2Pos() == 0) {
    setFourBarSpeed(1.25 * (lowerBound - getFourBarPot()));
    wait(20, msec);
  }
  lastPos = getFourBarPot();
  macroRun = false;
}

void fourBarRing() {
  macroRun = true;
  while (
      (getFourBarPot() < ringHeight - 5 || getFourBarPot() > ringHeight + 5) &&
      getAxis2Pos() == 0) {
    setFourBarSpeed(1.25 * (ringHeight - getFourBarPot()));
    wait(20, msec);
  }
  lastPos = getFourBarPot();
  macroRun = false;
}

void fourBarSeasaw() {
  macroRun = true;
  while ((getFourBarPot() < seasawHeight - 5 ||
          getFourBarPot() > seasawHeight + 5) &&
         getAxis2Pos() == 0) {
    setFourBarSpeed(1.25 * (seasawHeight - getFourBarPot()));
    wait(20, msec);
  }
  lastPos = getFourBarPot();
  macroRun = false;
}

void setIntakeSpeed() {
  if (!intakeOverride) {
    if (rearClampLimit.pressing() && getFourBarPot() > lowerBound + 40 &&
        (getFourBarPot() < 2200 || frontClamp.value() == 0)) {
      intake.spin(fwd, 12, volt);
    } else {
      intake.stop();
    }
  } else {
    if (getL1Pos() && intakeDelay > 20) {
      if (!intakeState) {
        intake.spin(fwd, 12, volt);
        intakeState = true;
      } else {
        intake.stop();
        intakeState = false;
      }
      intakeDelay = 0;
    } else{
      intakeDelay++;
    }
  }

  if (getL2Pos() && intakeDelay > 20) {
    intakeOverride ^= true;
    intake.spin(fwd, intake.isSpinning() ? 0 : 12, volt);
    intakeDelay = 0;
  } else {
    intakeDelay++;
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
    thread check(rearClampCheck);

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
  if ((getYPos() && pnumaticDelayFront > 20)) {
    frontClamp.set(!frontClamp.value());
    pnumaticDelayFront = 0;
  } else {
    pnumaticDelayFront++;
  }
}

void setFrontClampAuton() { frontClamp.set(!frontClamp.value()); }

int getFourBarSpeed() {
  int potVal = getFourBarPot();
  int returnVal = getAxis2Pos();
  if (returnVal > 0)
    return returnVal > upperBound - potVal ? 1.5 * (upperBound - potVal)
                                           : returnVal;
  else if (returnVal < 0)
    return returnVal < lowerBound - potVal ? 2 * (lowerBound - potVal)
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