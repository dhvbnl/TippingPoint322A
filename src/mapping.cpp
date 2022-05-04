#include "vex.h" 

void visionTesting(){
  wait(2, sec);
  thread  clamp(setFrontClampAuton);
  //setGoalCoverAuton();
  //setGoalCoverAuton();
  timer test;
  //findFrontGoalClose(blue, BLUEGOAL, 5, false, true, false);
  setFrontClampAuton();
  Controller.Screen.print(test.time(sec) );
  //timeDrive(-3, 1000);
}


void allianceRightRightWin(color col, signature sig, bool runCover) {
  setDrivetrainLock();
  thread calib(findBottomBound);
  thread lifts(setFourBarIntakeAuton);
  
  setFrontClampAuton();
  if(runCover)
    setGoalCoverAuton();
  


  lifts.interrupt();
}

void allianceRightRight(color col, signature sig, bool runCover){
  setDrivetrainLock();
  thread calib(findBottomBound);
  
  setFrontClampAuton();
  if(runCover)
    setGoalCoverAuton();

  timer goalTime; 
  printf("Starting... \n");

  findFrontGoalAgressive(yellow, YELLOWGOAL, 12, true, false, true);
  setFrontClampAuton();
  printf("Rush: %f \n", goalTime.time(sec));
  thread lifts(setFourBarIntakeAuton);

  backUpSonar(34, 12);
  //timeDrive(-12, 700);
  changeArmPos(1000);
  findRearGoal(col, sig, 4, false, true, false);
  setRearClampAuton();
  wait(200, msec);
  drivetrainTurn(350);
  intakeMove(1);
  timeDrive(5, 2000);
  wait(300, msec);
  timeDrive(-6, 1700);
  wait(200, msec);
  drivetrainTurn(220);
  changeArmPos(3350);
  wait(300, msec);
  intakeMove(1);
  timeDrive(4, 2500);
  wait(500, msec);
  setRearClampAuton();
  intakeMove(0);
  timeDrive(3, 300);

  printf("Finished: %f \n", goalTime.time(sec));

  /*wait(2, sec);
  Controller.rumble("--");
  wait(2, sec);
  frontClampStandoff.set(0);
  rearClamp.set(1);
  frontClamp.set(1);
  setGoalCoverAuton();
  setDrivetrainCreep();*/

  lifts.interrupt();
}

void allianceRightMiddle(color col, signature sig, bool runCover){
  setDrivetrainLock();
  thread calib(findBottomBound);
  
  setFrontClampAuton();
  if(runCover)
    setGoalCoverAuton();
  
  timer goalTime; 
  printf("Starting... \n");

  findFrontGoalAgressive(yellow, YELLOWGOAL, 12, true, false, true);
  setFrontClampAuton();
  printf("Rush: %f \n", goalTime.time(sec));
  thread lifts(setFourBarIntakeAuton);

  timeDrive(-12, 1000);
  changeArmPos(1000);
  findRearGoal(col, sig, 4, false, true, false);
  setRearClampAuton();
  intakeMove(1);
  wait(1000, msec);
  drivetrainTurn(25);
  timeDrive(5, 2000);
  wait(300, msec);
  timeDrive(-6, 2700);
  wait(200, msec);
  setRearClampAuton();
  intakeMove(0);
  timeDrive(5, 300);

  lifts.interrupt();
}

void allianceRightRightMiddle(color col, signature sig, bool runCover){
  setDrivetrainLock();
  thread calib(findBottomBound);
  
  setFrontClampAuton();
  if(runCover)
    setGoalCoverAuton();

  timer goalTime; 
  printf("Starting... \n");

  findFrontGoalAgressive(yellow, YELLOWGOAL, 12, true, false, true);
  setFrontClampAuton();
  printf("Rush: %f \n", goalTime.time(sec));
  thread lifts(setFourBarIntakeAuton);
  backUpSonar(25, 12);
  drivetrainTurn(120);
  findRearGoal(yellow, YELLOWGOAL, 7, true, false, true);
  setRearClampAuton();
  timeDrive(7, 2200);
  drivetrainTurn(300);
  timeDrive(-5, 500);
  setRearClampAuton();
  changeArmPos(1000);
  timeDrive(8, 1100);
  drivetrainTurn(270);
  findRearGoal(col, sig, 7, false, true, false);
  setRearClampAuton();
  wait(200, msec);
  intakeMove(1);
  timeDrive(7, 600);
  setRearClampAuton();
  timeDrive(4, 400);
  intakeMove(0);


  lifts.interrupt();
}
 
