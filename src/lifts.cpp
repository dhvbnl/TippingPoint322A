#include "vex.h"

int liftControl(){
  lBackDriveBackLift.setBrake(brake);
  while(true){
    //if(!mBackDriveLift.value() && !lBackTransmission.value() && !rBackTransmission.value())
    setRearLiftSpeed(getRearLiftSpeed());
    Controller.Screen.clearLine();
    Controller.Screen.print(getBackLiftPot());
    wait(10, msec);
  }
}

void setRearLiftSpeed(int speed){
    lBackDriveBackLift.spin(fwd, speed, pct);
}

int getRearLiftSpeed(){
  int potVal = getBackLiftPot();
  Brain.Screen.clearLine();
  Brain.Screen.print(potVal);
  //if(potVal < bBondRearLift && potVal > tBondRearLift){
    if(getR1Pos() && potVal > tBondRearLift + 2){
      return 3 * (potVal- tBondRearLift);
    } else if(getR2Pos() && potVal < bBondRearLift){
      return 4 * (potVal - bBondRearLift);
    } else{ 
      return 0;
    }
  //}
  //return 0;
}

int getBackLiftPot(){
  return lBackLift.value(pct);
}