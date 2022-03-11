#include "vex.h"

// Global constants
//const double errorMargin = 0.01;
const double V_trackWidth = 1.5;
const double H_trackWidth = 2.50;

 struct Coordinate {
   double xPos;
   double yPos;
   double deltaH;
   double thetaRad;
   double linearDistance; 
   double headingRad;
   double clockwiseHeadRad;
   double deltaHeading;
} coor; 

void horizontalmove() {
  double radius; double linearDistance;
  double deltaX; double deltaY;
      
      // Calculate the incremental linear distance traveled.
    if (fabs(coor.deltaHeading) < 0.01)
    {
        linearDistance = coor.deltaH;
    }
    else
    {
        radius = (coor.deltaH / coor.deltaHeading) - H_trackWidth; 
        linearDistance = 2.0 * radius * sin(coor.deltaHeading / 2.0);
    }

    // Calculate the incremental 2-dimensional coordinates x & y
    deltaX = linearDistance * cos(2 * M_PI - (M_PI / 2 - coor.headingRad + coor.deltaHeading / 2.0));
    deltaY = linearDistance * sin(2 * M_PI - (M_PI / 2 - coor.headingRad + coor.deltaHeading / 2.0));

  // coor.deltaH = coor.deltaH - H_trackWidth * coor.deltaHeading;

  // if (fabs(coor.deltaHeading) <= 0.5) {
  //   deltaX = coor.deltaH;
  // }
  // else {
  //   deltaX = (2 * sin(coor.deltaH / 2)) * (coor.deltaH/coor.deltaHeading + H_trackWidth);
  //   deltaY = (2 * sin(coor.deltaH/2))*(deltaRight/deltaTheta +V_trackWidth);
  // }
    coor.xPos +=deltaX;
    coor.yPos += deltaY;

  wait(100, msec);
}

