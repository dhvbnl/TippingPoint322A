#include "vex.h"

int liftControl() {
  mFrontIntakeBackDlift.setBrake(hold);
  while (true) {
    //setRearCascadeSpeed(getRearCascadeSpeed());
    if(mBackDriveLift.value() && !lBackTransmission.value() && !rBackTransmission.value()){
      setRearLiftSpeed(getRearLiftSpeed());
      setRearLiftBrake();
       
      //setRearCascadeSpeed(getRearCascadeSpeed());
    }
    setFrontSixBarSpeed(getFrontSixBarSpeed());
    wait(10, msec);
  }
}

void setRearLiftSpeed(int speed) {
  lBackDriveBackLift.spin(fwd, speed, volt); 
}

void setRearCascadeSpeed(int speed) {
  rBackDriveCascadeLift.spin(fwd, speed, volt); 
}

void setFrontSixBarSpeed(int speed) {
  mFrontIntakeBackDlift.spin(fwd, -speed, volt); 
}

void setRearLiftBrake(){
  int potVal = getBackLiftPot();
  if(potVal < 12 || potVal > 38 || getlFrontDriveVoltage() > 0)
    lBackDriveBackLift.setBrake(hold);
  else
    lBackDriveBackLift.setBrake(coast);
}

int getRearLiftSpeed() {
  int potVal = getBackLiftPot();
  if (getL1Pos() && potVal > tBondRearLift) {
    return -(0.3 * (potVal - tBondRearLift) + 2);
  } else if (getL2Pos() && potVal < bBondRearLift) {
    return -(0.5 * (potVal - bBondRearLift) - 2);
  } else {
    return 0;
  }
}

int getFrontSixBarSpeed(){
  if(1000 - mFrontIntakeBackDlift.position(deg) < getAxis2Pos()){
    //return (1000 - mFrontIntakeBackDlift.position(deg))/voltageConverstion;

  } else if(0 - mFrontIntakeBackDlift.position(deg) > getAxis2Pos()){
    //return (0 - mFrontIntakeBackDlift.position(deg))/voltageConverstion;
  }
  return getAxis2Pos()/voltageConverstion; 
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