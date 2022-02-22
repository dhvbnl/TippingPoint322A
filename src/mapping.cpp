#include "vex.h" 

void allianceMain() {
  thread odometry(getPos);
  thread lifts(setFourBarIntakeAuton);
  timeDrive(-4, 200);
  setRearClampAuton();
  changeArmPos(1650);
  timeDrive(4, 300);
  wait(500, msec);
  intakeMove(true);
  wait(1000, msec);
  setPos(27, -5, 5, true);
  wait(300, msec);
  setPos(44, -90, 5, true);
  drivetrainTurn(260);
  intakeMove(false);
  timeDrive(6, 1000);
  setFrontClampAuton();
  wait(1000, msec);
  timeDrive(-4, 300);
  odometry.interrupt();
  lifts.interrupt();
  fourBar.stop();
}

void allianceMainCut() {
  thread odometry(getPos);
  thread lifts(setFourBarIntakeAuton);
  timeDrive(-4, 200);
  setRearClampAuton();
  changeArmPos(1650);
  timeDrive(4, 300);
  wait(500, msec);
  intakeMove(true);
  wait(1000, msec);
  setPos(27, -5, 5, true);
  wait(300, msec);
  setPos(44, -55, 5, true);
  wait(500, msec);
  timeDrive(-4, 500);
  intakeMove(false);
  odometry.interrupt();
  lifts.interrupt();
  fourBar.stop();
}

void alliancerightGoal(){
  thread odometry(getPos);
  thread lifts(setFourBarIntakeAuton);
  setFrontClampAuton();
  timeDrive(12, 700);
  wait(350, msec);
  setFrontClampAuton();
  wait(200, msec);
  timeDrive(-7, 1100);
  //setPos(0, 18, 7, false);
  wait(200, msec);
  changeArmPos(1650);
  wait(500, msec);
  drivetrainTurn(305);
  timeDrive(-4, 2300);
  wait(200, msec);
  setRearClampAuton();
  intakeMove(true);
  wait(500, msec);
  timeDrive(4, 250);
  intakeMove(true);
  wait(2000, msec);
  intakeMove(false);
  setRearClampAuton();
  timeDrive(4, 250);


  // //setFrontClampAuton();
  // wait(200, msec);
  // setPos(12, 24, 5, false);
  // setRearClampAuton();
  // changeArmPos(1650);
  // setPos(4, 25, 7, true);
  // drivetrainTurn(0);
  // intakeMove(true);
  // wait(500, msec);
  // timeDrive(4, 1600);
  // wait(500, msec);
  // timeDrive(-8, 700);
  // intakeMove(false);
  // odometry.interrupt();
  // lifts.interrupt();
  // fourBar.stop();
}

void rightsidewinpoint() {
  thread odometry(getPos);
  thread lifts(setFourBarIntakeAuton);
  timeDrive(-4, 1000);
  wait(400, msec);
  setRearClampAuton();
  wait(400, msec);
  intakeMove(true);
  wait(2000, msec);
  timeDrive(4, 400);
}
void allianceleftGoal() {
  thread odometry(getPos);
  thread lifts(setFourBarIntakeAuton);
  changeArmPos(1475);
  setFrontClampAuton();
  timeDrive(10, 750);
  wait(400, msec);
  setFrontClampAuton();
  wait(500, msec);
  timeDrive(-10, 850);
  wait(200, msec);
 // setPos(0, -2, 8, false);
  drivetrainTurn(260);
  timeDrive(-4, 700);
  //setRearClampAuton();
  wait(400, msec);
  intakeMove(true);
  //timeDrive(4, 500);

}

