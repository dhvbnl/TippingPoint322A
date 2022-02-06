
#include "vex.h"

struct Acceleration {
  double dist;
  bool fwd;
  double deg;
  double maxspeed;
} acc;

double speed = 0;

int move(double speed, bool fwd) {
  if (fwd) {
    leftFrontDrive.spin(vex::directionType::fwd, speed, volt);
    leftMiddleDrive.spin(vex::directionType::fwd, speed, volt);
    rightFrontDrive.spin(vex::directionType::fwd, speed, volt);
    rightMiddleDrive.spin(vex::directionType::fwd, speed, volt); 
    leftBackDrive.spin(vex::directionType::fwd, speed, volt);
    rightBackDrive.spin(vex::directionType::fwd, speed, volt);
  } else {
    leftFrontDrive.spin(vex::directionType::rev, speed, volt);
    leftMiddleDrive.spin(vex::directionType::rev, speed, volt);
    rightFrontDrive.spin(vex::directionType::rev, speed, volt);
    rightMiddleDrive.spin(vex::directionType::rev, speed, volt);
    leftBackDrive.spin(vex::directionType::rev, speed, volt);
    rightBackDrive.spin(vex::directionType::rev, speed, volt);
  }
  return 0;
}
//accelerate
int accelerate() {
  //robot current position
  double lorig = getVerticalEncoderRotation() * convertInches;
  //if the robot is going forwards
  if (acc.fwd) {
    //distance we want the robot to go to + where robot currently is
    acc.dist += lorig;
    while ((getVerticalEncoderRotation() * convertInches) < acc.dist) {
      //speed = 4.0 * (fabs((fabs(getLeftEncoderRotation()) * convertInches) - lorig) + 1) + 2.6;
      speed = 5 * pow((fabs((fabs(getVerticalEncoderRotation()) * convertInches) - lorig) + 1), 2) + 2.6;
      //if (speed > 11)
        //speed = 11;
      if (speed > acc.maxspeed)
        speed = acc.maxspeed;
      wait(10, msec);
    }
  //if the robot is going backwards
  } else {
    //distance we want the robot to go to - where the robot currently is (becaues the robot is going backwards)
    acc.dist = lorig - acc.dist;
    while ((getVerticalEncoderRotation() * convertInches) > acc.dist) {
      //speed = 3.2 * (fabs((fabs(getLeftEncoderRotation()) * convertInches) - lorig) + 1) + 2.6;
      speed = 4 * pow((fabs((fabs(getVerticalEncoderRotation()) * convertInches) - lorig) + 1), 2) + 2.6;
      //if (speed > 9)
       // speed = 9;
      if (speed > acc.maxspeed) 
        speed = acc.maxspeed;
      wait(10, msec);
    }
  }
  return 0;
}
//decelerate
int decelerate() {
  //robot current position (in inches)
  double lorig = getVerticalEncoderRotation() * convertInches;
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
    while ((getVerticalEncoderRotation() * convertInches) < acc.dist) {
      speed = 1.1 * exp((-0.2 * fabs((fabs(getVerticalEncoderRotation()) * convertInches) - lorig + n)) + 2) + 1.15;
        if (speed > acc.maxspeed) speed = acc.maxspeed;
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
    while ((getVerticalEncoderRotation() * convertInches) > acc.dist) {
      speed = 1.1 * exp((-0.2 * fabs((fabs(getVerticalEncoderRotation()) * convertInches) - lorig + n)) + 2) + 1.15; 
        if (speed > acc.maxspeed) speed = acc.maxspeed;
        if (speed < 3) speed = 3;
        wait(10, msec);
    }
  }
  return 0;
}



int driveProfile(int dist, double maxspeed, bool fwd) { //encoder orientation flipped
  //Inertial.resetRotation();
  double acceldist = 0;
  int targetL = 0;
  double actdist;
  acc.maxspeed = maxspeed;
 
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
    actdist = getVerticalEncoderRotation() + dist;
  } else {
    actdist = getVerticalEncoderRotation() - dist;
  }
  //going forward
  if (fwd)  {
    acc.dist = acceldist; // feeding acc.dist inch value -- accelerate() handles inches
    acc.fwd = fwd;

    thread thread1(accelerate);

    // accelerate-- switch to degrees
    acceldist *= convertDegrees;
    targetL = getVerticalEncoderRotation() + acceldist; // target to finish acceleration
   
    while (getVerticalEncoderRotation() < targetL) {
      move(speed, false);
      printf(" encoder: %f", getVerticalEncoderRotation() * convertInches);
      wait(10, msec);
    }
    thread1.interrupt();
    while (getVerticalEncoderRotation() < (actdist - acceldist)) {
      move(maxspeed, false);
    } 
    acc.dist = acceldist * convertInches;
    thread thread3(decelerate);
    // decelerate
    targetL = getVerticalEncoderRotation() + acceldist;
    while (getVerticalEncoderRotation() < targetL ) {
      move(speed, false);
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
    targetL = getVerticalEncoderRotation() - acceldist;
   
    while ((getVerticalEncoderRotation() > targetL)) {
     // printf("accelerate: %f\n", speed);
      move(speed, false);
      printf(" encoder: %f", getVerticalEncoderRotation() * convertInches);
      wait(10, msec);
    }
    thread2.interrupt();
   
    while (getVerticalEncoderRotation() > (actdist + acceldist)) {
      move(maxspeed, false);
    }


    acc.dist = acceldist * convertInches;
    //decelerate
    thread thread4(decelerate);
    targetL = getVerticalEncoderRotation() - acceldist;
    while (getVerticalEncoderRotation() > targetL) {
      //printf("decelerate %f\n", speed);
      move(speed, false);
    } 
    thread4.interrupt();   
  }
 
  leftFrontDrive.stop();
  leftMiddleDrive.stop();
  rightFrontDrive.stop();
  rightMiddleDrive.stop();
  rightBackDrive.stop();
  leftBackDrive.stop();
  return 0;
}
