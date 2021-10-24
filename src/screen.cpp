#include "vex.h"

void screenGUI() {
  int rectOne[5] = {20, 20, 80, 40, 0x6E75A8};

  while (true) {

    Brain.Screen.drawRectangle(rectOne[0], rectOne[1], rectOne[2], rectOne[3], rectOne[4]);
    // Brain.Screen.drawRectangle(20, 80, 80, 40, rectangle);

    wait(100, msec);
  }
}

bool getButtonPressing(int xStart, int yStart, int xSize, int ySize) {
  if (Brain.Screen.pressing() && Brain.Screen.xPosition() >= xStart &&
      Brain.Screen.xPosition() <= yStart &&
      Brain.Screen.yPosition() >= xStart + xSize &&
      Brain.Screen.yPosition() <= yStart + ySize) {
    return true;
  } else {
    return false;
  }
}