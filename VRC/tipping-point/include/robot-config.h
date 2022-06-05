using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor armR;
extern motor armL;
extern controller Controller1;
extern motor claw;
extern motor rDriveB;
extern motor rDriveF;
extern motor lDriveF;
extern motor lDriveB;
extern motor intake;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );