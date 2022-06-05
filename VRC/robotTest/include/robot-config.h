using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor rDriveB;
extern motor rDriveM;
extern controller Controller1;
extern motor rDriveF;
extern motor lDriveF;
extern motor lDriveM;
extern motor lDriveB;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );