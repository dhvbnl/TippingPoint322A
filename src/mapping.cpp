#include "vex.h" 

void allianceMain(color col, signature sig) {
  /*while(true){
    Controller.Screen.clearLine();
    Controller.Screen.print(rearSonar.distance(inches));
    wait(20, msec);
  }*/
  //thread odometry(getPos);
  setDrivetrainLock();
  thread calib(findBottomBound);
  thread  clamp(setFrontClampAuton);
  
  timer test;
  findFrontGoal(yellow, YELLOWGOAL, 12, true, false, true);
  setFrontClampAuton();
  wait(200, msec);

  thread lifts(setFourBarIntakeAuton);
  backUpSonar(35, 12);
  changeArmPos(400);
  drivetrainTurn(320);
  findRearGoal(col, sig, 5, false, true, false);
  setRearClampAuton();
  //Controller.Screen.print(test.time(sec) );
  printf("inertial start %f\n", getInertialHeading());
  drivetrainTurn(277);
  printf("inertial end %f\n", getInertialHeading());
  wait(200, msec);
  intakeMove(1);
  timeDrive(9, 800);
  timeDrive(4, 2200);
  printf("inertial start %f\n", getInertialHeading());
  //drivetrainTurn(300);
  intakeMove(2);
  printf("inertial end %f\n", getInertialHeading());
  setRearClampAuton();
  timeDrive(6, 700);
  drivetrainTurn(0);
  wait(200, msec);
  timeDrive(-7, 1800);
  drivetrainTurn(300);
  while(!rearGoalLimit.pressing()){
    setDrivetrainSpeed(-4, -4);
  }
  setDrivetrainSpeed(0, 0);
  //findRearGoal(red, REDGOAL, 4, false, true, false);
  setRearClampAuton();
  wait(200, msec);
  intakeMove(1);
  wait(300, msec);
  timeDrive(4, 300);
  setRearClampAuton();
  //Controller.Screen.print(test.time(sec));



  //odometry.interrupt();
  //lifts.interrupt();
  fourBar.stop();
}

void allianceRightNeutral(color col, signature sig){
  setDrivetrainLock();
  thread calib(findBottomBound);
  thread  clamp(setFrontClampAuton);
  timer test;
  findFrontGoal(yellow, YELLOWGOAL, 12, true, false, true);
  setFrontClampAuton();
  Controller.Screen.print(test.time(sec));
  thread lifts(setFourBarIntakeAuton);
  backUpSonar(30, 12);
  changeArmPos(400);
  findRearGoal(col, sig, 5, false, true, false);
  setRearClampAuton();
  drivetrainTurn(345);
  intakeMove(1);
  timeDrive(3, 2500);
  timeDrive(-5, 1500);
  wait(300, msec);
  drivetrainTurn(210);
  changeArmPos(1200);
  wait(800, msec);
  intakeMove(1);
  timeDrive(2.7, 3000);
  timeDrive(-4, 400);
  setRearClampAuton();



}

void allianceMiddleNeutral(color col, signature sig){
  setDrivetrainLock();
  thread lifts(setFourBarIntakeAuton);
  setFrontClampAuton();
  findFrontGoal(yellow, YELLOWGOAL, 12, true, false, true);
  setFrontClampAuton();
  changeArmPos(300);
  timeDrive(-12, 700);
  drivetrainTurn(300);
  wait(500, msec);
  findRearGoal(col, sig, 7, false, true, true);
  setRearClampAuton();
  intakeMove(true);
  drivetrainTurn(20);
  timeDrive(3, 2700);
  wait(200, msec);
  timeDrive(-5, 1700);
  setRearClampAuton();


}
 
void allianceLeftNeutral(color col, signature sig){
  setDrivetrainLock();
  thread lifts(setFourBarIntakeAuton);
  setFrontClampAuton();
  timer test;
  findFrontGoal(yellow, YELLOWGOAL, 12, true, false, true);
  setFrontClampAuton();
  Controller.Screen.print(test.time(sec));
  timeDrive(-12, 400);
  changeArmPos(300);
  timeDrive(-6, 2000);
  drivetrainTurn(290);
  changeArmPos(1075);
  while(!rearGoalLimit.pressing()){
    setDrivetrainSpeed(-4, -4);
  }
  setDrivetrainSpeed(0, 0);
  //findRearGoal(red, REDGOAL, 4, false, true, false);
  setRearClampAuton();
  wait(200, msec);
  intakeMove(1);
  timeDrive(4, 400);
  drivetrainTurn(260);
  wait(2.5, sec);
  timeDrive(3.5, 3500);
  timeDrive(-4, 400);
  setRearClampAuton();

}

