using namespace vex;

extern brain Brain;

extern controller Controller;

//main drive motors
extern motor lFrontDrive;
extern motor lMiddleDrive;
extern motor rFrontDrive;
extern motor rMiddleDrive;

//transmission drive motors
extern motor lBackDriveBackLift;
extern motor rBackDriveCascadeLift;

//intake/dr4b shared motor
extern motor mFrontIntakeBackDlift;

//goal rotator
extern motor mBackRotator;

//sensors
extern inertial mInertial;

extern triport bExpander;

extern encoder lTraker;
extern encoder rTracker;
extern encoder mTracker;
extern encoder encoderH;

extern limit lBackTransmission;
extern limit rBackTransmission;

extern digital_out mBackDriveLift;

extern pot lBackLift;

void vexcodeInit(void);
