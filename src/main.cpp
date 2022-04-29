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
    Brain.Screen.printAt(x + 15, y + 50, false, text.c_str());
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
bool redSide = true;
color autonColor = red;
signature autonSig = REDGOAL;
bool selected = false;
int spacing = 10;
int xSize = 107;
int ySize = 107;

Button autonButtons[] = {
    Button(spacing, spacing, xSize, ySize, "NWIN", purple, white),
    Button(2 * spacing + xSize, spacing, xSize, ySize, "RIGHT", black, white),

    Button(3 * spacing + 2 * xSize, 10, xSize, ySize, "LEFT", black, white),
    Button(4 * spacing + 3 * xSize, 10, xSize, ySize, "MID", black, white),

    Button(spacing, spacing * 2 + ySize, xSize, ySize, "WIN", black, white),
    Button(spacing * 2 + xSize, spacing * 2 + ySize, xSize, ySize, "SKILLS", black,
           white),

    Button(3 * spacing + 2 * xSize, spacing * 2 + ySize, xSize, ySize, "RED",
           red, white),
    Button(4 * spacing + 3 * xSize, spacing * 2 + ySize, xSize, ySize, "BLUE",
           black, white),
};

void autonomous(void) {
  if (redSide) {
    switch (autonToRun) {
    case 0:
      //visionTesting();
      skills();
      break;
    case 1:
      allianceRightNeutral(red, REDGOAL);
      break;
    case 2:
      allianceLeftNeutral(red, REDGOAL);
      break;
    case 3:
      allianceMiddleNeutral(red, REDGOAL);
      break;
    case 4: // code
      break;
    case 5:
      skills();
      break;
    case 6: // code
      break;
    case 7:
      break;
    }
  } else {
    switch (autonToRun) {
    case 0:
      allianceMain(blue, BLUEGOAL);
      break;
    case 1:
      allianceRightNeutral(blue, BLUEGOAL);
      break;
    case 2:
      allianceLeftNeutral(blue, BLUEGOAL);
      break;
    case 3:
      allianceMiddleNeutral(blue, BLUEGOAL);
      break;
    case 4: // code
      break;
    case 5:
      skills();
      break;
    case 6: // code
      break;
    case 7:
      break;
    }
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(opcontrol);
  preauton();

  while (true) {
    if (!Competition.isEnabled()) {
      Brain.Screen.clearScreen();
      Brain.Screen.setFont(prop30);
      for (int i = 0; i < 8; i++){
        autonButtons[i].render();
      }
        
      while (!Competition.isEnabled()) {
        for (int i = 0; i < 6; i++) {
          if (autonButtons[i].isClicked()) {
            frontVision.setLedColor(255, 255, 255);
            autonButtons[autonToRun].buttonColor = black;
            autonButtons[i].buttonColor = purple;
            autonButtons[autonToRun].render();
            autonButtons[i].render();
            autonToRun = i;
            selected = true;
          }
        }
        for (int i = 6; i < 8; i++) {
          if (autonButtons[i].isClicked()) {
            if(i == 6){
              rearVision.setLedColor(255, 0, 0);
              autonButtons[7].buttonColor = black;
              autonButtons[i].buttonColor = red;
              autonButtons[7].render();
              autonButtons[i].render();
              redSide = true; 
            } else if(i == 7){
              rearVision.setLedColor(0, 0, 255);
              autonButtons[6].buttonColor = black;
              autonButtons[i].buttonColor = blue;
              autonButtons[6].render();
              autonButtons[i].render();
              redSide = false;
            }
          }
        }
        if(redSide){
          rearVision.setLedColor(255, 0, 0);
        } else{
          rearVision.setLedColor(0, 0, 255);
        }
        if(!selected)
        {
          frontVision.setLedColor(0, 255, 0);
        }
        wait(100, msec);
      }
    } else {
      Brain.Screen.clearScreen();
      Brain.Screen.drawImageFromFile("logo.png", 0, 0);
      frontVision.setLedColor(128, 0, 128);
      rearVision.setLedColor(128, 0, 128);
      while(Competition.isEnabled()){
        wait(100, msec);
      }
    }
  }
}

bool taskStop(){
  if(Competition.isAutonomous())
    return true;
  return false;
}
