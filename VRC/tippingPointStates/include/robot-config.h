using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor armMotor;
extern motor transmissionMotor;
extern motor rDriveF;
extern motor rDriveM;
extern motor rDriveB;
extern motor lDriveF;
extern motor lDriveM;
extern motor lDriveB;
extern controller Controller1;
extern signature visionSensor__SIG_1;
extern signature visionSensor__SIG_2;
extern signature visionSensor__SIG_3;
extern signature visionSensor__SIG_4;
extern signature visionSensor__SIG_5;
extern signature visionSensor__SIG_6;
extern signature visionSensor__SIG_7;
extern vision visionSensor;
extern digital_out transmissionPiston;
extern digital_out clawPiston;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );