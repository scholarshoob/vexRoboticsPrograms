#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// armMotor             motor         8               
// leftDriveFront       motor         1               
// leftDriveMiddle      motor         2               
// leftDriveBack        motor         3               
// rightDriveFront      motor         11              
// rightDriveMiddle     motor         12              
// rightDriveBack       motor         13              
// Controller1          controller                    
// clawMotor            motor         4               
// visionSensor         vision        10              
// inertialSensor       inertial      14              
// ---- END VEXCODE CONFIGURED DEVICES ----
using namespace vex;


// -0.5 : 0.5 = perfect right turn
competition Competition;

int startingArea = 1;
enum autonPos {rightWinPoint = 1, leftCombo = 2, leftMiddleGoal = 3, leftBridge = 4};

void cycleF(){
  if(startingArea == 4){
    startingArea = 1;
  }
  else{
    startingArea += 1;
  }
}

void cycleB(){
  if(startingArea == 1){
    startingArea = 4;
  }
  else{
    startingArea -= 1;
  }
}

void setRobotVelocity(int speed){
  motor_group leftside =
      motor_group(leftDriveFront, leftDriveMiddle, leftDriveBack);
  motor_group rightside =
      motor_group(rightDriveFront, rightDriveMiddle, rightDriveBack);
  leftside.setVelocity(speed, percent);
  rightside.setVelocity(speed, percent);
}

void turnRobot(float rotations){
  motor_group leftside =
      motor_group(leftDriveFront, leftDriveMiddle, leftDriveBack);
  motor_group rightside =
      motor_group(rightDriveFront, rightDriveMiddle, rightDriveBack);
  leftside.spinFor(rotations, turns, false);
  rightside.spinFor(-rotations, turns, true);
}

void moveRobot(float rotations){
  motor_group leftside =
      motor_group(leftDriveFront, leftDriveMiddle, leftDriveBack);
  motor_group rightside =
      motor_group(rightDriveFront, rightDriveMiddle, rightDriveBack);
  leftside.spinFor(rotations, turns, false);
  rightside.spinFor(rotations, turns, true);
}

void stopRobot(){
  motor_group leftside =
      motor_group(leftDriveFront, leftDriveMiddle, leftDriveBack);
  motor_group rightside =
      motor_group(rightDriveFront, rightDriveMiddle, rightDriveBack);
  leftside.stop();
  rightside.stop();
}

void brainScreen(){
  while(true){
    Controller1.ButtonA.pressed(cycleF);
    Controller1.ButtonY.pressed(cycleB);
    Brain.Screen.clearLine();
    switch(startingArea){
      case(rightWinPoint):
        Brain.Screen.print("Right Side Win Point");
        break;
      case(leftCombo):
        Brain.Screen.print("Left Side Combo");
        break;
      case(leftMiddleGoal):
        Brain.Screen.print("Left Side Middle Goal");
        break;
      case(leftBridge):
        Brain.Screen.print("Left Side Bridge");
        break;
      default:
        break;
    }
    if(Controller1.ButtonX.pressing()){
      Brain.Screen.newLine();
      Brain.Screen.print("Selected!");
      break;
    }
  }
}

void detectGrabYellowGoal(){
  int VISION_SENSOR_X_MIDDLE = 158;
  int OFFSET_BUFFER = 20;

  motor_group leftside =
      motor_group(leftDriveFront, leftDriveMiddle, leftDriveBack);
  motor_group rightside =
      motor_group(rightDriveFront, rightDriveMiddle, rightDriveBack);

  leftside.setStopping(hold);
  rightside.setStopping(hold);
  setRobotVelocity(10);
  while(true){
    visionSensor.takeSnapshot(visionSensor__YELLOW_GOAL);
    if(visionSensor.largestObject.centerX > VISION_SENSOR_X_MIDDLE - OFFSET_BUFFER &&
        visionSensor.largestObject.centerX < VISION_SENSOR_X_MIDDLE + OFFSET_BUFFER &&
         visionSensor.largestObject.centerY >= 86){
      stopRobot();
      clawMotor.setVelocity(100, percent);
      clawMotor.spinFor(reverse, 1, seconds);
      break;     
    }
    if(visionSensor.largestObject.centerX < VISION_SENSOR_X_MIDDLE){
      turnRobot(-0.03);
    }
    else if(visionSensor.largestObject.centerX > VISION_SENSOR_X_MIDDLE){
      turnRobot(0.03);
    } 
    if(visionSensor.largestObject.centerY < 86){
      moveRobot(-0.2);
    }
  }
}


