#include "vex.h"

using namespace vex;

brain Brain;

controller Controller = controller(primary);

/* ENTER CORRECT PORTS FOR MOTORS*/
motor lFrontDrive = motor(PORT1, ratio6_1, false);
motor lMiddleDrive = motor(PORT2, ratio6_1, false);

motor rFrontDrive = motor(PORT3, ratio6_1, true);
motor rMiddleDrive = motor(PORT4, ratio6_1, true);

motor lBackDriveBackLift = motor(PORT5, ratio6_1, true);
motor rBackDriveFrontLift = motor(PORT6, ratio6_1, true);

motor mFrontIntakeBackDlift = motor(PORT7, ratio18_1, true);

motor mBackRotator = motor(PORT8, ratio18_1, true);

inertial mInertial = inertial(PORT9);

triport Expander = triport(PORT2);

encoder lTraker = encoder(Expander.G);
encoder rTracker = encoder(Expander.C);
//encoder mTracker = encoder(INSERT);

limit lBackTransmission = limit(Expander.B);
limit rBackTransmission = limit(Expander.A);

digital_out mBackDriveLift = digital_out(Expander.E);

pot lBackLift = pot(Expander.F);

void vexcodeInit(void) {
  
}