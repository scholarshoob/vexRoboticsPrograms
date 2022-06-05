#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor leftBaseB = motor(PORT1, ratio18_1, true);
motor leftBaseM = motor(PORT2, ratio18_1, true);
motor leftBaseF = motor(PORT3, ratio18_1, true);
motor rightBaseB = motor(PORT11, ratio18_1, false);
motor rightBaseM = motor(PORT12, ratio18_1, false);
motor rightBaseF = motor(PORT13, ratio18_1, false);
motor arm = motor(PORT9, ratio36_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}