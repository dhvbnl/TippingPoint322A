using namespace vex;

extern brain Brain;

extern controller Controller;

//main drive motors
extern motor leftFrontDrive;
extern motor leftMiddleDrive;
extern motor rightFrontDrive;
extern motor rightMiddleDrive;
extern motor leftBackDrive;
extern motor rightBackDrive;

//intake/dr4b shared motor
extern motor fourBar;

//goal rotator
extern motor mBackRotator;

//sensors
extern inertial inert;

extern triport bExpander;

extern encoder verticalTracker;
extern encoder horizontalTracker;

extern pot fourBarPot;

void vexcodeInit(void);
