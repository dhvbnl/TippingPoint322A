#include "vex.h"

using namespace vex;

brain Brain;

controller Controller = controller(primary);

/* ENTER CORRECT PORTS FOR ALL*/
motor lFrontDrive = motor(PORT1, ratio6_1, false);
motor lMiddleDrive = motor(PORT2, ratio6_1, false);

motor rFrontDrive = motor(PORT3, ratio6_1, true);
motor rMiddleDrive = motor(PORT4, ratio6_1, true);

motor lBackDriveBackLift = motor(PORT5, ratio6_1, true);
motor rBackDriveFrontLift = motor(PORT6, ratio6_1, true);

motor mFrontIntakeBackDlift = motor(PORT7, ratio18_1, true);

motor mBackRotator = motor(PORT8, ratio18_1, true);

inertial mInertial = inertial(PORT9);

triport Expander = triport(PORT10);

encoder lTraker = encoder(Expander.A);
encoder rTracker = encoder(Expander.C);
encoder mTracker = encoder(Expander.E);

limit lBackTransmission = limit(Expander.G);
limit rBackTransmission = limit(Expander.H);

void vexcodeInit(void) {
  
}