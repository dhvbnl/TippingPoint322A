#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

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

triport Expander = triport(PORT13);

encoder verticalTracker = encoder(Expander.A);
encoder horizontalTracker = encoder(Expander.E);

digital_out rearClamp = digital_out(Expander.C);  
digital_out frontClamp = digital_out(Brain.ThreeWirePort.A);

limit rearClampLimit = limit(Brain.ThreeWirePort.B);
limit rearGoalLimit = limit(Brain.ThreeWirePort.E);

pot fourBarPot = pot(Expander.D);

line frontLineTracker = line(Brain.ThreeWirePort.F);
line intakeLineTracker = line(Brain.ThreeWirePort.H);

sonar rearSonar = sonar(Brain.ThreeWirePort.C);

signature REDGOAL = signature (1, 10267, 11207, 10736, -835, -387, -610, 11, 0);
signature YELLOWGOAL = signature (2, 2057, 2409, 2234, -3213, -2875, -3044, 9.2, 0);
signature BLUEGOAL = signature (3, -2759, -2009, -2384, 11045, 12621, 11834, 4.5, 0);

vision frontVision = vision (PORT6, 25, REDGOAL, YELLOWGOAL, BLUEGOAL);
vision rearVision = vision (PORT7, 25, REDGOAL, YELLOWGOAL, BLUEGOAL);

void vexcodeInit(void) {
  
}