void skills(){
  thread odometry(getPos);
  thread lifts(setFourBarIntakeAuton);
  timeDrive(-4, 200);
  setRearClampAuton();
  setFrontClampAuton();
  //setPos(3, 6, 3, true);
  //step two
  setPos(48, 3, 7, true);
  setFrontClampAuton();
  changeArmPos(1700);
  intakeMove(true);
  setPos(87, 0, 5, true);
  intakeMove(false);
  wait(300, msec);
  changeArmPos(1475);
  wait(500, msec);
  setFrontClampAuton();
  wait(200, msec);
  timeDrive(-4, 700);
  wait(300, msec);
  setPos(78, 10, 5, true);
  wait(400, msec);
  setFrontClampAuton();
  wait(500, msec);
  changeArmPos(1700);
  timeDrive(-4, 300);
  intakeMove(true);
  setPos(83, -25, 5, true);
  drivetrainTurn(180);
  timeDrive(5, 2000);
  intakeMove(false);
  wait(500, msec);
  timeDrive(-4, 800);
  setRearClampAuton();
  wait(500, msec);
  timeDrive(5, 500);
  setPos(105, -85, 7, true);
  drivetrainTurn(180);
  timeDrive(-4, 800);
  wait(500, msec);
  setRearClampAuton();
  timeDrive(4, 800);
  wait(300, msec);
  intakeMove(true);
  setPos(20, -55, 7, true);
  changeArmPos(2300);
  intakeMove(false);
  wait(1000, msec);
  timeDrive(5, 1000);
  setFrontClampAuton();
  odometry.interrupt();
  lifts.interrupt();
  fourBar.stop();
}



void teamworkwinpoint() {
  thread get(getPos);
  thread arm(setFourBarIntakeAuton);
  timeDrive(-4, 200);
  setRearClampAuton();
  setPos(3, 6, 3, true);
  changeArmPos(1650);
  intakeMove(true);
  setPos(25, 7, 6, true);
  setPos(40, -94, 5, true);
  wait(200, msec);
  timeDrive(-6, 400);
  wait(200, msec);
  intakeMove(false);
  //changeArmPos(1475);
  drivetrainTurn(230);
  //setPos(27, -90, 5, true);
  timeDrive(6, 1500);
  setFrontClampAuton();
  //drivetrainTurn(270);
  /*setPos(38, -82, 5, true);
  wait(200, msec);
  timeDrive(-6, 400);
  intakeMove(false);
  setFrontClampAuton();
  changeArmPos(1475);
  setPos(27, -90, 5, true);
  timeDrive(4, 500);
  setFrontClampAuton();
  drivetrainTurn(270);*/
  
  get.interrupt();
  arm.interrupt();
  fourBar.stop();
}

void skillsauton() {
  setDrivetrainLock();

  /*setRearClampAuton();
  wait(1000, msec);
  drivetrainTurn(90);
  wait(500, msec);
  printf("%f", inert.heading());
  drivetrainTurn(0);
  wait(500, msec);
  printf("%f", getInertialHeading());
  drivetrainTurn(180);
  wait(500, msec);
  printf("%f", getInertialHeading());
  drivetrainTurn(0);
  printf("%f", getInertialHeading());
  wait(500, sec);*/

  thread get(getPos);
  thread arm(setFourBarIntakeAuton);
  //step one
  timeDrive(-4, 200);
  setRearClampAuton();
  setFrontClampAuton();
  setPos(3, 6, 3, true);
  //step two
  setPos(48, -3, 7, true);
  setFrontClampAuton();
  changeArmPos(2300);
  intakeMove(true); 
  //step three
  //setPos(70, -25, 5, true);
  setPos(89, -41, 5, true);
  wait(500, msec);
  intakeMove(false);
  drivetrainTurn(90);
  wait(500, msec);
  timeDrive(5, 500);
  setFrontClampAuton();
  wait(500, msec);
  timeDrive(-6, 400);
  //step 4
  //setPos(89, -39, 5, false);
  wait(100, msec);
  drivetrainTurn(145);
  changeArmPos(1475);
  timeDrive(-5, 700);
  setRearClampAuton();
  timeDrive(5, 700);
  wait(500, msec);
  drivetrainTurn(325);
  timeDrive(5, 1200);
  setFrontClampAuton();

 // setRearClampAuton(); //turn off
  

}

void teamworkright() {
  setPos(0, 40, 12, true);
  //timeDrive(11, 500);
  setFrontClampAuton();
  wait(100, msec);
  setPos(-20, 10, 5, false);
  setRearClampAuton();
  changeArmPos(1650);

  intakeMove(true);
  setPos(-40, 20, 5, true);

}

void teamworkleft() {
  setPos(0, 40, 12, true);
  //timeDrive(11, 500);
  setPos(0, 0, 6, false);
  drivetrainTurn(270);
  timeDrive(-2, 400);
  setRearClampAuton();

}
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
  //printf("%f\n", getInertialHeading());
  //thread getposition(getPos);
  printf("intertial %f\n", getInertialHeading());
  setPos(1, -30, 5, false);
  setPos(5, 0, 3, true);
  //drivetrainTurn(270);
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