void allianceLeftLeft(color col, signature sig, bool runCover){
  setDrivetrainLock();
  thread calib(findBottomBound);
  

  setFrontClampAuton();
  if (runCover)
    setGoalCoverAuton();

  timer goalTime;
  printf("Starting... \n");

  findFrontGoalAgressive(yellow, YELLOWGOAL, 12, true, false, true);
  setFrontClampAuton();
  printf("Rush: %f \n", goalTime.time(sec));
  thread lifts(setFourBarIntakeAuton);

  timeDrive(-12, 1300);
  timeTurn(-7, -9, 600);
  //timeDrive(-7, 600);
  changeArmPos(3350);
  drivetrainTurn(280);
  timeDrive(6, 700);
  wait(300, msec);
  findRearGoal(col, sig, 4, true, false, true);
  setRearClampAuton();
  wait(200, msec);
  intakeMove(1);
  wait(1000, msec);
  timeDrive(4, 2000);
  timeDrive(-4, 2000);
  wait(500, msec);
  timeDrive(4, 2000);
  wait(500, msec);
  setRearClampAuton();
  intakeMove(0);
  timeDrive(5, 300);

  printf("Finished: %f \n", goalTime.time(sec));

  /*wait(2, sec);
  Controller.rumble("--");
  wait(2, sec);
  frontClampStandoff.set(0);
  rearClamp.set(1);
  frontClamp.set(1);
  setDrivetrainCreep();*/

  lifts.interrupt();
}

void allianceLeftMiddle(color col, signature sig, bool runCover){
  setDrivetrainLock();
  thread calib(findBottomBound);
  thread lifts(setFourBarIntakeAuton);
  
  setFrontClampAuton();
  if(runCover)
    setGoalCoverAuton();
  


  lifts.interrupt();
}