// turn the robot based on absolute position from the original point of the robot
void drivetrainTurn(double targetdeg) {

   // proportionality constants
  // double kP = 0.388;
  // double kI = .00001;
  // double kD = 0.12;
//last working variation (volts, no velocity check)
  //  double kP = 0.21;
  //  double kI = 0.001;
  //  double kD = 1.8;
  //  if (frontLineTracker.value(pct) < 60) {
  //    kP = 0.8;
  //    kI = 0.001;
  //    kD = 1.5;
  //  }

  double kP = 0.7;
  double kI = 0.003;
  double kD = 1.5;

  // double kP = 0.55;
  // double kI = 0.005;
  // double kD = 1.3;

  // double pU = 0.675;
  // double kU = 1.17 * 0.6;
  // double kP = 0.5 * kU;
  // double kI = 1.2 * kU / pU;
  // double kD = 0.075 * kU * pU + 0.4;

  /*if(rearClampLimit.pressing()){
    kP = 0.47;
    kI = 0.001;
    kD = 1.2;
  }*/

  double tempX = coor.xPos;
  double tempY = coor.yPos;

  // PID loop variables
  double error = 0.0;
  double integral = 0.0;
  double derivative = 0.0;
  double prevError = 0.0;
  double motorPower = 0.0;
  bool useright = true;
  double avgvel = 0;
  double speed;
  const double minMotorPower = 2.5;
  double changevel = 2.5;
  int x = 0;
  while (fabs(targetdeg - getInertialHeading()) > 1) {
    // PID loop to determine motorPower at any given point in time
    x++;
    avgvel = (fabs(leftFrontDrive.velocity(pct)) + fabs(rightFrontDrive.velocity(pct))) / 2;
    
    double head = getInertialHeading();
    // printf("head %f \n", head);

    double errorright = targetdeg - head;
    if (targetdeg < head) {
      errorright = 360 - head + targetdeg;
    }

    double errorleft = fabs(targetdeg - head);
    if (targetdeg > head) {
      errorleft = 360 + head - targetdeg;
    }

    if (errorright < errorleft) {
      error = errorright;
      useright = true;
    } else {
      error = errorleft;
      useright = false;
    }

    // pid stuff
    
    integral = integral + error;
    if ((error == 0.0) or (error > targetdeg)) {
      integral = 0.0;
    }
    derivative = error - prevError;
    
    speed = (error * kP + integral * kI + derivative * kD);
    motorPower = speed;
    if (avgvel < speed) {
      motorPower += (speed - avgvel) * changevel;
    } else if (avgvel > speed) {
      motorPower -= (avgvel - speed) * changevel;
    } 

    motorPower = motorPower * 12/100;
    prevError = error;

    if (motorPower < minMotorPower) {
      motorPower = minMotorPower;
    }

  
    // powering the motors
    if (!useright) {
      leftFrontDrive.spin(fwd, -motorPower, volt);
      leftMiddleDrive.spin(fwd, -motorPower, volt);
      leftBackDrive.spin(fwd, -motorPower, volt);
      rightMiddleDrive.spin(fwd, motorPower, volt);
      rightFrontDrive.spin(fwd, motorPower, volt);
      rightBackDrive.spin(fwd, motorPower, volt);
    } else {
      leftFrontDrive.spin(fwd, motorPower, volt);
      leftMiddleDrive.spin(fwd, motorPower, volt);
      leftBackDrive.spin(fwd, motorPower, volt);
      rightMiddleDrive.spin(fwd, -motorPower, volt);
      rightFrontDrive.spin(fwd, -motorPower, volt);
      rightBackDrive.spin(fwd, -motorPower, volt);
    }
    wait(10, msec);

  } // end while()

  leftMiddleDrive.stop();
  rightMiddleDrive.stop();
  leftFrontDrive.stop();
  rightFrontDrive.stop();
  rightBackDrive.stop();
  leftBackDrive.stop();
  
  coor.xPos = tempX;
  coor.yPos = tempY;
  // printf("x: %f", coor.xPos);
  // printf("y: %f\n", coor.yPos);

}
/*void drivetrainTurn(double targetdeg) {
   // proportionality constants
  double kP = 0.4;
  double kI = 0.002;
  double kD = 0.6;

  // PID loop variables
  double error = 1;
  double integral = 0;
  double derivative = 0;
  double prevError = 0;
  double motorPower = 0;
  bool useright = true;
  while (fabs(targetdeg - getInertialHeading()) > 2) {
    // PID loop to determine motorPower at any given point in time
    double head = getInertialHeading();
    double errorright = targetdeg - head;
    if (targetdeg < head) {
      errorright = 360 - head + targetdeg;
    }
    double errorleft = fabs(targetdeg - head);
    if (targetdeg > head) {
      errorleft = 360 + head - targetdeg;
    }
    if (errorright < errorleft) {
      error = errorright;
      useright = true;
    } else {
      error = errorleft;
      useright = false;
    }
    // pid stuff
    integral = integral + error;
    if (error == 0 or error > targetdeg) {
      integral = 0;
    }
    derivative = error - prevError;
    motorPower = (error * kP + integral * kI + derivative * kD);
    prevError = error;

    wait(15, msec);

    // powering the motors
    if (!useright) {
      leftFrontDrive.spin(fwd, -motorPower, pct);
      leftMiddleDrive.spin(fwd, -motorPower, pct);
      leftBackDrive.spin(fwd, -motorPower, pct);
      rightMiddleDrive.spin(fwd, motorPower, pct);
      rightFrontDrive.spin(fwd, motorPower, pct);
      rightBackDrive.spin(fwd, motorPower, pct);
    } else {
      leftFrontDrive.spin(fwd, motorPower, pct);
      leftMiddleDrive.spin(fwd, motorPower, pct);
      leftBackDrive.spin(fwd, motorPower, pct);
      rightMiddleDrive.spin(fwd, -motorPower, pct);
      rightFrontDrive.spin(fwd, -motorPower, pct);
      rightBackDrive.spin(fwd, -motorPower, pct);
    }
  }
  leftMiddleDrive.stop();
  rightMiddleDrive.stop();
  leftFrontDrive.stop();
  rightFrontDrive.stop();
  rightBackDrive.stop();
  leftBackDrive.stop();
}*/

