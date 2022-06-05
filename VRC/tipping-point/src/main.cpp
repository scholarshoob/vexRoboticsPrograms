/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\sylar                                            */
/*    Created:      Sun Oct 03 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// armR                 motor         10              
// armL                 motor         19              
// Controller1          controller                    
// claw                 motor         9               
// rDriveB              motor         5               
// rDriveF              motor         4               
// lDriveF              motor         17              
// lDriveB              motor         18              
// intake               motor         8               
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

Mechanism RingIntake(intake);
Mechanism Claw(claw);
Mechanism ArmR(armR);
Mechanism ArmL(armL);

enum AutonPos {rightAuton = 1, leftAuton = 2, rightWinPoint = 3, leftWinPoint = 4};

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
      case(rightWinPoint):
        Brain.Screen.print("Right Side Win Point");
        break;
      case(leftWinPoint):
        Brain.Screen.print("Left Side Win Point");
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

void setRobotSpeed(int percentage){
  rDriveB.setVelocity(percentage, percent);
  rDriveF.setVelocity(percentage, percent);
  lDriveB.setVelocity(percentage, percent);
  lDriveF.setVelocity(percentage, percent);
}

void moveRobot(float rotations){
  rDriveB.spinFor(rotations, turns, false); 
  rDriveF.spinFor(rotations, turns, false);
  lDriveB.spinFor(rotations, turns, false);
  lDriveF.spinFor(rotations, turns);
  rDriveB.setStopping(brake);
  rDriveF.setStopping(brake);
  lDriveB.setStopping(brake);
  lDriveF.setStopping(brake);
  rDriveB.stop();
  rDriveF.stop();
  lDriveB.stop();
  lDriveF.stop();
  wait(0.1 ,seconds);
}

void turnRobot(float rotations){
  rDriveB.spinFor(-1.0 * rotations, turns, false); 
  rDriveF.spinFor(-1.0 * rotations, turns, false);
  lDriveB.spinFor(rotations, turns, false);
  lDriveF.spinFor(rotations, turns);
  rDriveB.setStopping(brake);
  rDriveF.setStopping(brake);
  lDriveB.setStopping(brake);
  lDriveF.setStopping(brake);
  rDriveB.stop();
  rDriveF.stop();
  lDriveB.stop();
  lDriveF.stop();
  wait(0.1 ,seconds);
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

void pickUpYellowGoalFromStart()
{
  // Move Forward
  setRobotSpeed(100);
  moveRobot(3);
  setRobotSpeed(50);
  moveRobot(0.8);
  // Close Claw
  closeClaw();
  // Back up to scoring line
  moveRobot(-2);
  // Release Goal
  openClaw();
  moveRobot(-0.35);
}

void moveGoalFromTriangle(){
  // Start after pickUpYellowGoalFromStart();
  turnRobot(0.6);
  moveRobot(1.7);
  closeClaw();
  moveRobot(-1.7);
  openClaw();
}

void pickUpCenterGoal(){
  setRobotSpeed(100);
  turnRobot(0.4);
  moveRobot(4);
  closeClaw();
  moveRobot(-4.2);
  openClaw();
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

void rightSideAuton(){
  moveGoalFromTriangle();
}

void leftSideAuton(){
  pickUpCenterGoal();
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
  claw.setVelocity(10, percent);
  claw.spinFor(reverse, 0.5, turns);
  moveRobot(-1);
}

void autonomous() {
  if(startingArea <= 2){
    pickUpYellowGoalFromStart();
    if(startingArea == rightAuton){
      rightSideAuton();
    }
    else if (startingArea == leftAuton){
      leftSideAuton();
    } 
  }
  else if(startingArea >= 3){
    if(startingArea == rightWinPoint){
      rightWinPointAuton();
    }
    else if (startingArea == leftWinPoint){
      leftWinPointAuton();
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
        lDriveF.setVelocity(10 * (leftSideSpeedOverThreasholdCounter - 1) *
                                leftSideSpeedDirection,
                            percent);
        lDriveB.setVelocity(10 * (leftSideSpeedOverThreasholdCounter - 1) *
                                leftSideSpeedDirection,
                            percent);
        leftSideSpeedOverThreasholdCounter -= 1;
      } else {
        lDriveF.setVelocity(0, percent);
        lDriveB.setVelocity(0, percent);
      }
    } else {
      // Set the speed to leftSideSpeed
      lDriveF.setVelocity(leftSideSpeed, percent);
      lDriveB.setVelocity(leftSideSpeed, percent);
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
        rDriveF.setVelocity(10 * (rightSideSpeedOverThreasholdCounter - 1) *
                                rightSideSpeedDirection,
                            percent);
        rDriveB.setVelocity(10 * (rightSideSpeedOverThreasholdCounter - 1) *
                                rightSideSpeedDirection,
                            percent);
        rightSideSpeedOverThreasholdCounter -= 1;
      } else {
        rDriveF.setVelocity(0, percent);
        rDriveB.setVelocity(0, percent);
      }
    } else {
      // Set the speed to rightSideSpeed
      rDriveF.setVelocity(rightSideSpeed, percent);
      rDriveB.setVelocity(rightSideSpeed, percent);
      rightSideSpeedOverThreashold = true;
      if (rightSideSpeed > 0) {
        rightSideSpeedDirection = 1;
      } else {
        rightSideSpeedDirection = -1;
      }
    }
    rDriveF.spin(forward);
    lDriveF.spin(forward);
    rDriveB.spin(forward);
    lDriveB.spin(forward);

    // Claw Control
    if(Controller1.ButtonR1.pressing()){
      Claw.moveMotorBackward(60);
    }
    else if(Controller1.ButtonR2.pressing()){
      Claw.moveMotorForward(60);
    }
    else{
      Claw.stopMotor();
    }

    // Arm Control
    if(Controller1.ButtonL1.pressing()){
      ArmR.moveMotorForward(100);
      ArmL.moveMotorForward(100);
    }
    else if(Controller1.ButtonL2.pressing()){
      ArmR.moveMotorBackward(100);
      ArmL.moveMotorBackward(100);
    }
    else{
      ArmR.stopMotor();
      ArmL.stopMotor();
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
    else if(Controller1.ButtonA.pressing()){
      intakeAutoOn = false;
      RingIntake.moveMotorForward(100);
    }
    else if(Controller1.ButtonB.pressing()){
      intakeAutoOn = false;
      RingIntake.moveMotorBackward(60);
    }
    else if(intakeAutoOn){
      RingIntake.moveMotorForward(100);
    }
    else if(intakeAutoOn == false){
      RingIntake.stopMotor();
    }
  }
  wait(20, msec);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  Brain.Screen.clearScreen();
  pre_auton();
  brainScreen();
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
