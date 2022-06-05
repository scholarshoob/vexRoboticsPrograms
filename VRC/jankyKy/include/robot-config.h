using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor armMotor;
extern motor leftDriveFront;
extern motor leftDriveMiddle;
extern motor leftDriveBack;
extern motor rightDriveFront;
extern motor rightDriveMiddle;
extern motor rightDriveBack;
extern controller Controller1;
extern motor clawMotor;
extern signature visionSensor__YELLOW_GOAL;
extern signature visionSensor__SIG_2;
extern signature visionSensor__SIG_3;
extern signature visionSensor__SIG_4;
extern signature visionSensor__SIG_5;
extern signature visionSensor__SIG_6;
extern signature visionSensor__SIG_7;
extern vision visionSensor;
extern inertial inertialSensor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );