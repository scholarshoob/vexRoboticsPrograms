// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// leftBaseB            motor         1               
// leftBaseM            motor         2               
// leftBaseF            motor         3               
// rightBaseB           motor         11              
// rightBaseM           motor         12              
// rightBaseF           motor         13              
// arm                  motor         9               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

competition Competition;

void pre_auton(void) {
  // Initializing Robot Configuration
  vexcodeInit();
}

int startingArea = 1;

class Mechanism{ 
  public:
  motor *mechanismMotor;
    Mechanism(motor &attachedMotor){
      mechanismMotor = &attachedMotor;
      mechanismMotor->setVelocity(100, percent);
    };  
    void moveMotorForward(int speed){
      mechanismMotor->spin(forward, speed, percent);
    }

    void moveMotorBackward(int speed){
      mechanismMotor->spin(reverse, speed, percent);
    }

    void stopMotor(){
      mechanismMotor->setStopping(hold);
      mechanismMotor->stop();
    }
};

Mechanism Claw(claw);
Mechanism Arm(arm);

enum AutonPos {rightAuton = 1, leftAuton = 2, rightMiddle = 3, leftMiddle = 4};

void cycleStartArea(){
  if(startingArea == 4){
    startingArea = 1;
  }
  else{
    startingArea += 1;
  }
}

void cycleBack(){
  if(startingArea == 1){
    startingArea = 4;
  }
  else{
    startingArea -= 1;
  }
}

void brainScreen(){
  while(true){
    Controller1.ButtonRight.pressed(cycleBack);
    Controller1.ButtonLeft.pressed(cycleStartArea);
    Brain.Screen.clearLine();
    switch(startingArea){
      case(rightAuton):
        Brain.Screen.print("Right Side Auton");
        break;
      case(leftAuton):
        Brain.Screen.print("Left Side Auton");
        break;
      case(rightMiddle):
        Brain.Screen.print("Right Middle Auton");
        break;
      case(leftMiddle):
        Brain.Screen.print("Left Middle Auton");
        break;
      default:
        break;
    }
    if(Controller1.ButtonUp.pressing()){
      Brain.Screen.newLine();
      Brain.Screen.print("Selected!");
      break;
    }
  }
}

void debugScreen(){
  while(true){
    Brain.Screen.clearScreen();
    Controller1.Screen.clearScreen();
    Brain.Screen.print(arm.temperature(percent));
    Controller1.Screen.print(arm.temperature(percent));
  }
}

void setRobotSpeed(int percentage){
  rightBaseB.setVelocity(percentage, percent);
  rightBaseM.setVelocity(percentage, percent);
  rightBaseF.setVelocity(percentage, percent);
  leftBaseB.setVelocity(percentage, percent);
  leftBaseM.setVelocity(percentage, percent);
  leftBaseF.setVelocity(percentage, percent);
}

void moveRobot(float rotations){
  rightBaseB.spinFor(rotations, turns, false);
  rightBaseM.spinFor(rotations, turns, false); 
  rightBaseF.spinFor(rotations, turns, false);
  leftBaseB.spinFor(rotations, turns, false);
  leftBaseM.spinFor(rotations, turns, false);
  leftBaseF.spinFor(rotations, turns);
  rightBaseB.setStopping(brake);
  rightBaseM.setStopping(brake);
  rightBaseF.setStopping(brake);
  leftBaseB.setStopping(brake);
  leftBaseM.setStopping(brake);
  leftBaseF.setStopping(brake);
  rightBaseB.stop();
  rightBaseM.stop();
  rightBaseF.stop();
  leftBaseB.stop();
  leftBaseM.stop();
  leftBaseF.stop();
  wait(0.1 ,seconds);
}

void turnRobot(float rotations){
  rightBaseB.spinFor(-1.0 * rotations, turns, false);
  rightBaseM.spinFor(-1.0 * rotations, turns, false);
  rightBaseF.spinFor(-1.0 * rotations, turns, false);
  leftBaseB.spinFor(rotations, turns, false);
  leftBaseM.spinFor(rotations, turns, false);
  leftBaseF.spinFor(rotations, turns);
  rightBaseB.setStopping(brake);
  rightBaseM.setStopping(brake);
  rightBaseF.setStopping(brake);
  leftBaseB.setStopping(brake);
  leftBaseM.setStopping(brake);
  leftBaseF.setStopping(brake);
  rightBaseB.stop();
  rightBaseM.stop();
  rightBaseF.stop();
  leftBaseB.stop();
  leftBaseM.stop();
  leftBaseF.stop();
  wait(0.1 ,seconds);
}

void stopRobot(){
  rightBaseB.stop();
  rightBaseM.stop();
  rightBaseF.stop();
  leftBaseB.stop();
  leftBaseM.stop();
  leftBaseF.stop();
}

