#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor rDriveB = motor(PORT1, ratio36_1, false);
motor rDriveM = motor(PORT2, ratio36_1, true);
controller Controller1 = controller(primary);
motor rDriveF = motor(PORT3, ratio36_1, false);
motor lDriveF = motor(PORT8, ratio36_1, true);
motor lDriveM = motor(PORT9, ratio36_1, false);
motor lDriveB = motor(PORT10, ratio36_1, true);

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