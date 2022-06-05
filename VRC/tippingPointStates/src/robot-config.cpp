#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor armMotor = motor(PORT9, ratio18_1, false);
motor transmissionMotor = motor(PORT10, ratio18_1, false);
motor rDriveF = motor(PORT13, ratio18_1, false);
motor rDriveM = motor(PORT12, ratio18_1, false);
motor rDriveB = motor(PORT11, ratio18_1, false);
motor lDriveF = motor(PORT8, ratio18_1, true);
motor lDriveM = motor(PORT2, ratio18_1, true);
motor lDriveB = motor(PORT1, ratio18_1, true);
controller Controller1 = controller(primary);
/*vex-vision-config:begin*/
vision visionSensor = vision (PORT20, 50);
/*vex-vision-config:end*/
digital_out transmissionPiston = digital_out(Brain.ThreeWirePort.A);
digital_out clawPiston = digital_out(Brain.ThreeWirePort.B);

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