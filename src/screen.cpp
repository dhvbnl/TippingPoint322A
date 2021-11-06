#include "vex.h"

void screenGUI() {
  int rectOne[5] = {20, 20, 80, 40, 0x00F0F8FF};

  while (true) {
    //drawButton(rectOne, ClrAntiqueWhite);
    // Brain.Screen.drawRectangle(20, 80, 80, 40, rectangle);
    Brain.Screen.drawImageFromFile("logo.png", 82, 0);
    wait(100, msec);
  }
}

void drawButton(int info[], color col){

  if(getButtonPressing(info)){
    Brain.Screen.drawRectangle(info[0], info[1], info[2], info[3], white);
  }
  else{
    Brain.Screen.drawRectangle(info[0], info[1], info[2], info[3], ClrAqua);
  }
    

  
  
}

bool getButtonPressing(int info[]) {
  if (Brain.Screen.pressing() && Brain.Screen.xPosition() >= info[0] &&
      Brain.Screen.yPosition() >= info[1] &&
      Brain.Screen.xPosition() <= info[0] + info[2] &&
      Brain.Screen.yPosition() <= info[1] + info[3]) {
    return true;
  } else {
    return false;
  }
}