#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor rightBaseM = motor(PORT10, ratio36_1, true);
motor rightBaseB = motor(PORT19, ratio36_1, false);
motor claw = motor(PORT3, ratio18_1, true);
motor leftBaseB = motor(PORT11, ratio36_1, true);
motor leftBaseF = motor(PORT8, ratio36_1, true);
motor rightBaseF = motor(PORT20, ratio36_1, false);
motor leftBaseM = motor(PORT9, ratio36_1, false);
motor arm = motor(PORT2, ratio36_1, true);
controller Controller1 = controller(primary);

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