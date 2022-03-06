#include "vex.h" 

void allianceMain() {
  thread odometry(getPos);
  thread lifts(setFourBarIntakeAuton);

  setDrivetrainLock();

  thread  clamp(setFrontClampAuton);
  timer test;
  findFrontGoal(yellow, YELLOWGOAL, 12, true, false, true);
  setFrontClampAuton();
  Controller.Screen.print(test.time(sec));
  backUpSonar(35, 12);
  changeArmPos(1700);
  findRearGoal(red, REDGOAL, 7, false, true, false);
  setRearClamp();
  wait(200, sec);


  odometry.interrupt();
  //lifts.interrupt();
  fourBar.stop();
}

void allianceRightNeutral(){

}

void allainceMiddleNeutral(){

}
 
void allianceLeftNeutral(){

}

void skills(){
   timer t;
  setDrivetrainLock();
  thread odometry(getPos);
  thread lifts(setFourBarIntakeAuton);
  setFrontClampAuton();
  timeDrive(-4, 400);
  setRearClampAuton();
  wait(100, msec);
  
  timeDrive(4, 500);
  findFrontGoal(yellow, YELLOWGOAL, 8, true, true, false);
  setFrontClampAuton();
  wait(100, msec);
  changeArmPos(2330); //2285
  intakeMove(true);
   t.reset();
  setPos(74, -36, 7, true);
  //  if (t.time() > 1) {
  //    stopdrive();
  //  }
  wait(500, msec);
  drivetrainTurn(80);
  wait(500, msec);
  timeDrive(5, 1200);
  wait(300, msec);
  changeArmPos(2270); //2285
  // places first yellow goal on platform
  wait(300, msec);
  setFrontClampAuton();
  wait(500, msec);
  changeArmPos(2330); 
  timeDrive(-5, 1000);
  changeArmPos(1475); 
  setRearClampAuton();
  wait(500, msec);
  // drivetrainTurn(255);
  // wait(300, msec);
  // // hook onto red goal
  // setFrontClampAuton();
  // wait(500, msec); 
  // changeArmPos(2330); 
  // wait(500, msec);
  // drivetrainTurn(75);
  // wait(500, msec);
  // timeDrive(5, 1000);
  // setFrontClampAuton();

  odometry.interrupt();
  lifts.interrupt();
  fourBar.stop();
}

void skillsBackup() {
  setDrivetrainLock();
  thread odometry(getPos);
  thread lifts(setFourBarIntakeAuton);
  setFrontClampAuton();
  timeDrive(-4, 400);
  setRearClampAuton();
  wait(100, msec);
  
  timeDrive(4, 500);
  findFrontGoal(yellow, YELLOWGOAL, 8, true, true, false);
  setFrontClampAuton();
  wait(300, msec);
  intakeMove(true);
  driveProfile(44, 8, true);
  wait(100, msec);
  setFrontClampAuton();
  wait(500, msec);
  drivetrainTurn(270);
  driveProfile(5, 8, true);
  setRearClampAuton();
  wait(200, msec);
  driveProfile(18, 8, true);
  wait(200, msec);
  drivetrainTurn(90);
  findFrontGoal(red, REDGOAL, 8, false, true, false); 
  setFrontClampAuton();
  wait(300, msec);
  // findFrontGoal(yellow, YELLOWGOAL, 8, true, true, false);
  // setFrontClampAuton();
  // wait(300, msec);

  odometry.interrupt();
  lifts.interrupt();
  fourBar.stop();
}

