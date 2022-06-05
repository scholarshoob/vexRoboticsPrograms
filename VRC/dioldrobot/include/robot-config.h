using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor leftBaseB;
extern motor leftBaseM;
extern motor leftBaseF;
extern motor rightBaseB;
extern motor rightBaseM;
extern motor rightBaseF;
extern motor arm;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );