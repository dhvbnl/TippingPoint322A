#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

#include "robot-config.h"
#include "screen.h"
#include "controller.h"
#include "drivetrain.h"
#include "lifts.h"
#include "opcontrol.h"

//maximum safe temperature for motors
const int tempLimit = 55;

//convert between velocity and voltage.
const double voltageConverstion = 100/12;

//global var


#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)