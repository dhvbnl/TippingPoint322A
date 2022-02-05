#include "vex.h"

using namespace vex;

brain Brain;

controller Controller = controller(primary);

/* ENTER CORRECT PORTS FOR MOTORS*/
motor leftFrontDrive = motor(PORT2, ratio6_1, false);
motor leftMiddleDrive = motor(PORT9, ratio6_1, false);
motor leftBackDrive = motor(PORT19, ratio6_1, false);

motor rightFrontDrive = motor(PORT4, ratio6_1, true);
motor rightMiddleDrive = motor(PORT8, ratio6_1, true);
motor rightBackDrive = motor(PORT7, ratio6_1, true);

motor fourBar = motor(PORT10, ratio36_1, true);

motor intake = motor(PORT8, ratio18_1, true);

inertial inert = inertial(PORT5);

triport Expander = triport(PORT20);

encoder leftTracker = encoder(Expander.G);
encoder rightTracker = encoder(Expander.C);
encoder middleTracker = encoder(Brain.ThreeWirePort.B);

limit lBackTransmission = limit(Expander.B);
limit rBackTransmission = limit(Expander.A);

digital_out mBackDriveLift = digital_out(Expander.E);
digital_out mFrontLift = digital_out(Brain.ThreeWirePort.A);

pot lBackLift = pot(Expander.F);

void vexcodeInit(void) {
  
}