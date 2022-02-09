#include "vex.h"

void preauton() {
  vexcodeInit();
  //set cylinder postion
  rearClamp.set(1);
  wait(100, msec);

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


