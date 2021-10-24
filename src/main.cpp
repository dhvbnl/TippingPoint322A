/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Synergy Robotics 322A                                     */
/*    Created:      Sat Oct 23 2021                                           */
/*    Description:  Tipping Point V1                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

competition Competition;

void pre_auton(void) {
  vexcodeInit();

}

void autonomous(void) {
}

void usercontrol(void) {
  while (1) {
    wait(20, msec);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();
  
  while (true) {
    wait(100, msec);
  }
}
