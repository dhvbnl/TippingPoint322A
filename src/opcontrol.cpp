#include "vex.h"

void opcontrol()
{
  //make sure drivetrain is set to coast
  setDrivetrainCreep();

  //start all control tasks
  thread driveMove(drivetrainControl);
  thread liftMove(liftControl);
  
  while(true)
  {
    wait(100, msec);
  }
}