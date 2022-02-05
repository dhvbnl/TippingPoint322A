#include "vex.h"

int liftControl() {

  while (true) {
    Controller.Screen.clearLine();
    Controller.Screen.print(getFourBarPot());
    setFourBarSpeed(getFourBarSpeed());
    wait(50, msec);
  }
}

void setFourBarSpeed(int speed) {
  fourBar.spin(fwd, speed / voltageConverstion, volt);
}

int getFourBarSpeed() {
  int potVal = getFourBarPot();
  int returnVal = getAxis2Pos();
  if (returnVal > 0)
    return returnVal > 345 - potVal ? 1 * (345 - potVal) : returnVal;
  else if (returnVal < 0)
    return returnVal < 128 - potVal ? 1 * (128 - potVal) : returnVal;
  else
    return 0;

  /*if (getL1Pos() && potVal > tBondRearLift) {
    return -(0.3 * (potVal - tBondRearLift) + 2);
  } else if (getL2Pos() && potVal < bBondRearLift) {
    return -(0.5 * (potVal - bBondRearLift) - 2);
  } else {
    return 0;
  }*/
}

int getFourBarPot() { return fourBarPot.value(range10bit); }