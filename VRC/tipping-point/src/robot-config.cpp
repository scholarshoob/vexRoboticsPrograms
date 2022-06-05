#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor armR = motor(PORT10, ratio18_1, true);
motor armL = motor(PORT19, ratio18_1, false);
controller Controller1 = controller(primary);
motor claw = motor(PORT9, ratio18_1, false);
motor rDriveB = motor(PORT5, ratio18_1, true);
motor rDriveF = motor(PORT4, ratio18_1, true);
motor lDriveF = motor(PORT17, ratio18_1, false);
motor lDriveB = motor(PORT18, ratio18_1, false);
motor intake = motor(PORT8, ratio18_1, false);

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