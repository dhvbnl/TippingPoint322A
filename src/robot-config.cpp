#include "vex.h"

using namespace vex;

brain Brain;

controller Controller = controller(primary);

/* ENTER CORRECT PORTS FOR MOTORS*/
motor lFrontDrive = motor(PORT2, ratio6_1, false);
motor lMiddleDrive = motor(PORT9, ratio6_1, false);

motor rFrontDrive = motor(PORT4, ratio6_1, true);
motor rMiddleDrive = motor(PORT8, ratio6_1, true);

motor lBackDriveBackLift = motor(PORT19, ratio6_1, false);
motor rBackDriveCascadeLift = motor(PORT7, ratio6_1, true);

motor mFrontIntakeBackDlift = motor(PORT10, ratio36_1, true);

motor mBackRotator = motor(PORT8, ratio18_1, true);

inertial mInertial = inertial(PORT9);

triport Expander = triport(PORT20);

encoder lTraker = encoder(Expander.G);
encoder rTracker = encoder(Expander.C);
//encoder mTracker = encoder(INSERT);

limit lBackTransmission = limit(Expander.B);
limit rBackTransmission = limit(Expander.A);

digital_out mBackDriveLift = digital_out(Expander.E);
digital_out mFrontLift = digital_out(Brain.ThreeWirePort.B);

pot lBackLift = pot(Expander.F);

void vexcodeInit(void) {
  
}