void climbBridgeBackwards(){
  motor_group leftside =
      motor_group(leftDriveFront, leftDriveMiddle, leftDriveBack);
  motor_group rightside =
      motor_group(rightDriveFront, rightDriveMiddle, rightDriveBack);
  leftside.setStopping(hold);
  rightside.setStopping(hold);
  setRobotVelocity(7);
  while(true){
    if (inertialSensor.orientation(roll, deg) > -5.0 && inertialSensor.orientation(roll, deg) < -2.0){
      leftside.stop();
      rightside.stop();
      wait(1, seconds);
      setRobotVelocity(7);
      moveRobot(0.5);
      break;
    }
    else if(inertialSensor.orientation(roll, deg) < -20.0){
      leftside.spin(vex::directionType::rev);
      rightside.spin(vex::directionType::rev);
    }
    else if(inertialSensor.orientation(roll, deg) > 10){
      leftside.spin(vex::directionType::fwd);
      rightside.spin(vex::directionType::fwd);
    }
  }
}

void climbBridge1Way(){
  motor_group leftside =
      motor_group(leftDriveFront, leftDriveMiddle, leftDriveBack);
  motor_group rightside =
      motor_group(rightDriveFront, rightDriveMiddle, rightDriveBack);
  leftside.setStopping(hold);
  rightside.setStopping(hold);
  setRobotVelocity(10);
  while(true){
    if(inertialSensor.orientation(roll, deg) > -22 && inertialSensor.orientation(roll, deg) < 0){
      break;
    }
    moveRobot(-0.1);
    wait(0.8, sec);
  }
}

void correctBridge(){
  motor_group leftside =
      motor_group(leftDriveFront, leftDriveMiddle, leftDriveBack);
  motor_group rightside =
      motor_group(rightDriveFront, rightDriveMiddle, rightDriveBack);
  leftside.setStopping(hold);
  rightside.setStopping(hold);
  setRobotVelocity(10);
  while(true){
    if(inertialSensor.orientation(roll, deg) > -3){
      moveRobot(0.1);
    }
    else if(inertialSensor.orientation(roll, deg) < -5){
      moveRobot(-0.1);
    }
    else{
      break;
    }
    wait(0.8, sec);
  }
}

void rightWinPointAuton(){
  setRobotVelocity(15);
  moveRobot(-1.2);

  clawMotor.setVelocity(50, percent);
  clawMotor.spinFor(-0.4, turns, true);
  wait(0.8, seconds);
  clawMotor.setVelocity(100, percent);
  clawMotor.spinFor(reverse, 1, seconds);
  wait(0.3, seconds);
  setRobotVelocity(75);
  moveRobot(1);
  turnRobot(0.5);
  clawMotor.spinFor(forward, 1, seconds);
  turnRobot(-0.74);
  moveRobot(-1.85);
  detectGrabYellowGoal();
  setRobotVelocity(100);
  moveRobot(2.4);
}

void leftComboAuton(){
  setRobotVelocity(75);
  moveRobot(-1.98);
  detectGrabYellowGoal();
  setRobotVelocity(75);
  moveRobot(1.5);
  turnRobot(0.5);
  clawMotor.setVelocity(100, percent);
  clawMotor.spinFor(forward, 1, seconds);
  wait(0.2, seconds);
  setRobotVelocity(75);
  turnRobot(-0.75);
  moveRobot(-2.5);
  detectGrabYellowGoal();
  setRobotVelocity(75);
  moveRobot(2);
  setRobotVelocity(100);
}