double getxPos() {
  return coor.xPos;
}

double getyPos() {
  return coor.yPos;
}

// if endHeading doesn't matter, input a number > 360
int setPos (double x, double y, double speed, bool fwd) {
  
  double curr_xPos = coor.xPos;
  double curr_yPos = coor.yPos;
  double xdist = x - curr_xPos;
  double ydist = y - curr_yPos;
  double hyp = sqrt((xdist * xdist) + (ydist * ydist));
  double refAngle = fabs(atan(ydist/xdist)) * 180 / M_PI;
  
  wait(10, msec);
 // printf("refangle %f\n", refAngle);
  if (xdist != 0 || ydist != 0) {
    if (xdist == 0) {
      Controller.Screen.print(ydist);
      hyp = fabs(ydist);
      if (fabs(ydist) > 0) {
        if (fwd) {
          if (fabs(getInertialHeading()) > 1 && fabs(getInertialHeading()) < 359) {
            drivetrainTurn(0);
          }
        } else {
          if (fabs(getInertialHeading() - 180) > 1) { 
            drivetrainTurn(180);
          }
        }
      } 
      else if (ydist < 0) {
        if (fwd) {
          if (fabs(getInertialHeading() - 180) > 1) {
            drivetrainTurn(180);
          }  
        } else {
          if (fabs(getInertialHeading()) > 1 && fabs(getInertialHeading()) < 359)  {
            drivetrainTurn(0);
          }
        }
      }
    } 
    else if (ydist == 0) 
    {
      hyp = fabs(xdist);
      if (xdist > 0 && fabs(getInertialHeading() - 90) > 1) {
        if (fwd) drivetrainTurn(90);
        if (!fwd) drivetrainTurn(270);
      } 
      else if (xdist < 0  && (fabs(getInertialHeading()) > 1 || fabs(getInertialHeading()) < 359)) {
        if (fwd) drivetrainTurn(270);
        if (!fwd) drivetrainTurn(90);
      }
    }
    // Using quadrants to calculate absolute angle to turn to
    // Current position (curr_xPos, curr_yPos) is new "center of origin" for quadrant system
    else if (x > curr_xPos && y > curr_yPos) // Quadrant 1 angle
    {
      if (fwd) drivetrainTurn(90 - refAngle);
      if (!fwd) drivetrainTurn(270 - refAngle);
    } 
    else if (x < curr_xPos && y > curr_yPos) // Quadrant 2 angle
    {
      if (fwd) drivetrainTurn(270 + refAngle);
      if (!fwd) drivetrainTurn(90 + refAngle);
    } 
    else if (x < curr_xPos && y < curr_yPos) // Quadrant 3 angle
    {
      if (fwd) drivetrainTurn(270 - refAngle);
      if (!fwd) drivetrainTurn(90 - refAngle);
    } 
    else if (x > curr_xPos && y < curr_yPos)
    { 
      if (fwd) drivetrainTurn(90 + refAngle);
      if (!fwd) drivetrainTurn(270 + refAngle);
    } 
    
    wait(100, msec);
    Controller.Screen.clearLine();
    //Controller.Screen.print("here");
    //printf(" refAng: %f", refAngle);
    driveProfile(hyp, speed, fwd);
    printf("x: %f", coor.xPos);
    printf("y: %f\n", coor.yPos);
    // if (endHeading < 360) {
    //   drivetrainTurn(endHeading);
    // }
    
    /*if (fabs(x - coor.xPos) > 1 || fabs(y - coor.yPos) > 1) {
      setPos(x, y, fwd, endHeading);
    }*/
    
  }

  return 0;
} 

