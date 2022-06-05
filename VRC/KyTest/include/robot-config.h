using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor rDriveF;
extern motor rDriveM;
extern motor rDriveB;
extern motor lDriveF;
extern motor lDriveM;
extern motor lDriveB;
extern controller Controller1;
extern motor armMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );