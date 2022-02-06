#include "vex.h"

// Global constants
const double errorMargin = 0.01;

struct Coordinate {
  double xPos;
  double yPos;
  double deltaH;
  double thetaRad;
  double linearDistance; 
  double headingRad;
} coor; 

void horizontalmove() {
  double refAngle;
  double headingDeg = coor.headingRad * (180 / M_PI);
  int dir = 0;

  if (headingDeg < 90) { // Quad 1
    refAngle  = headingDeg;
    dir = 1;
  } 
  else if (headingDeg < 180) { // Quad 4
    refAngle = 180 - headingDeg;
    dir = 2;
  } 
  else if (headingDeg < 270) { // Quad 3
    refAngle = headingDeg - 180;
    dir = 3;
  } 
  else {
    refAngle = 360 - headingDeg; // Quad 2
    dir = 4;
  }

  double deltaX = cos(refAngle * 180 / M_PI) * fabs(coor.deltaH);
  double deltaY = sin(refAngle * 180 / M_PI) * fabs(coor.deltaH); 

  if (coor.deltaH > 0) { // moving right (positive direction)
    if (dir % 2 == 1) { // Quads 1 or 3
      coor.xPos += deltaX;
      coor.yPos -= deltaY;
    } else { // Quads  2 or 4
      coor.xPos += deltaX;
      coor.yPos += deltaY;
    }
  } 
  else { // moving left (negative direction)
    if (dir % 2 == 1) {
      coor.xPos -= deltaX;
      coor.yPos += deltaY;
    } else {
      coor.xPos -= deltaX;
      coor.yPos -= deltaY;
    }
  }
}

double getxPos() {
  return coor.xPos;
}

double getyPos() {
  return coor.yPos;
}

int setPos (double x, double y, bool repeat) {
  
  double curr_xPos = coor.xPos;
  double curr_yPos = coor.yPos;
  double xdist = x - curr_xPos;
  double ydist = y - curr_yPos;
  double hyp = sqrt((xdist * xdist) + (ydist * ydist));
  double refAngle = fabs(atan(ydist/xdist)) * 180 / M_PI;
  
  wait(100, msec);

  if (xdist != 0 || ydist != 0) {
    // Using quadrants to calculate absolute angle to turn to
    // Current position (curr_xPos, curr_yPos) is new "center of origin" for quadrant system
    if (x > curr_xPos && y > curr_yPos) // Quadrant 1 angle
    {
      drivetrainTurn(90 - refAngle);
    } 
    else if (x < curr_xPos && y > curr_yPos) // Quadrant 2 angle
    {
      drivetrainTurn(270 + refAngle);
    } 
    else if (x < curr_xPos && y < curr_yPos) // Quadrant 3 angle
    {
      drivetrainTurn(270 - refAngle);
    } 
    else if (x > curr_xPos && y < curr_yPos)
    { 
      drivetrainTurn(90 + refAngle);
    } 
    else if (xdist == 0) 
    {
      Controller.Screen.print(ydist);
      hyp = fabs(ydist);
      if (ydist > 0 && fabs(getInertialHeading() - 0) > 1) {
        drivetrainTurn(0);
      } else if (ydist < 0 && fabs(getInertialHeading() - 0) > 1) {
        drivetrainTurn(180);
      }
    } 
    else if (ydist == 0) 
    {
      hyp = fabs(xdist);
      if (xdist > 0 && fabs(getInertialHeading() - 90) > 1) {
        drivetrainTurn(90);
      } else if (xdist < 0 && fabs(getInertialHeading() - 0) > 1) {
        drivetrainTurn(270);
      }
    }
    wait(100, msec);
    Controller.Screen.clearLine();
    Controller.Screen.print("here");
    printf(" refAng: %f", refAngle);
    driveProfileslow(hyp, true);
    
    if (repeat) 
    {
      if (fabs(x - coor.xPos) > 1 || fabs(y - coor.yPos) > 1) {
        setPos(x, y, false);
      }
    }
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
  double deltaHeading = 0.0;
  double lRadius = 0.0;
  double prevHeadRad = 0.0;

  coor.headingRad = 0.0;
  coor.deltaH = 0.0;
  coor.linearDistance = 0.0;
  coor.xPos = 0.0;
  coor.yPos = 0.0;

  while (true)
  {
      // Reading the odometry encoders
      currentEn = getVerticalEncoderRotation() * convertInches; 
      currentH = getHorizontalEncoderRotation() * convertInches;
      
      deltaEn = currentEn - previousEn;
      coor.deltaH = currentH - previousH;

      // Sensor-based heading reading in radians
      coor.headingRad = getInertialHeading() * (M_PI / 180);

      // Convert head from clockwise angle to counterclockwise (unit circle-based) angle
      coor.headingRad = fmod(((2.5 * M_PI) - coor.headingRad), (2 * M_PI)); 
    
      deltaHeading = coor.headingRad - prevHeadRad; // change in heading using inertial sensor readings

      // Calculate the incremental linear distance traveled.
      if (fabs(deltaHeading) < 0.01)
      {
          coor.linearDistance = deltaEn;
      }
      else
      {
          lRadius = deltaEn / deltaHeading; 
          coor.linearDistance = 2.0 * lRadius * sin(deltaHeading / 2.0);
      }

      // Calculate the incremental 2-dimensional coordinates x & y
      deltaX = coor.linearDistance * cos(coor.headingRad + (deltaHeading / 2.0));
      deltaY = coor.linearDistance * sin(coor.headingRad + (deltaHeading / 2.0));

      coor.xPos += deltaX; 
      coor.yPos += deltaY;
      printPos();

      horizontalTracker.changed(*horizontalmove);
      wait(10, msec);
      /* if (fabs(coor.deltaH) > 0.01) {
        horizontalmove();
      } */
      previousEn = currentEn;
      prevHeadRad = coor.headingRad;
      previousH = currentH;

      printf("x: %f", coor.xPos);
      printf("y: %f\n", coor.yPos);

      wait(10, msec); 
      Brain.Screen.clearLine();
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

void printPos() {
  printf("x: %f", coor.xPos);
  printf("y: %f\n", coor.yPos);
}


