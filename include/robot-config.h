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

extern encoder leftTracker;
extern encoder rightTracker;
extern encoder middleTracker;
//extern encoder mTracker;
extern encoder encoderH;

extern limit lBackTransmission;
extern limit rBackTransmission;

extern digital_out mBackDriveLift;
extern digital_out mFrontLift;

extern pot fourBarPot;

void vexcodeInit(void);
