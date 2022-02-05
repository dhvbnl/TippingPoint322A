#include "vex.h"

void screenGUI() {
    Brain.Screen.render();
  while (true) {
    //drawButton(rectOne, ClrAntiqueWhite);
    // Brain.Screen.drawRectangle(20, 80, 80, 40, rectangle);
    wait(100, msec);
  }
}

void drawButton(int info[], color col){
  
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
