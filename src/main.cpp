/*-------------------------------------------*/
/*                                           */
/*    Program:      TippingPoint322A         */
/*    Author:       Synergy Robotics 322A    */
/*    Created:      Sat Oct 23 2021          */
/*    Description:  Tipping Point V1         */
/*                                           */
/*-------------------------------------------*/
#include "vex.h"

using namespace vex;

class Button {
public:
  int x, y, width, height;
  std::string text;
  color buttonColor, textColor;

  Button(int x, int y, int width, int height, std::string text,
         color buttonColor, color textColor)
      : x(x), y(y), width(width), height(height), text(text),
        buttonColor(buttonColor), textColor(textColor) {}

  void render() {
    Brain.Screen.drawRectangle(x, y, width, height, buttonColor);
    Brain.Screen.printAt(x + 10, y + 20, false, text.c_str());
  }

  bool isClicked() {
    if (Brain.Screen.pressing() && Brain.Screen.xPosition() >= x &&
        Brain.Screen.xPosition() <= x + width &&
        Brain.Screen.yPosition() >= y && Brain.Screen.yPosition() <= y + width)
      return true;
    return false;
  }
};

competition Competition;

int autonToRun = 0;
int spacing = 10;
int xSize = 107;
int ySize = 107;

Button autonButtons[] = {
    Button(spacing, spacing, xSize, ySize, "1", purple, white),
    Button(2 * spacing + xSize, spacing, xSize, ySize, "2", black, white),

    Button(3 * spacing + 2 * xSize, 10, xSize, ySize, "3", black, white),
    Button(4 * spacing + 3 * xSize, 10, xSize, ySize, "4", black, white),

    Button(spacing, spacing * 2 + ySize, xSize, ySize, "5", black, white),
    Button(spacing * 2 + xSize, spacing * 2 + ySize, xSize, ySize, "6", black,
           white),

    Button(3 * spacing + 2 * xSize, spacing * 2 + ySize, xSize, ySize, "7",
           black, white),
    Button(4 * spacing + 3 * xSize, spacing * 2 + ySize, xSize, ySize, "8",
           black, white),
};

void autonomous(void) {
  switch (autonToRun) {
  case 0: getPos();
    break;
  case 1: // code
    break;
  case 2: // code
    break;
  case 3: // code
    break;
  case 4: // code
    break;
  case 5: // code
    break;
  case 6: // code
    break;
  case 7: // code
    break;
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(opcontrol);
  preauton();

  while (true) {
    if (!Competition.isEnabled()) {
      Brain.Screen.clearScreen();
      for (int i = 0; i < 8; i++)
        autonButtons[i].render();
      while (!Competition.isEnabled()) {
        for (int i = 0; i < 8; i++) {
          if (autonButtons[i].isClicked()) {
            autonButtons[autonToRun].buttonColor = black;
            autonButtons[i].buttonColor = purple;
            autonButtons[autonToRun].render();
            autonButtons[i].render();
            autonToRun = i;
          }
        }
        wait(100, msec);
      }
    } else {
      Brain.Screen.clearScreen();
      Brain.Screen.drawImageFromFile("logo.png", 0, 0);
      while(Competition.isEnabled()){
        wait(100, msec);
      }
    }
  }
}
