#include "vex.h"

/*
void test() { //(-2.3, 2.3)
  thread getPos(getPosition);
  //setPos(-2.3, 80, false);
  driveProfile(87, true);
  wait(100, msec);
  drivetrainTurn(45);
  //setPos(-20, 20, false);
  driveProfileslow(90, false);
  wait(100, msec);
  drivetrainTurn(355);
  timeDrive(5, 3000);
  getPos.interrupt();
} 

void redalliance() {
  thread getPos(getPosition);
  timeDrive(-4, 300);
  wait(100, msec);
  timeDrive(4, 700);
  drivetrainTurn(300);
  wait(100, msec);
  driveProfile(27, false);
  drivetrainTurn(343);
  timeDrive(-7, 3000);
  //setMFrontLiftCylinder();
  timeDrive(5, 1500);
  getPos.interrupt();
}

void skills() {
  thread getPos(getPosition);
  wait(10, msec);
  setPos(-2.3, 80, false);
  getPos.interrupt();
}

void seesawGoal() {
  thread getPos(getPosition);
  timeDrive(-4, 300);
  wait(100, msec);
  timeDrive(4, 700);
  wait(100, msec);
  getPos.interrupt();
}

void farGoal() {
  thread getPos(getPosition);
  timeDrive(-4, 1000);
  //setMFrontLiftCylinder();
  wait(100, msec);
  timeDrive(4, 1000);
  wait(100, msec);
  getPos.interrupt();
}

void elims() {
  thread getPos(getPosition);
  timeDrive(-11, 860);
  wait(200, msec);
  //setMFrontLiftCylinder();
  wait(200, msec);
  timeDrive(11, 900);

}*/

void test() {
  
  //drivetrainTurn(90);
  thread get(getPos);
  setPos(20, 0, true, 0);
  setPos(-10, 10, false, 0);

/*leftFrontDrive.spin(vex::directionType::fwd, 4, volt);
  leftMiddleDrive.spin(vex::directionType::fwd, 4, volt);
  rightFrontDrive.spin(vex::directionType::fwd, -4, volt);
  rightMiddleDrive.spin(vex::directionType::fwd, -4, volt); 
  leftBackDrive.spin(vex::directionType::fwd, 4, volt);
  rightBackDrive.spin(vex::directionType::fwd, -4, volt);
 }
  leftFrontDrive.stop();
  leftMiddleDrive.stop();
  rightFrontDrive.stop();
  rightMiddleDrive.stop();
  rightBackDrive.stop();
  leftBackDrive.stop();*/

}