void leftMiddleGoalAuton(){
  // Drop ring in red mobile goal
  clawMotor.setVelocity(50, percent);
  clawMotor.spinFor(-0.4, turns, true);
  wait(0.8, seconds);
  
  // Turn to face yellow mobile goal
  setRobotVelocity(50);
  moveRobot(0.3);
  wait(0.7, seconds);
  turnRobot(-0.21);

  // Back up to reach yellow mobile goal
  setRobotVelocity(100);
  moveRobot(-2.8);

  // Grab goal
  detectGrabYellowGoal();

  // Move forward to drag mobile goal back into home zone
  setRobotVelocity(100);
  moveRobot(3);
}

void leftBridgeAuton(){
  // Drop ring in red mobile goal
  clawMotor.setVelocity(50, percent);
  clawMotor.spinFor(-0.4, turns, true);
  wait(0.8, seconds);
  clawMotor.setVelocity(100, percent);
  clawMotor.spinFor(reverse, 0.5, seconds);
  setRobotVelocity(100);
  moveRobot(-2.25);
  climbBridge1Way();
  wait(0.3, seconds);
  correctBridge();
  wait(0.3, seconds);
  clawMotor.spinFor(forward, 0.5, seconds);
}

void autonomous(){
  motor_group leftside =
      motor_group(leftDriveFront, leftDriveMiddle, leftDriveBack);
  motor_group rightside =
      motor_group(rightDriveFront, rightDriveMiddle, rightDriveBack);

  clawMotor.setStopping(hold);

  switch(startingArea){
    case(rightWinPoint):
      rightWinPointAuton();
      break;
    case(leftCombo):
      leftComboAuton();
      break;
    case(leftMiddleGoal):
      leftMiddleGoalAuton();
      break;
    case(leftBridge):
      leftBridgeAuton();
      break;
    default:
      break;
  }
}


void userControl(){
  digital_out dig1 = digital_out(Brain.ThreeWirePort.G);
  motor_group(leftDriveFront, leftDriveMiddle, leftDriveBack).spin(forward);
  motor_group(rightDriveFront, rightDriveMiddle, rightDriveBack).spin(forward);
  motor_group(leftDriveFront, leftDriveMiddle, leftDriveBack).setStopping(coast);
  motor_group(rightDriveFront, rightDriveMiddle, rightDriveBack).setStopping(coast);

  while(true){

    bool holdBaseMotors = false;

    

    if(Controller1.ButtonR2.pressing()){
      dig1.set(true);
    }
    else if(Controller1.ButtonR1.pressing()){
      dig1.set(false);
    }

    if(Controller1.ButtonUp.pressing()){
      armMotor.spin(forward, 100, percent);
    }
    else if(Controller1.ButtonDown.pressing()){
      armMotor.spin(reverse, 100, percent);
    }
    else if(Controller1.ButtonUp.pressing() == false && Controller1.ButtonDown.pressing() == false){
      armMotor.setStopping(hold);
      armMotor.stop();
    }
    if(Controller1.ButtonL1.pressing()){
      clawMotor.spin(forward, 100, percent);
    }
    else if(Controller1.ButtonL2.pressing()){
      clawMotor.spin(reverse, 100, percent);
    }
    else if(Controller1.ButtonL1.pressing() == false && Controller1.ButtonL2.pressing() == false){
      clawMotor.setStopping(hold);
      clawMotor.stop();
    }

    if(Controller1.ButtonLeft.pressing() == true){
      holdBaseMotors = true;
    }

    if(holdBaseMotors == true){
      motor_group(leftDriveFront, leftDriveMiddle, leftDriveBack).setStopping(hold);
      motor_group(rightDriveFront, rightDriveMiddle, rightDriveBack).setStopping(hold);
    }
    else{
      motor_group(leftDriveFront, leftDriveMiddle, leftDriveBack).setStopping(coast);
      motor_group(rightDriveFront, rightDriveMiddle, rightDriveBack).setStopping(coast);
    }

  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  inertialSensor.calibrate();
  // waits for Inertial Sensor to calibrate 
  while (inertialSensor.isCalibrating()) {
    wait(100, msec);
  }
  brainScreen();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(userControl);
  while(true){
    wait(100, msec);
  }
}