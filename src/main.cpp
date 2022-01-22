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

competition Competition;

void autonomous(void) {
}

int main() {
  Competition.autonomous(redalliance);
  Competition.drivercontrol(opcontrol);

  preauton();

  while (true) {
    wait(100, msec);
  }
}
