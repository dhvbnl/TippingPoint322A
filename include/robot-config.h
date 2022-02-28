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

//intake 
extern motor intake;

//goal rotator
extern motor mBackRotator;

//sensors
extern inertial inert;

extern triport bExpander;

extern encoder verticalTracker;
extern encoder horizontalTracker;

extern digital_out rearClamp;
extern digital_out frontClamp;

extern limit rearClampLimit;

extern pot fourBarPot;

extern line rearRingCheck;

void vexcodeInit(void);