void closeClaw(){
  claw.setVelocity(100, percent);
  claw.setMaxTorque(100, percent);
  claw.spin(forward);
  wait(0.5, seconds);
  claw.setStopping(hold);
  claw.stop();
}

void openClaw(){
  claw.setVelocity(100, percent);
  claw.setMaxTorque(100, percent);
  claw.spin(reverse);
  wait(0.5, seconds);
  claw.setStopping(hold);
  claw.stop();
}
void pre_teleop(){
  setRobotSpeed(100);
}


/** Auton Functions **/

void pickUpRightYellowGoal()
{
  // Move Forward
  setRobotSpeed(100);
  moveRobot(2.7);
  setRobotSpeed(65);
  moveRobot(0.15);
   //was moveRobot(2.8) and speed (50) moveRobot(0.8)
   // Close Claw
  closeClaw();
  // Back up to scoring line
  moveRobot(-1.8);
  // Release Goal
  openClaw();
  moveRobot(-0.3);
  arm.setVelocity(100, percent);
  arm.spin(forward);
  wait(1.8, seconds);
  arm.stop();
}

void pickUpLeftYellowGoal(){
  // Move Forward
  setRobotSpeed(100);
  moveRobot(2.7);
  setRobotSpeed(65);
  moveRobot(0.15);
   //was moveRobot(2.8) and speed (50) moveRobot(0.8)
   // Close Claw
  closeClaw();
  // Back up to scoring line
  moveRobot(-1.8);
  // Release Goal
  openClaw();
  moveRobot(-0.1);
  arm.setVelocity(100, percent);
  arm.spin(forward);
  wait(1.8, seconds);
  arm.stop();
}

void moveGoalFromTriangle(){
  // Start after pickUpYellowGoalFromStart();
  //Make the turn value negative so it turns correctly
  turnRobot(-0.37);
  moveRobot(-1.0);
  wait(1, seconds);
  stopRobot();
  arm.spin(reverse);
  wait(2.1, seconds);
  arm.stop();
  moveRobot(0.3);
}

void pickUpBridgeGoal(){
  turnRobot(-0.32);
  moveRobot(-1.0);
  wait(1, seconds);
  stopRobot();
  arm.spin(reverse);
  wait(2.1, seconds);
  arm.stop();
  moveRobot(0.5);
}

bool intakeAutoOn = false;
void toggleIntake(){
  if (intakeAutoOn){
    intakeAutoOn = false;
  }
  else{
    intakeAutoOn = true;
  }
}

void leftSideAuton(){
  //Default
  //moveGoalFromTriangle();
  pickUpBridgeGoal();
}

void rightSideAuton(){
  moveGoalFromTriangle();
}

void pickUpMiddleGoal(){
 setRobotSpeed(100);
 moveRobot(0.8);
 setRobotSpeed(65);
 moveRobot(0.15);
 closeClaw();
 moveRobot(-0.65);
 openClaw();
 moveRobot(-0.1);
}

void rightWinPointAuton(){
  moveRobot(1.45);
  turnRobot(0.6);
  moveRobot(1.7);
  closeClaw();
  moveRobot(-1.7);
  openClaw();
}

void leftWinPointAuton(){
  claw.setVelocity(30, percent);
  claw.spinFor(forward, 0.5, turns);
  claw.setVelocity(100, percent);
  claw.spin(reverse);
  wait(0.5, seconds);
  claw.setStopping(coast);
  claw.stop();
  wait(0.5, seconds);
  setRobotSpeed(30);
  moveRobot(-1.0);
  wait(1, seconds);
}

void autonomous() {
  if(startingArea <= 2){
    if(startingArea == leftAuton){
      pickUpLeftYellowGoal();
      leftSideAuton();
    }  
    else if(startingArea == rightAuton){
      pickUpRightYellowGoal();
      rightSideAuton();
    } 
    else if(startingArea >= 3){
      if(startingArea == rightMiddle){
        pickUpRightYellowGoal();
        turnRobot(0.5);
        pickUpMiddleGoal();
      }    
    }
    else if(startingArea == leftMiddle){
        pickUpLeftYellowGoal();
        turnRobot(-0.5);
        pickUpMiddleGoal();
    }
  }
}

