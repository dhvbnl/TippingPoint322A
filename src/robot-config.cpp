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

motor fourBar = motor(PORT17, ratio6_1, false);

motor intake = motor(PORT6, ratio36_1, true);

inertial inert = inertial(PORT9);

triport bottomExpander = triport(PORT13);
triport topExander = triport(PORT2);

//encoder verticalTracker = encoder(Expander.A);
//encoder horizontalTracker = encoder(Expander.E);

digital_out rearClamp = digital_out(Brain.ThreeWirePort.G);  
digital_out frontClamp = digital_out(topExander.F);

digital_out frontClampStandoff = digital_out(topExander.E);
digital_out goalCover = digital_out(topExander.D);

limit rearClampLimit = limit(Brain.ThreeWirePort.H);
limit rearGoalLimit = limit(Brain.ThreeWirePort.B);

pot fourBarPot = pot(bottomExpander.D);

line frontLineTracker = line(topExander.G);
line intakeLineTracker = line(Brain.ThreeWirePort.A);

sonar rearSonar = sonar(Brain.ThreeWirePort.C);

//home values
signature REDGOAL = signature (1, 10267, 11207, 10736, -835, -387, -610, 11, 0);
signature YELLOWGOAL = signature (2, 2057, 2409, 2234, -3213, -2875, -3044, 9.2, 0);
signature BLUEGOAL = signature (3, -2759, -2009, -2384, 11045, 12621, 11834, 4.5, 0);

//comp values
//signature REDGOAL = signature (1, 10267, 11207, 10736, -835, -387, -610, 11, 0);
//signature YELLOWGOAL = signature (2, 2057, 2409, 2234, -3213, -2875, -3044, 9.4, 0);
//signature BLUEGOAL = signature (3, -2759, -2009, -2384, 11045, 12621, 11834, 6.5, 0);

vision frontVision = vision (PORT5, 25, REDGOAL, YELLOWGOAL, BLUEGOAL);
vision rearVision = vision (PORT4, 25, REDGOAL, YELLOWGOAL, BLUEGOAL);

void vexcodeInit(void) {
  
}