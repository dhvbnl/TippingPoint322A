#include "vex.h"

const int lowerBound = 1450;
const int ringHeight = 1650;
const int seasawHeight = 2285;
const int upperBound = 2520;

const int armBoundsDeg = 1270;
const int ringHeightDiff = 300;
const int seasawHeightDiff = 1075;

int armPos;

int pnumaticDelayRear = 0;
int pnumaticDelayFront = 0;
int intakeDelay = 0;
int previousTarget = lowerBound;
int lastPos = lowerBound;
int holdDelayFourBar = 0;
int macroDelay;

int bottomBoundFourBar;
int topBoundFourBar;
int ringHeightDeg;
int seesawHeightDeg;

thread macro;
bool macroRun = false;
bool intakeOverride = false;
bool intakeState = false;
bool runIntake = false;

int liftControl() {
  fourBar.setBrake(coast);
  findBottomBound();
  while (true) {
    setFourBarSpeedHolding(getFourBarSpeed());
    setIntakeSpeed();
    setRearClamp();
    setFrontClamp();
    wait(20, msec);
  }
}

void setFourBarSpeed(int speed) {
  fourBar.spin(fwd, speed / voltageConverstion, volt);
}

void setFourBarSpeedHolding(int speed) {
  if (macroDelay > 50) {
    if (getBPos()) {
      fourBarGround();
      macroDelay = 0;
      return;
    } else if (getAPos()) {
      fourBarRing();
      macroDelay = 0;
      return;
    } else if (getXPos()) {
      fourBarSeasaw();
      macroDelay = 0;
      return;
    }
  } else{
    macroDelay++;
  }
  if (macroRun)
    return;
  if (speed != 0) {
    setFourBarSpeed(speed);
    lastPos = getFourBarCurPos();
  } else {
    setFourBarPosition(lastPos);
  }
}

void setFourBarPosition(int pos) {
  setFourBarSpeed(1.25 * (pos - getFourBarCurPos()));
}

void setFourBarIntakeAuton() {
  while (taskStop()) {
    setFourBarPosition(armPos);
    if (runIntake) {
      intake.spin(fwd, 12, volt);
      if (intakeDelay > 15 && intake.velocity(pct) < 10) {
        runIntake = false;
      }
      intakeDelay++;
    } else {
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
    if (rearClampLimit.pressing() && getFourBarPot() > lowerBound + 40 &&
        (getFourBarPot() < 2200 || frontClamp.value() == 0) &&
        rearRingCheck.value(pct) > 65) {
      intake.spin(fwd, 12, volt);
    } else {
      intake.stop();
    }
  } else {
    if (getR1Pos() && intakeDelay > 20) {
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

  if (getR2Pos() && intakeDelay > 20) {
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
    frontClamp.set(!frontClamp.value());
    pnumaticDelayFront = 0;
  } else {
    pnumaticDelayFront++;
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
    fourBar.spin(fwd, -5, volt);
    wait(200, msec);
  } while (fourBar.torque() < 0.8 && fabs(fourBar.velocity(pct)) > 10);
  fourBar.stop();
  bottomBoundFourBar = getFourBarCurPos() + 35;
  topBoundFourBar = bottomBoundFourBar + armBoundsDeg;
  ringHeightDeg = bottomBoundFourBar + ringHeightDiff;
  seesawHeightDeg = bottomBoundFourBar + seasawHeightDiff;
  lastPos = bottomBoundFourBar;
}