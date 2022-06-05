#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor armMotor = motor(PORT8, ratio18_1, false);
motor leftDriveFront = motor(PORT1, ratio18_1, true);
motor leftDriveMiddle = motor(PORT2, ratio18_1, true);
motor leftDriveBack = motor(PORT3, ratio18_1, true);
motor rightDriveFront = motor(PORT11, ratio18_1, false);
motor rightDriveMiddle = motor(PORT12, ratio18_1, false);
motor rightDriveBack = motor(PORT13, ratio18_1, false);
controller Controller1 = controller(primary);
motor clawMotor = motor(PORT4, ratio18_1, false);
/*vex-vision-config:begin*/
signature visionSensor__YELLOW_GOAL = signature (1, 47, 3799, 1922, -5121, -3415, -4268, 3, 0);
vision visionSensor = vision (PORT10, 50, visionSensor__YELLOW_GOAL);
/*vex-vision-config:end*/
inertial inertialSensor = inertial(PORT14);

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