int getPos()
{
  double currentEn = 0.0;
  double currentH = 0.0; 
  double previousEn = 0.0;
  double previousH = 0.0;
  double deltaEn = 0.0;
  double deltaX = 0.0;
  double deltaY = 0.0;
  double radius = 0.0;
  double prevHeadRad = 0.0;

  coor.deltaHeading = 0.0;
  coor.clockwiseHeadRad = 0.0; // heading by clockwise angle
  coor.headingRad = 0.0;
  coor.deltaH = 0.0;
  coor.linearDistance = 0.0;
  coor.xPos = 4.85023 - 0.000230;
  coor.yPos = -4.849925 - 0.000075;

  while (true)
  {
      // Reading the odometry encoders
      currentEn = getVerticalEncoderRotation() * convertInches; 
      currentH = getHorizontalEncoderRotation() * convertInches;
      
      deltaEn = currentEn - previousEn;
      coor.deltaH = currentH - previousH;

      // Sensor-based heading reading in radians
      coor.headingRad = getInertialHeading() * (M_PI / 180);
      
      coor.clockwiseHeadRad = coor.headingRad;

      // Convert head from clockwise angle to counterclockwise (unit circle-based) angle
      coor.headingRad = fmod(((2.5 * M_PI) - coor.headingRad), (2 * M_PI)); 
    
      coor.deltaHeading = coor.headingRad - prevHeadRad; // change in heading using inertial sensor readings

      // Calculate the incremental linear distance traveled.
      if (fabs(coor.deltaHeading) < 0.01)
      {
          coor.linearDistance = deltaEn;
      }
      else
      {
          radius = (deltaEn / coor.deltaHeading) + V_trackWidth; 
          coor.linearDistance = 2.0 * radius * sin(coor.deltaHeading / 2.0);
      }

      // Calculate the incremental 2-dimensional coordinates x & y
      deltaX = coor.linearDistance * cos(coor.headingRad + (coor.deltaHeading / 2.0));
      deltaY = coor.linearDistance * sin(coor.headingRad + (coor.deltaHeading / 2.0));

      coor.xPos += deltaX; 
      coor.yPos += deltaY;

      //printf("delta h: %f\n", coor.deltaH);
      horizontalmove();
      wait(100, msec);
      previousEn = currentEn;
      prevHeadRad = coor.headingRad;
      previousH = currentH;

      //printf("heading deg: %f", coor.clockwiseHeadRad * (180 / M_PI));
       printf("x: %f", coor.xPos);
       printf("y: %f\n", coor.yPos);
      //printf("%f\n", coor.headingRad);

      wait(100, msec); 
      //Brain.Screen.clearLine();
    }

  return 0;
}

