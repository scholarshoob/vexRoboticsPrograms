using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor rightBaseM;
extern motor rightBaseB;
extern motor claw;
extern motor leftBaseB;
extern motor leftBaseF;
extern motor rightBaseF;
extern motor leftBaseM;
extern motor arm;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );