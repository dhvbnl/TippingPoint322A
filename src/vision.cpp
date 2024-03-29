#include "vex.h"

const int centerX = 165;
const int centerTol = 20;

//home
//const int redBrightness = 29;
//const int blueBrightness = 150;
//const int yellowBrightness = 12;

//comp
const int redBrightness = 50;
const int blueBrightness = 80;
const int yellowBrightness = 25;
void findFrontGoal(color col, signature sig, int basespeed, bool right,
                   bool check, bool risk) {
  if (col == red) {
    frontVision.setBrightness(redBrightness);
  } else if (col == blue) {
    frontVision.setBrightness(blueBrightness);
  } else if (col == yellow) {
    frontVision.setBrightness(yellowBrightness);
  }
  frontVision.takeSnapshot(sig);
  if (check) {
    if (right) {
      setDrivetrainSpeed(4.5, -4.5);
    } else {
      setDrivetrainSpeed(-4.5, 4.5);
    }
    while (frontVision.objectCount == 0 ||
           frontVision.largestObject.height < 10 ||
           frontVision.largestObject.width < 20) {
      wait(20, msec);
      frontVision.takeSnapshot(sig);
    }
  }

  vision::object test = frontVision.largestObject;
  if (!risk) {
    while (test.centerX < centerX - centerTol || test.centerX > centerX + centerTol) {
      if (test.centerX < centerX - centerTol) {
        setDrivetrainSpeed(-4, 4);
      } else if (test.centerX > centerX + centerTol) {
        setDrivetrainSpeed(4, -4);
      }
      wait(20, msec);
      frontVision.takeSnapshot(sig);
    }
  }

  int leftSpeed = basespeed;
  int rightSpeed = basespeed;
  while (test.centerY < 140) {
    if (test.centerY > 120) {
      basespeed = (140 - test.centerY) / 8 + 3;
    }
    if (test.centerY < 165) {
      if (test.centerX < centerX) {
        rightSpeed = basespeed;
        leftSpeed = basespeed + (test.centerX - centerX) * 0.1;
      } else {
        leftSpeed = basespeed;
        rightSpeed = basespeed - (test.centerX - centerX) * 0.1;
      }
    } else {
      leftSpeed = basespeed;
      rightSpeed = basespeed;
    }
    setDrivetrainSpeed(leftSpeed, rightSpeed);
    wait(20, msec);
    frontVision.takeSnapshot(sig);
  }
  while (frontLineTracker.value(pct) > 60) {
    setDrivetrainSpeed(3, 3);
    wait(20, msec);
  }
  setDrivetrainSpeed(0, 0);
}

void findRearGoal(color col, signature sig, int basespeed, bool right,bool check, bool risk) {
  if (col == red) {
    rearVision.setBrightness(redBrightness);
  } else if (col == blue) {
    rearVision.setBrightness(blueBrightness);
  } else if (col == yellow) {
    rearVision.setBrightness(yellowBrightness);
  }
  
  frontVision.takeSnapshot(sig);
  if (check) {
    if (right) {
      setDrivetrainSpeed(4.5, -4.5);
    } else {
      setDrivetrainSpeed(-4.5, 4.5);
    }

    while (rearVision.objectCount == 0 ||
           rearVision.largestObject.height < 15 ||
           rearVision.largestObject.width < 35) {
      wait(20, msec);
      rearVision.takeSnapshot(sig);
    }
  }

  vision::object test = rearVision.largestObject;
  if (!risk) {
    while (test.centerX < centerX - centerTol ||
           test.centerX > centerX + centerTol) {
      if (test.centerX < centerX - centerTol) {
        setDrivetrainSpeed(-3, 3);
      } else if (test.centerX > centerX + centerTol) {
        setDrivetrainSpeed(3, -3);
      }
      wait(20, msec);
      rearVision.takeSnapshot(sig);
    }
  }

  int leftSpeed = -basespeed;
  int rightSpeed = -basespeed;
  int goalDist = rearSonar.distance(inches);
  while(goalDist < 5){
    wait(20, msec);
  }
  while (goalDist > 9) {
    if (goalDist < 21) {
      basespeed = (goalDist) / 3;
    }
    if (test.centerY < centerX) {
      if (test.centerX < centerX) {
        rightSpeed = -basespeed;
        leftSpeed = -basespeed + (test.centerX - centerX) * 0.07;
      } else {
        leftSpeed = -basespeed;
        rightSpeed = -basespeed - (test.centerX - centerX) * 0.07;
      }
    } else {
      leftSpeed = -basespeed;
      rightSpeed = -basespeed;
    }
    setDrivetrainSpeed(leftSpeed, rightSpeed);
    wait(20, msec);
    rearVision.takeSnapshot(sig);
    goalDist = rearSonar.distance(inches);
  }
  while (!rearGoalLimit.pressing()) {
    setDrivetrainSpeed(-3, -3);
    wait(20, msec);
  }
  setDrivetrainSpeed(0, 0);
}

void backUpSonar(int dist, int speed){
  int setSpeed;
  while(rearSonar.distance(inches) > dist){
    int distanceRemaining = rearSonar.distance(inches) - dist;
    setSpeed = distanceRemaining / 3  + 3 < speed ? distanceRemaining / 3 + 3: speed;
    setDrivetrainSpeed(-setSpeed, -setSpeed);
    wait(20, msec);
  }
  setDrivetrainSpeed(0, 0);
}