using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor leftDriveFront;
extern motor leftDriveMiddle;
extern motor leftDriveBack;
extern motor armMotor;
extern motor clawMotor;
extern motor rightDriveBack;
extern motor rightDriveMiddle;
extern motor rightDriveFront;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );