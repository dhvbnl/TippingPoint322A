#include "vex.h"

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
  drivetrainTurn(345);
  timeDrive(-7, 2500);
  setMFrontLiftCylinder();
  timeDrive(5, 1500);
  getPos.interrupt();
}

void skills() {
  thread getPos(getPosition);
  wait(10, msec);
  setPos(-2.3, 80, false);
  getPos.interrupt();
}