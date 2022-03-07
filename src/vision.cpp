#include "vex.h"

const int centerX = 165;
const int centerTol = 20;

void findFrontGoal(color col, signature sig, int basespeed, bool right,
                   bool check, bool risk) {
  if (col == red) {
    frontVision.setBrightness(29);
  } else if (col == blue) {
    frontVision.setBrightness(150);
  } else if (col == yellow) {
    frontVision.setBrightness(12);
  }
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
  while (test.centerY < 160) {
    if (test.centerY > 130) {
      basespeed = (160 - test.centerY) / 8 + 3;
    }
    if (test.centerY < centerX) {
      if (test.centerX < centerX) {
        rightSpeed = basespeed;
        leftSpeed = basespeed + (test.centerX - centerX) * 0.07;
      } else {
        leftSpeed = basespeed;
        rightSpeed = basespeed - (test.centerX - centerX) * 0.07;
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
    setDrivetrainSpeed(4.5, 4.5);
    wait(20, msec);
  }
  setDrivetrainSpeed(0, 0);
}

void findRearGoal(color col, signature sig, int basespeed, bool right,bool check, bool risk) {
  if (col == red) {
    rearVision.setBrightness(29);
  } else if (col == blue) {
    rearVision.setBrightness(150);
  } else if (col == yellow) {
    rearVision.setBrightness(12);
  }

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