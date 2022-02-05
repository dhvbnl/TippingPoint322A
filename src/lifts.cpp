#include "vex.h"

int liftControl() {

  while (true) {
    setFourBarSpeed(getFourBarSpeed());
    wait(10, msec);
  }
}

void setFourBarSpeed(int speed) {
  fourBar.spin(fwd, speed / voltageConverstion, volt);
}

int getFourBarSpeed() {
  int potVal = getFourBarPot();
  int returnVal = getAxis2Pos();
  if (returnVal > 0)
    return returnVal > 345 - potVal ? 1.5 * (345 - potVal) : returnVal;
  else if (returnVal < 0)
    return returnVal < 128 - potVal ? 1.5 * (128 - potVal) : returnVal;
  else
    return 0;
}

int getFourBarPot() { return fourBarPot.value(range10bit); }