void skills(){
  setDrivetrainLock();
  //thread odometry(getPos);
  thread lifts(setFourBarIntakeAuton);
  setFrontClampAuton();
  timeDrive(-4, 400);
  setRearClampAuton();
  wait(700, msec);

  changeArmPos(3350);
  intakeMove(1);
  timeDrive(5, 1800);
  wait(200, msec);
  inert.resetHeading();
  intakeMove(0);

  
  timeDrive(-4, 500);
  changeArmPos(0);
  drivetrainTurn(78);
  findFrontGoal(yellow, YELLOWGOAL, 10, true, true, false);
  setFrontClampAuton();
  wait(100, msec);
  changeArmPos(3350); //2285
  intakeMove(1);
  drivetrainTurn(134);
  timeDrive(7, 1800);

  wait(200, msec);
  drivetrainTurn(88); //89
  wait(500, msec);
  timeDrive(5, 1500);
  wait(100, msec);

  // places first yellow goal on platform
  setFrontClampAuton();
  wait(100, msec);

  //move back from goal 
  timeDrive(-5, 1000);
  changeArmPos(0); 
  wait(100, msec);
  setRearClampAuton();
  wait(100, msec);

  //pick up blue goal #1
  timeDrive(4, 800);
  findFrontGoal(blue, BLUEGOAL, 5, false, true, false);
  setFrontClampAuton();
  changeArmPos(3350);
  timeDrive(-5, 500);
  drivetrainTurn(114); //112
  timeDrive(5, 1500);
  setFrontClampAuton();
  timeDrive(-5, 1000);



//get yellow goal #2 
  changeArmPos(1000);

  drivetrainTurn(177);
  timeDrive(6, 2000);
  wait(100, msec);
  timeDrive(-4, 1000);

  findFrontGoal(yellow, YELLOWGOAL, 7, true, true, false);
  setFrontClampAuton();
  wait(100, msec);
  changeArmPos(3350);
  drivetrainTurn(294); //turn to platform 
  timeDrive(6, 3000);
  wait(100, msec); 
  setFrontClampAuton();

  //get blue #2
  timeDrive(-5, 700); 
  changeArmPos(0);
  drivetrainTurn(180);
  findFrontGoal(blue, BLUEGOAL, 7, true, true, false);
  setFrontClampAuton();

  //platform blue 
  intakeMove(1);
  changeArmPos(3350);
  timeDrive(-5, 500);
  drivetrainTurn(82); //85
  timeDrive(7, 3000);
  setFrontClampAuton();
  wait(100, msec);
  timeDrive(-5, 400);

  // yellow 3
  drivetrainTurn(265);
  findFrontGoal(yellow, YELLOWGOAL, 5, true, true, false);
  setFrontClampAuton();
  wait(100, msec);
  changeArmPos(900);
  drivetrainTurn(37);
  timeDrive(7, 2000);
  changeArmPos(0);
  wait(200, msec);
  setFrontClampAuton();
  timeDrive(-4, 500);
  findFrontGoal(red, REDGOAL, 5, false, true, false);
  setFrontClampAuton();
  
  changeArmPos(900);
  drivetrainTurn(163);
  timeDrive(7, 4000);
 // timeDrive(-4, 700);
  drivetrainTurn(270);
  wait(200, msec);
  findRearGoal(red, REDGOAL, 5, false, true, false);
  setRearClampAuton();

  //go to platform
  changeArmPos(3350);
  drivetrainTurn(285); 
  intakeMove(1);
  timeDrive(8, 4000);
  setFrontClampAuton();
  wait(200, msec);
  timeDrive(-5, 1000);
  changeArmPos(0); 
  setRearClampAuton();
  wait(100, msec);

  timeDrive(4, 500);
  drivetrainTurn(95);
  timeDrive(-4, 400);
  findFrontGoal(red, REDGOAL, 5, false, true, true);
  setFrontClampAuton();
  changeArmPos(3350);
  timeDrive(-5, 500);
  drivetrainTurn(276); //85
  timeDrive(5, 1500);
  setFrontClampAuton();
  timeDrive(-5, 400);



//   drivetrainTurn(273);
//   timeDrive(6, 1700);
//   drivetrainTurn(0);
//   findRearGoal(blue, BLUEGOAL, 5, true, true, false);
//   setRearClampAuton();

//   wait(100, msec);
//   intakeMove(1);
//   changeArmPos(3350);
//   drivetrainTurn(75); // maybe arc it?
//   timeDrive(5, 1800);
//   drivetrainTurn(45);
//   timeDrive(8, 1800);
//   wait(200, msec);
//   drivetrainTurn(85); //82
//   timeDrive(4, 1500); //change it if its too long
//   intakeMove(0);

// //place yellow #2 and blue #2 on platform
//   setFrontClampAuton();
//   wait(200, msec);
//   timeDrive(-5, 1000);
//   changeArmPos(0); 
//   setRearClampAuton();
//   wait(100, msec);

//   timeDrive(4, 500);
//   drivetrainTurn(265);
//   timeDrive(-4, 400);
//   findFrontGoal(blue, BLUEGOAL, 5, false, true, true);
//   setFrontClampAuton();
//   changeArmPos(3350);
//   timeDrive(-5, 500);
//   drivetrainTurn(82); //85
//   timeDrive(5, 1500);
//   setFrontClampAuton();
//   timeDrive(-5, 400);


// //get yellow #3
//   drivetrainTurn(265);
//   findFrontGoal(yellow, YELLOWGOAL, 5, false, true, false);
//   setFrontClampAuton();
//   wait(100, msec);
//   changeArmPos(900);
//   drivetrainTurn(27);
//   timeDrive(7, 2000);
//   changeArmPos(0);
//   setFrontClampAuton();
//   timeDrive(-4, 500);
//   findFrontGoal(red, REDGOAL, 5, false, true, false);
//   setFrontClampAuton();
  
//   changeArmPos(900);
//   drivetrainTurn(0);
//   timeDrive(-7, 3400);
//   timeDrive(4, 700);
//   drivetrainTurn(90);
//   wait(200, msec);
//   findRearGoal(red, REDGOAL, 5, true, true, false);
//   setRearClampAuton();

  // setFrontClampAuton();
  // changeArmPos(1000);
  // drivetrainTurn(232);
  // timeDrive(-7, 2500);
  // drivetrainTurn(190);
  // timeDrive(-4, 1000);
 // drivetrainTurn(178);
  // wait(100, msec);
  // changeArmPos(3450);
  // timeDrive(3.5, 4500);
  // wait(100, msec);
  // changeArmPos(3300);
  // wait(100, msec);
  // setFrontClampAuton();
  // timeDrive(-3, 1000);
//get red #1


  
  //odometry.interrupt();
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
