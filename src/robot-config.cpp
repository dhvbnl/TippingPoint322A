#include "vex.h"

using namespace vex;

brain Brain;

controller Controller = controller(primary);

/* ENTER CORRECT PORTS FOR MOTORS*/
motor leftFrontDrive = motor(PORT18, ratio18_1, true);
motor leftMiddleDrive = motor(PORT19, ratio18_1, true);
motor leftBackDrive = motor(PORT10, ratio18_1, true);

motor rightFrontDrive = motor(PORT16, ratio18_1, false);
motor rightMiddleDrive = motor(PORT15, ratio18_1, false);
motor rightBackDrive = motor(PORT20, ratio18_1, false);

motor fourBar = motor(PORT17, ratio18_1, false);

motor intake = motor(PORT8, ratio18_1, true);

inertial inert = inertial(PORT9);

triport Expander = triport(PORT11);

encoder verticalTracker = encoder(Expander.A);
encoder horizontalTracker = encoder(Expander.E);

digital_out rearClamp = digital_out(Expander.C);
digital_out frontClamp = digital_out(Brain.ThreeWirePort.A);

pot fourBarPot = pot(Expander.D);

void vexcodeInit(void) {
  
}