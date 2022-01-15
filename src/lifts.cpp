#include "vex.h"

int liftControl() {
  
  while (true) {
    setRearCascadeSpeed(getRearCascadeSpeed());
    if(mBackDriveLift.value() && !lBackTransmission.value() && !rBackTransmission.value()){
      setRearLiftSpeed(getRearLiftSpeed());
      setRearLiftBrake();

      setRearCascadeSpeed(getRearCascadeSpeed());
    }
    wait(10, msec);
  }
}

void setRearLiftSpeed(int speed) {
  lBackDriveBackLift.spin(fwd, speed, volt); 
}

void setRearCascadeSpeed(int speed) {
  rBackDriveCascadeLift.spin(fwd, speed, volt); 
}

void setRearLiftBrake(){
  int potVal = getBackLiftPot();
  if(potVal < 12 || potVal > 38 || getlFrontDriveVoltage() > 0)
    lBackDriveBackLift.setBrake(brake);
  else
    lBackDriveBackLift.setBrake(coast);
}

int getRearLiftSpeed() {
  int potVal = getBackLiftPot();
  if (getR1Pos() && potVal > tBondRearLift) {
    return 0.3 * (potVal - tBondRearLift) + 2;
  } else if (getR2Pos() && potVal < bBondRearLift) {
    return 0.5 * (potVal - bBondRearLift) - 2;
  } else {
    return 0;
  }
}

int getRearCascadeSpeed() {
  if(getL1Pos()){
    return -12;
  }
  else if(getL2Pos()){
    return 12;
  }
  else{
    return 0;
  }
}


int getlFrontDriveVoltage() {return lBackDriveBackLift.voltage();}

int getBackLiftPot() { return lBackLift.value(pct); }