void skills(){
  setDrivetrainLock();
  thread odometry(getPos);
  thread lifts(setFourBarIntakeAuton);
  setFrontClampAuton();
  timeDrive(-4, 400);
  setRearClampAuton();
  wait(100, msec);
  
  timeDrive(4, 500);
  drivetrainTurn(80);
  findFrontGoal(yellow, YELLOWGOAL, 8, true, true, false);
  setFrontClampAuton();
  wait(100, msec);
  changeArmPos(1100); //2285
  intakeMove(1);
  
  setPos(74, -36, 7, true);

  wait(500, msec);
  drivetrainTurn(88); //80
  wait(500, msec);
  timeDrive(5, 1200);
  wait(300, msec);
  //changeArmPos(1100); //2285

  // places first yellow goal on platform
  //wait(300, msec);
  setFrontClampAuton();
  wait(200, msec);
  //changeArmPos(1100); 
  //move back from goal 
  timeDrive(-5, 1000);

  changeArmPos(0); 
  setRearClampAuton();
  wait(100, msec);
  timeDrive(5, 500);
  //pick up blue goal #1
  drivetrainTurn(265);
  findFrontGoal(blue, BLUEGOAL, 5, true, true, false);
  setFrontClampAuton();
  changeArmPos(1100);
  drivetrainTurn(120);
  timeDrive(5, 1500);
  setFrontClampAuton();

  //get red goal #1
  timeDrive(-5, 500);
  drivetrainTurn(200);
  changeArmPos(0);
  findRearGoal(red, REDGOAL, 6, true, true, false);
  setRearClampAuton();
  wait(100, msec);
  findFrontGoal(yellow, YELLOWGOAL, 7, true, true, false);
  setFrontClampAuton();
  intakeMove(1);
  changeArmPos(300);
  drivetrainTurn(230);
  timeDrive(7, 2000);
  changeArmPos(0);
  wait(1000, msec);
  setFrontClampAuton();
  timeDrive(-7, 300);
  drivetrainTurn(90);
  findFrontGoal(yellow, YELLOWGOAL, 7, true, true, false);
  setFrontClampAuton();
  drivetrainTurn(320);
  changeArmPos(1100);
  wait(300, msec);
  timeDrive(7, 1500);
  wait(400, msec);
  setFrontClampAuton();
  wait(500, msec);


  timeDrive(-5, 1000);
  wait(200, msec);
  changeArmPos(0); 
  setRearClampAuton();
  wait(100, msec);
  timeDrive(5, 500);
  drivetrainTurn(95);
  findFrontGoal(red, REDGOAL, 5, true, true, false);
  setFrontClampAuton();
  changeArmPos(1100);
  drivetrainTurn(315);
  wait(200, msec);
  timeDrive(5, 1500);
  setFrontClampAuton();

  timeDrive(-5, 500);
  changeArmPos(0);
  findFrontGoal(blue, BLUEGOAL, 7, false, true, false);
  setFrontClampAuton();
  changeArmPos(1100);
  drivetrainTurn(70);
  timeDrive(7, 2800);
  setFrontClampAuton();
  wait(500, msec);
  timeDrive(-7, 2000);
  intakeMove(1);
  changeArmPos(0);
  wait(500, msec);
  findFrontGoal(red, REDGOAL, 5, true, true, false);
  intakeMove(0);
  setFrontClampAuton();
  wait(500, msec);
  changeArmPos(1100);
  timeDrive(-8, 2000);
  wait(500, msec);
  drivetrainTurn(315);
  timeDrive(5, 1500);
  setFrontClampAuton();
  wait(200, msec);
  timeDrive(-5, 500);
  //get center goal
  
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

void test3() {
  setDrivetrainLock();
  thread odometry(getPos);
  thread lifts(setFourBarIntakeAuton);
  setFrontClampAuton();
  // thread lifts(setFourBarIntakeAuton);
  // thread calib(findBottomBound);
  // thread pos(getPos);
  // thread  clamp(setFrontClampAuton);
  // setDrivetrainLock();
  // wait(1000, msec);
  // //changeArmPos(1075);
  // //wait(2000, msec);
  // //driveProfile(10, 5, true);
  // setFrontClampAuton();
  // setRearClampAuton();
  // wait(200, msec);
  // changeArmPos(300);
  // wait(1000, msec);
  // drivetrainTurn(180);
  // wait(100, msec);
  // drivetrainTurn(0);
  // printf("turns done %f \n", getInertialHeading());
  // wait(2000, msec);
  //thread get(getPos);
    findFrontGoal(yellow, YELLOWGOAL, 7, true, true, false);
    setFrontClampAuton();
  // wait(2000, msec);
  // drivetrainTurn(180);
  // wait(400, msec);
  // drivetrainTurn(0);
  // wait(400, msec);
  // wait(400, msec);
  // drivetrainTurn(45);
  // driveProfile(10, 8, true);
  // wait(400, msec);
  // driveProfile(10, 8, false);
}
