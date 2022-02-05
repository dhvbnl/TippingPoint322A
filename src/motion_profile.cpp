/*#include "vex.h"

struct Acceleration {
  double dist;
  bool fwd;
  double deg;
} acc;

double speed = 0;
//accelerate
int accelerate() {
  //robot current position
  double lorig = getLeftEncoderRotation() * convertInches;
  //if the robot is going forwards
  if (acc.fwd) {
    //distance we want the robot to go to + where robot currently is
    acc.dist += lorig;
    while ((getLeftEncoderRotation() * convertInches) < acc.dist) {
      //speed = 4.0 * (fabs((fabs(getLeftEncoderRotation()) * convertInches) - lorig) + 1) + 2.6;
      speed = 5 * pow((fabs((fabs(getLeftEncoderRotation()) * convertInches) - lorig) + 1), 2) + 2.6;
      //if (speed > 11)
        //speed = 11;
      if (speed > 7)
        speed = 7;
      wait(10, msec);
    }
  //if the robot is going backwards
  } else {
    //distance we want the robot to go to - where the robot currently is (becaues the robot is going backwards)
    acc.dist = lorig - acc.dist;
    while ((getLeftEncoderRotation() * convertInches) > acc.dist) {
      //speed = 3.2 * (fabs((fabs(getLeftEncoderRotation()) * convertInches) - lorig) + 1) + 2.6;
      speed = 4 * pow((fabs((fabs(getLeftEncoderRotation()) * convertInches) - lorig) + 1), 2) + 2.6;
      //if (speed > 9)
       // speed = 9;
      if (speed > 7) 
        speed = 7;
      wait(10, msec);
    }
  }
  return 0;
}
//decelerate
int decelerate() {
  //robot current position (in inches)
  double lorig = getLeftEncoderRotation() * convertInches;
  int n = 0;
  //if the robot is going forward
  if (acc.fwd) {
    //changing "x" to make sure that the robot can decelerate properly no matter 
    //the distance
    if (acc.dist < 14) {
      n = 14 - acc.dist;
    }
    //robot current position added to distance it needs to decelerate
    acc.dist += lorig;
    while ((getLeftEncoderRotation() * convertInches) < acc.dist) {
      speed = 1.1 * exp((-0.2 * fabs((fabs(getLeftEncoderRotation()) * convertInches) - lorig + n)) + 2) + 1.15;
        if (speed > 7.5) speed = 7.5;
        if (speed < 3) speed = 3;
        wait(10, msec);
    }
  //if the robot is going backwards
  } else {
    //changing "x" to make sure that the robot can decelerate properly no matter 
    //the distance
    if (acc.dist < 14) {
      n = 14 - acc.dist;
    }
    //distance it needs to decelerate subtracted from robot current position (because encoder reads going backwards as negative)
    acc.dist = lorig - acc.dist;
    while ((getLeftEncoderRotation() * convertInches) > acc.dist) {
      speed = 1.1 * exp((-0.2 * fabs((fabs(getLeftEncoderRotation()) * convertInches) - lorig + n)) + 2) + 1.15; 
        if (speed > 7.5) speed = 7.5;
        if (speed < 3) speed = 3;
        wait(10, msec);
    }
  }
  return 0;
}

//driver function
int driveProfile(int dist, bool fwd) { //encoder orientation flipped 
  //Inertial.resetRotation();
  double acceldist = 0;
  int targetL = 0;
  double actdist;
  
  //determines acceleration and deceleration distance
  if (dist > 28) 
  {
    acceldist = 14;
  } 
  else {
    acceldist = dist / 2.0;
  }
  // Switching units to degrees here
  dist *= convertDegrees;
 
  if (fwd) {
   actdist = getLeftEncoderRotation() + dist;
  } else {
    actdist = getLeftEncoderRotation() - dist;
  }
  //going forward
  if (fwd)  {
    acc.dist = acceldist; // feeding acc.dist inch value -- accelerate() handles inches
    acc.fwd = fwd;

    thread thread1(accelerate);

    // accelerate-- switch to degrees
    acceldist *= convertDegrees;
    targetL = getLeftEncoderRotation() + acceldist; // target to finish acceleration
   
    while (getLeftEncoderRotation() < targetL) {
      lFrontDrive.spin(vex::directionType::fwd, speed, volt);
      lMiddleDrive.spin(vex::directionType::fwd, speed, volt);
      rFrontDrive.spin(vex::directionType::fwd, speed, volt);
      rMiddleDrive.spin(vex::directionType::fwd, speed, volt); 
      lBackDriveBackLift.spin(vex::directionType::rev, speed, volt);
      rBackDriveCascadeLift.spin(vex::directionType::rev, speed, volt);
      printf(" encoder: %f", getLeftEncoderRotation()*convertInches);
      wait(10, msec);
    }
    thread1.interrupt();
    while (getLeftEncoderRotation() < (actdist - acceldist)) {
      lFrontDrive.spin(vex::directionType::fwd, 8.4, volt);
      lMiddleDrive.spin(vex::directionType::fwd, 8.4, volt);
      rFrontDrive.spin(vex::directionType::fwd, 8.4, volt);
      rMiddleDrive.spin(vex::directionType::fwd, 8.4, volt); 
      lBackDriveBackLift.spin(vex::directionType::rev, 8.4, volt);
      rBackDriveCascadeLift.spin(vex::directionType::rev, 8.4, volt);
    } 
    acc.dist = acceldist * convertInches;
    thread thread3(decelerate);
    // decelerate
    targetL = getLeftEncoderRotation() + acceldist;
    while (getLeftEncoderRotation() < targetL ) {
      lFrontDrive.spin(vex::directionType::fwd, speed, volt);
      lMiddleDrive.spin(vex::directionType::fwd, speed, volt);
      rFrontDrive.spin(vex::directionType::fwd, speed, volt);
      rMiddleDrive.spin(vex::directionType::fwd, speed, volt);
      lBackDriveBackLift.spin(vex::directionType::rev, speed, volt);
      rBackDriveCascadeLift.spin(vex::directionType::rev, speed, volt);
      wait(10, msec);
    }
    thread3.interrupt();
  } 
  //backwards
  else {
    acc.dist = acceldist;
    acc.fwd = fwd;
    acceldist *= convertDegrees;
   
    thread thread2(accelerate);
    // accelerate
    targetL = getLeftEncoderRotation() - acceldist;
   
    while ((getLeftEncoderRotation() > targetL)) {
     // printf("accelerate: %f\n", speed);
      lFrontDrive.spin(vex::directionType::rev, speed, volt);
      lMiddleDrive.spin(vex::directionType::rev, speed, volt);
      rFrontDrive.spin(vex::directionType::rev, speed, volt);
      rMiddleDrive.spin(vex::directionType::rev, speed, volt);
      lBackDriveBackLift.spin(vex::directionType::fwd, speed, volt);
      rBackDriveCascadeLift.spin(vex::directionType::fwd, speed, volt);
      printf(" encoder: %f", getLeftEncoderRotation()*convertInches);
      wait(10, msec);
    }
    thread2.interrupt();
   
    while (getLeftEncoderRotation() > (actdist + acceldist)) {
      lFrontDrive.spin(vex::directionType::rev, 8.4, volt);
      lMiddleDrive.spin(vex::directionType::rev, 8.4, volt);
      rFrontDrive.spin(vex::directionType::rev, 8.4, volt);
      rMiddleDrive.spin(vex::directionType::rev, 8.4, volt);
      lBackDriveBackLift.spin(vex::directionType::fwd, 8.4, volt);
      rBackDriveCascadeLift.spin(vex::directionType::fwd, 8.4, volt);
    }


    acc.dist = acceldist * convertInches;
    //decelerate
    thread thread4(decelerate);
    targetL = getLeftEncoderRotation() - acceldist;
    while (getLeftEncoderRotation() > targetL) {
      //printf("decelerate %f\n", speed);
      lFrontDrive.spin(vex::directionType::rev, speed, volt);
      lMiddleDrive.spin(vex::directionType::rev, speed, volt);
      rFrontDrive.spin(vex::directionType::rev, speed, volt);
      rMiddleDrive.spin(vex::directionType::rev, speed, volt);
      lBackDriveBackLift.spin(vex::directionType::fwd, speed, volt);
      rBackDriveCascadeLift.spin(vex::directionType::fwd, speed, volt);
    } 
    thread4.interrupt();   
  }
  
  lFrontDrive.stop();
  lMiddleDrive.stop();
  rFrontDrive.stop();
  rMiddleDrive.stop();
  lBackDriveBackLift.stop();
  rBackDriveCascadeLift.stop();
  return 0;
}



int driveProfileslow(int dist, bool fwd) { //encoder orientation flipped 
  //Inertial.resetRotation();
  double acceldist = 0;
  int targetL = 0;
  double actdist;
  
  //determines acceleration and deceleration distance
  if (dist > 28) 
  {
    acceldist = 14;
  } 
  else {
    acceldist = dist / 2.0;
  }
  // Switching units to degrees here
  dist *= convertDegrees;
 
  if (fwd) {
   actdist = getLeftEncoderRotation() + dist;
  } else {
    actdist = getLeftEncoderRotation() - dist;
  }
  //going forward
  if (fwd)  {
    acc.dist = acceldist; // feeding acc.dist inch value -- accelerate() handles inches
    acc.fwd = fwd;

    thread thread1(accelerate);

    // accelerate-- switch to degrees
    acceldist *= convertDegrees;
    targetL = getLeftEncoderRotation() + acceldist; // target to finish acceleration
   
    while (getLeftEncoderRotation() < targetL) {
      lFrontDrive.spin(vex::directionType::fwd, speed, volt);
      lMiddleDrive.spin(vex::directionType::fwd, speed, volt);
      rFrontDrive.spin(vex::directionType::fwd, speed, volt);
      rMiddleDrive.spin(vex::directionType::fwd, speed, volt); 
      lBackDriveBackLift.spin(vex::directionType::rev, speed, volt);
      rBackDriveCascadeLift.spin(vex::directionType::rev, speed, volt);
      printf(" encoder: %f", getLeftEncoderRotation()*convertInches);
      wait(10, msec);
    }
    thread1.interrupt();
    while (getLeftEncoderRotation() < (actdist - acceldist)) {
      lFrontDrive.spin(vex::directionType::fwd, 7, volt);
      lMiddleDrive.spin(vex::directionType::fwd, 7, volt);
      rFrontDrive.spin(vex::directionType::fwd, 7, volt);
      rMiddleDrive.spin(vex::directionType::fwd, 7, volt); 
      lBackDriveBackLift.spin(vex::directionType::rev, 7, volt);
      rBackDriveCascadeLift.spin(vex::directionType::rev, 7, volt);
    } 
    acc.dist = acceldist * convertInches;
    thread thread3(decelerate);
    // decelerate
    targetL = getLeftEncoderRotation() + acceldist;
    while (getLeftEncoderRotation() < targetL ) {
      lFrontDrive.spin(vex::directionType::fwd, speed, volt);
      lMiddleDrive.spin(vex::directionType::fwd, speed, volt);
      rFrontDrive.spin(vex::directionType::fwd, speed, volt);
      rMiddleDrive.spin(vex::directionType::fwd, speed, volt);
      lBackDriveBackLift.spin(vex::directionType::rev, speed, volt);
      rBackDriveCascadeLift.spin(vex::directionType::rev, speed, volt);
      wait(10, msec);
    }
    thread3.interrupt();
  } 
  //backwards
  else {
    acc.dist = acceldist;
    acc.fwd = fwd;
    acceldist *= convertDegrees;
   
    thread thread2(accelerate);
    // accelerate
    targetL = getLeftEncoderRotation() - acceldist;
   
    while ((getLeftEncoderRotation() > targetL)) {
     // printf("accelerate: %f\n", speed);
      lFrontDrive.spin(vex::directionType::rev, speed, volt);
      lMiddleDrive.spin(vex::directionType::rev, speed, volt);
      rFrontDrive.spin(vex::directionType::rev, speed, volt);
      rMiddleDrive.spin(vex::directionType::rev, speed, volt);
      lBackDriveBackLift.spin(vex::directionType::fwd, speed, volt);
      rBackDriveCascadeLift.spin(vex::directionType::fwd, speed, volt);
      printf(" encoder: %f", getLeftEncoderRotation()*convertInches);
      wait(10, msec);
    }
    thread2.interrupt();
   
    while (getLeftEncoderRotation() > (actdist + acceldist)) {
      lFrontDrive.spin(vex::directionType::rev, 7, volt);
      lMiddleDrive.spin(vex::directionType::rev, 7, volt);
      rFrontDrive.spin(vex::directionType::rev, 7, volt);
      rMiddleDrive.spin(vex::directionType::rev, 7, volt);
      lBackDriveBackLift.spin(vex::directionType::fwd, 7, volt);
      rBackDriveCascadeLift.spin(vex::directionType::fwd, 7, volt);
    }


    acc.dist = acceldist * convertInches;
    //decelerate
    thread thread4(decelerate);
    targetL = getLeftEncoderRotation() - acceldist;
    while (getLeftEncoderRotation() > targetL) {
      //printf("decelerate %f\n", speed);
      lFrontDrive.spin(vex::directionType::rev, speed, volt);
      lMiddleDrive.spin(vex::directionType::rev, speed, volt);
      rFrontDrive.spin(vex::directionType::rev, speed, volt);
      rMiddleDrive.spin(vex::directionType::rev, speed, volt);
      lBackDriveBackLift.spin(vex::directionType::fwd, speed, volt);
      rBackDriveCascadeLift.spin(vex::directionType::fwd, speed, volt);
    } 
    thread4.interrupt();   
  }
  
  lFrontDrive.stop();
  lMiddleDrive.stop();
  rFrontDrive.stop();
  rMiddleDrive.stop();
  lBackDriveBackLift.stop();
  rBackDriveCascadeLift.stop();
  return 0;
}*/