#include "vex.h"

void preauton() {
  //Controller.Screen.print("Preauton starting");
  vexcodeInit();

  //setMFrontLiftCylinder();
  //reset all sensors
  resetDrivetrain();
  resetEncoders();

  //set motor stopping type
  setDrivetrainCreep();

  //calibrate inertial sensor
  calibrateInertial();
  Controller.Screen.print("Preauton Complete");
  Brain.Screen.print("Preauton complete :)");
}


