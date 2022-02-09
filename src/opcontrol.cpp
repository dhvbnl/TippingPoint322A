#include "vex.h"

void opcontrol()
{
  //make sure drivetrain is set to coast
  setDrivetrainCreep();

  //start all control tasks
  thread driveMove(drivetrainControl);
  thread liftMove(liftControl);
  //thread controllerScreen(screenGUI);
  
  while(true)
  {
    wait(10, msec);
  }
}