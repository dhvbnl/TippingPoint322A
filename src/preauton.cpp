#include "vex.h"

void preauton() {
  vexcodeInit();
  //set cylinder postion
  rearClamp.set(1);
  frontClamp.set(1);

  //reset all sensors
  resetDrivetrain();
  resetEncoders();

  //set motor stopping type
  setDrivetrainCreep();

  //calibrate inertial sensor
  calibrateInertial();
  Controller.Screen.print("Preauton Complete");
 // thread controllerScreen(screenGUI);
}


