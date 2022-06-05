/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\sylar                                            */
/*    Created:      Fri Mar 04 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// armMotor             motor         9               
// transmissionMotor    motor         10              
// rDriveF              motor         13              
// rDriveM              motor         12              
// rDriveB              motor         11              
// lDriveF              motor         8               
// lDriveM              motor         2               
// lDriveB              motor         1               
// Controller1          controller                    
// visionSensor         vision        20              
// transmissionPiston   digital_out   A               
// clawPiston           digital_out   B               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;
competition Competition;

motor_group leftDrive = motor_group(lDriveF, lDriveM, lDriveB);
motor_group rightDrive = motor_group(rDriveF, rDriveM, rDriveB);

enum autonPos {
  rightAuton = 1,
  leftAuton = 2,
  rightMiddle = 3,
  leftMiddle = 4
};
int startingArea = 1;

void cycleAutonPos() {
  if (startingArea == 4) {
    startingArea = 1;
  } else {
    startingArea += 1;
  }
}

void cycleAutonPosRev() {
  if (startingArea == 1) {
    startingArea = 4;
  } else {
    startingArea -= 1;
  }
}

void activeBrainScreen() {
  while (true) {
    Controller1.ButtonRight.pressed(cycleAutonPos);
    Controller1.ButtonLeft.pressed(cycleAutonPosRev);
    Brain.Screen.clearLine();

    switch (startingArea) {
    case (rightAuton):
      Brain.Screen.print("Right Side Auton");
      break;
    case (leftAuton):
      Brain.Screen.print("Left Side Auton");
      break;
    case (rightMiddle):
      Brain.Screen.print("Right Middle Auton");
      break;
    case (leftMiddle):
      Brain.Screen.print("Left Middle Auton");
      break;
    default:
      break;
    }

    if (Controller1.ButtonUp.pressing()) {
      Brain.Screen.newLine();
      Brain.Screen.print("Selected");
      break;
    }
  }
}

void setRobotSpeed(int percentage) {
  leftDrive.setVelocity(percentage, percent);
  rightDrive.setVelocity(percentage, percent);
}

void stopRobot() {
  leftDrive.setStopping(brake);
  rightDrive.setStopping(brake);
  leftDrive.stop();
  rightDrive.stop();
}

void moveRobot(float rotations) {
  stopRobot();
  leftDrive.spinFor(rotations, turns, false);
  rightDrive.spinFor(rotations, turns, true);
  wait(0.05, seconds);
}

void turnRobot(float rotations) {
  stopRobot();
  leftDrive.spinFor(rotations, turns, false);
  rightDrive.spinFor(-rotations, turns, false);
  stopRobot();
}

void openClaw(){
  clawPiston.set(false);
}

void closeClaw(){
  clawPiston.set(true);
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
  moveRobot(-0.1);
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
}

void moveGoalFromTriangle(){
  // Start after pickUpYellowGoalFromStart();
  //Make the turn value negative so it turns correctly
  turnRobot(-0.37);
  moveRobot(-1.0);
  wait(1, seconds);
  stopRobot();
}

void pickUpBridgeGoal(){
  turnRobot(-0.32);
  moveRobot(-1.0);
  wait(1, seconds);
  stopRobot();
  moveRobot(0.5);
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
  closeClaw();
  wait(0.5, seconds);
  openClaw();
  wait(0.5, seconds);
  setRobotSpeed(30);
  moveRobot(-1.0);
  wait(1, seconds);
}


void rightAutonCode(){ 
  pickUpRightYellowGoal();
  rightSideAuton();
}

void leftAutonCode(){
  leftSideAuton(); 
}

void rightMiddleCode(){
  pickUpRightYellowGoal();
  turnRobot(0.5);
  pickUpMiddleGoal();
}

void leftMiddleCode(){
  pickUpLeftYellowGoal();
  turnRobot(-0.5);
  pickUpMiddleGoal();
}

void autonomous() {
  switch (startingArea) {
  case (rightAuton):
    rightAutonCode();
    break;
  case (leftAuton):
    leftWinPointAuton();
    break;
  case (rightMiddle):
    rightMiddleCode();
    break;
  case (leftMiddle):
    leftMiddleCode();
    break;
  }
}

void transmissionToggle() {
  if (transmissionPiston.value() == 0) {
    transmissionPiston.set(true);
  } else if (transmissionPiston.value() == 1) {
    transmissionPiston.set(false);
  }
}

void userControl() {

  digital_out clawPiston = digital_out(Brain.ThreeWirePort.B);

  leftDrive.spin(forward);
  rightDrive.spin(forward);
  leftDrive.setStopping(coast);
  rightDrive.setStopping(coast);

  armMotor.setStopping(hold);
  transmissionMotor.setStopping(hold);

  bool intake = false;

  while (true) {
    leftDrive.setVelocity(Controller1.Axis3.position(), percent);
    rightDrive.setVelocity(Controller1.Axis2.position(), percent);

    if (Controller1.ButtonR2.pressing()) {
      clawPiston.set(true);
    } else if (Controller1.ButtonR1.pressing()) {
      clawPiston.set(false);
    }

    if (Controller1.ButtonL1.pressing()) {
      armMotor.spin(forward, 100, percent);
    } else if (Controller1.ButtonL2.pressing()) {
      armMotor.spin(reverse, 100, percent);
    } else if (Controller1.ButtonL1.pressing() == false &&
               Controller1.ButtonL2.pressing() == false) {
      armMotor.stop();
    }

    if (Controller1.ButtonX.pressing()) {
      transmissionPiston.set(true);
      transmissionMotor.spin(forward, 100, percent);
    } else if (Controller1.ButtonA.pressing()) {
      transmissionPiston.set(true);
      transmissionMotor.spin(reverse, 100, percent);
    } else if(Controller1.ButtonY.pressing()){
      transmissionPiston.set(false);
    }

    else if (Controller1.ButtonUp.pressing()) {
      transmissionPiston.set(false);
      transmissionMotor.spin(forward, 100, percent);
    }

    else if (Controller1.ButtonLeft.pressing()) {
      transmissionPiston.set(false);
      transmissionMotor.spin(reverse, 100, percent);
    } else if (Controller1.ButtonRight.pressing()) {
      intake = true;
      transmissionPiston.set(false);
      transmissionMotor.spin(forward, 100, percent);
    }

    else if (Controller1.ButtonDown.pressing()) {
      intake = false;
      transmissionMotor.stop();
    }

    if (Controller1.ButtonA.pressing() == false &&
        Controller1.ButtonX.pressing() == false &&
        Controller1.ButtonLeft.pressing() == false &&
        Controller1.ButtonUp.pressing() == false &&
        Controller1.ButtonRight.pressing() == false && 
        intake == false) {
      transmissionMotor.stop();
    }
  }
}

void preAuton() { vexcodeInit(); }

int main() {
  preAuton();
  activeBrainScreen();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(userControl);
  userControl();
  while (true) {
    wait(200, msec);
  }
}