int getPosition() {
  const double verticalRad = 1.25;
  const double horizRad = 3.0;
  const double verticaldisp = 1.25;
  const double horizdisp = 2.0;

  double currentHoriz = 0.0;
  double previousHoriz = 0.0;
  double currentVertical = 0.0;
  double previousVertical = 0.0;
  double deltaEnVertical = 0.0;
  double deltaEnHoriz = 0.0;

  double deltaX = 0.0;
  double deltaY = 0.0;
  double radius = 0.0;
  double prevHeadRad = 0.0;
  double inertialHead = 0.0;

  double verticalArcRad = 0.0;
  double linearDistanceVertical = 0.0;
  double horizArcRad = 0.0;
  double linearDistanceHorizontal = 0.0;

  coor.deltaHeading = 0.0;
  coor.clockwiseHeadRad = 0.0; // heading by clockwise angle
  coor.headingRad = 0.0;
  coor.linearDistance = 0.0;
  coor.xPos = 0;
  coor.yPos = 0;
  double iter = 0;

  while (true)
  {
      // Reading the odometry encoders
      currentVertical = getVerticalEncoderRotation() * convertInches; 
      currentHoriz = getHorizontalEncoderRotation() * convertInches;

      // Inertial-based heading reading in radians
      inertialHead = getInertialHeading();
      coor.headingRad = inertialHead * (M_PI / 180);
      // coor.clockwiseHeadRad = coor.headingRad;

      // Convert head from clockwise angle to counterclockwise (unit circle-based) angle
      coor.headingRad = fmod(((2.5 * M_PI) - coor.headingRad), (2 * M_PI)); 

      if (!(iter == 0)) {
        coor.deltaHeading = coor.headingRad - prevHeadRad; // change in heading using inertial sensor readings
      }

      // arc lengths - with correction of location of tracking wheels
      deltaEnVertical = (currentVertical - previousVertical);
      deltaEnHoriz = (currentHoriz- previousHoriz);
      // deltaEnVertical = (currentVertical - previousVertical) - (verticalRad * coor.deltaHeading);
      // deltaEnHoriz = (currentHoriz- previousHoriz) - (horizRad * coor.deltaHeading);

      // Calculate the incremental linear distance traveled.
      if (fabs(coor.deltaHeading) < 0.01)
      {
        linearDistanceVertical = deltaEnVertical;
        linearDistanceHorizontal = deltaEnHoriz;
      }
      else
      {
        verticalArcRad = (deltaEnVertical / coor.deltaHeading) - verticaldisp;
        linearDistanceVertical = 2.0 * verticalArcRad * sin(coor.deltaHeading / 2.0);


        horizArcRad = (deltaEnHoriz / coor.deltaHeading) + horizdisp;
        linearDistanceHorizontal = 2.0 * horizArcRad * sin(coor.deltaHeading / 2.0);
      }

      deltaY = linearDistanceVertical * sin(coor.headingRad + (coor.deltaHeading / 2.0));
      deltaX = linearDistanceHorizontal * cos(2 * M_PI - (M_PI / 2 - coor.headingRad + coor.deltaHeading / 2.0));

      coor.xPos += deltaX; 
      coor.yPos += deltaY;
      wait(100, msec);
      previousVertical = currentVertical;
      previousHoriz = currentHoriz;
      prevHeadRad = coor.headingRad;

      //printf("heading deg: %f", coor.clockwiseHeadRad * (180 / M_PI));
       printf("x: %f", coor.xPos);
       printf("y: %f\n", coor.yPos);
      //printf("%f\n", coor.headingRad);

      wait(100, msec); 
      //Brain.Screen.clearLine();
      iter++;
    }

  return 0;
}



void hi() {
  horizontalTracker.resetRotation();
  horizontalTracker.setRotation(0, deg);
  while (true) {
    printf("encoder h: %f\n", getHorizontalEncoderRotation());
  }
} 
void printinertial() {
  while (true) {
    printf("print inertial %f \n", getInertialHeading());
    wait(100, msec);
  }
}
void arcturn (double left, double right, double turnangle) {
  while (getInertialHeading() < turnangle - 2 || getInertialHeading() > turnangle + 2) {
    leftFrontDrive.spin(fwd, left, volt);
    leftMiddleDrive.spin(fwd, left, volt);
    leftBackDrive.spin(fwd, left, volt);
    rightFrontDrive.spin(fwd, right, volt);
    rightMiddleDrive.spin(fwd, right, volt);
    rightBackDrive.spin(fwd, right, volt);
    wait(10, msec);
  }
  leftFrontDrive.stop();
  leftMiddleDrive.stop();
  leftBackDrive.stop();
  rightFrontDrive.stop();
  rightMiddleDrive.stop();
  rightBackDrive.stop();
}

void turnNoPid(double deg) {
  while(getInertialHeading() < deg || getInertialHeading() > deg) 
  {
    leftFrontDrive.spin(vex::directionType::fwd, 4, volt);
    leftMiddleDrive.spin(vex::directionType::fwd, 4, volt);
    rightFrontDrive.spin(vex::directionType::rev, 4, volt);
    rightMiddleDrive.spin(vex::directionType::rev, 4, volt);
    leftBackDrive.spin(vex::directionType::fwd, 4, volt);
    rightBackDrive.spin(vex::directionType::rev, 4, volt);
  }
  leftMiddleDrive.stop();
  rightMiddleDrive.stop();
  leftFrontDrive.stop();
  rightFrontDrive.stop();
  rightBackDrive.stop();
  leftBackDrive.stop();
}
void stopdrive() {
  leftMiddleDrive.stop();
  rightMiddleDrive.stop();
  leftFrontDrive.stop();
  rightFrontDrive.stop();
  rightBackDrive.stop();
  leftBackDrive.stop();
}