void usercontrol() {
  pre_teleop();
  // Threshold stops the motors when Axis values are close to zero.
  int threshold = 5;
  bool leftSideSpeedOverThreashold = false;
  bool rightSideSpeedOverThreashold = false;
  int leftSideSpeedOverThreasholdCounter = 0;
  // direction 1 means forward, -1 means reversed
  int leftSideSpeedDirection = 1;
  int rightSideSpeedOverThreasholdCounter = 0;
  // direction 1 means forward, -1 means reversed
  int rightSideSpeedDirection = 1;
  int leftSideSpeed = 0;
  // Get the velocity percentage of the right motor. (Axis2)
  int rightSideSpeed = 0;
  while (true) {
    // Get the velocity percentage of the left motor. (Axis3)
    leftSideSpeed = Controller1.Axis3.position();
    // Get the velocity percentage of the right motor. (Axis2)
    rightSideSpeed = Controller1.Axis2.position();

    // Set the speed of the left motor. If the value is less than the
    // threshold, set it to zero.
    if (abs(leftSideSpeed) < threshold) {
      // Decrement the threashold counter by 1 each time the controller
      // Loops
      if (leftSideSpeedOverThreashold) {
        leftSideSpeedOverThreashold = false;
        leftSideSpeedOverThreasholdCounter = 5;
      }
      if (leftSideSpeedOverThreasholdCounter > 0) {
        leftBaseF.setVelocity(10 * (leftSideSpeedOverThreasholdCounter - 1) *
                                leftSideSpeedDirection,
                            percent);
        leftBaseM.setVelocity(10 * (leftSideSpeedOverThreasholdCounter - 1) *
                                leftSideSpeedDirection,
                            percent);
        leftBaseB.setVelocity(10 * (leftSideSpeedOverThreasholdCounter - 1) *
                                leftSideSpeedDirection,
                            percent);
        leftSideSpeedOverThreasholdCounter -= 1;
      } else {
        leftBaseF.setVelocity(0, percent);
        leftBaseM.setVelocity(0, percent);
        leftBaseB.setVelocity(0, percent);
      }
    } else {
      // Set the speed to leftSideSpeed
      leftBaseF.setVelocity(leftSideSpeed, percent);
      leftBaseM.setVelocity(leftSideSpeed, percent);
      leftBaseB.setVelocity(leftSideSpeed, percent);
      // Mark leftSideSpeed was greater than threashold
      leftSideSpeedOverThreashold = true;
      if (leftSideSpeed > 0) {
        leftSideSpeedDirection = 1;
      } else {
        leftSideSpeedDirection = -1;
      }
    }
    // Set the speed of the right motor. If the value is less than the
    // threshold, set it to zero.
    if (abs(rightSideSpeed) < threshold) {
      // Set the speed to zero
      if (rightSideSpeedOverThreashold) {
        rightSideSpeedOverThreashold = false;
        rightSideSpeedOverThreasholdCounter = 5;
      }
      if (rightSideSpeedOverThreasholdCounter > 0) {
        rightBaseF.setVelocity(10 * (rightSideSpeedOverThreasholdCounter - 1) *
                                rightSideSpeedDirection,
                            percent);
        rightBaseM.setVelocity(10 * (rightSideSpeedOverThreasholdCounter - 1) *
                                rightSideSpeedDirection,
                            percent);
        rightBaseB.setVelocity(10 * (rightSideSpeedOverThreasholdCounter - 1) *
                                rightSideSpeedDirection,
                            percent);
        rightSideSpeedOverThreasholdCounter -= 1;
      } else {
        rightBaseF.setVelocity(0, percent);
        rightBaseM.setVelocity(0, percent);
        rightBaseB.setVelocity(0, percent);
      }
    } else {
      // Set the speed to rightSideSpeed
      rightBaseF.setVelocity(rightSideSpeed, percent);
      rightBaseM.setVelocity(rightSideSpeed, percent);
      rightBaseB.setVelocity(rightSideSpeed, percent);
      rightSideSpeedOverThreashold = true;
      if (rightSideSpeed > 0) {
        rightSideSpeedDirection = 1;
      } else {
        rightSideSpeedDirection = -1;
      }
    }
    rightBaseF.spin(forward);
    leftBaseF.spin(forward);
    rightBaseM.spin(forward);
    leftBaseM.spin(forward);
    rightBaseB.spin(forward);
    leftBaseB.spin(forward);

    // Claw Control
    if(Controller1.ButtonR1.pressing()){
      Claw.moveMotorBackward(100);
    }
    else if(Controller1.ButtonR2.pressing()){
      Claw.moveMotorForward(100);
    }
    else{
      Claw.stopMotor();
    }

    // Arm Control
    if(Controller1.ButtonL1.pressing()){
      Arm.moveMotorForward(100);
    }
    else if(Controller1.ButtonL2.pressing()){
      Arm.moveMotorBackward(100);
    }
    else{
      Arm.stopMotor();
    }
    
    // Intake Control
    if (Controller1.ButtonX.pressing()){
      if(intakeAutoOn){
        intakeAutoOn = false;
      }
      else if (intakeAutoOn == false){
        intakeAutoOn = true;
      }
    }
  }
  wait(20, msec);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  Brain.Screen.clearScreen();
  pre_auton();
  brainScreen();
  //debugScreen();
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Auton and op-control
  // autonomous();
  // usercontrol();
  // Prevent main from exiting with an infinite loop.
  /*
  while (true) {
    wait(100, msec);
  }
  */
}