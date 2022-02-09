#include "vex.h"

void screenGUI() {
  while (true) {
    Controller.Screen.clearScreen();
    Controller.Screen.setCursor(0, 0);
    Controller.Screen.print(tempInfoDrive().c_str());
    Controller.Screen.newLine();
    Controller.Screen.print("hi");
    wait(500, msec);
  }
}

