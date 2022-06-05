/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\sylar                                            */
/*    Created:      Wed Dec 15 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// leftDriveFront       motor         11              
// leftDriveMiddle      motor         9               
// leftDriveBack        motor         8               
// armMotor             motor         2               
// clawMotor            motor         3               
// rightDriveBack       motor         19              
// rightDriveMiddle     motor         10              
// rightDriveFront      motor         20              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "vex_motorgroup.h"
using namespace vex;

competition Competition;

class Mechanism{ 
  public:
    motor_group mechanismMotor;
    Mechanism(motor_group mg){
      mechanismMotor = mg;
    }
    void initialize(){
      mechanismMotor.setVelocity(100, percent);
    }
    void moveMotorForward(int speed){
      mechanismMotor.spin(forward, speed, percent);
    }

    void moveMotorBackward(int speed){
      mechanismMotor.spin(reverse, speed, percent);
    }

    void stopMotor(){
      mechanismMotor.setStopping(hold);
      mechanismMotor.stop();
    }

    void bindToControllerButton(controller::button controllerButtonPositive, controller::button controllerButtonNegative, int speed){
      if(controllerButtonPositive.pressing() == true){
        moveMotorForward(speed);
      }
      if(controllerButtonNegative.pressing() == true){
        moveMotorBackward(speed);
      }
      else if(controllerButtonPositive.pressing() == false && controllerButtonNegative.pressing() == false){
        stopMotor();
      }
    }
};


class Drivetrain{
  public:
    motor_group leftSideMotors;
    motor_group rightSideMotors;

    Drivetrain(motor_group lmg, motor_group rmg){
      leftSideMotors = lmg;
      rightSideMotors = rmg;
    }

    float rightSideSpeed;
    float leftSideSpeed;
    
    void setRightSideSpeed(int speed){
      rightSideMotors.setVelocity(speed, percent);
    }

    void setLeftSideSpeed(int speed){
      leftSideMotors.setVelocity(speed, percent);
    }

    void setRobotSpeed(int speed){
      leftSideMotors.setVelocity(speed, percent);
      rightSideMotors.setVelocity(speed, percent);
    }

    void moveRobot(int rotations){
      rightSideMotors.spinFor(rotations, turns, false);
      leftSideMotors.spinFor(rotations, turns);
    }

    void turnRobot(int rotations){
      // Positive = right, negative = left
      rightSideMotors.spinFor(-rotations, turns, false);
      leftSideMotors.spinFor(rotations, turns);
    }

    void gradualMoveToTargetSpeed(motor_group motors, int speed){
      int currentVel = motors.velocity(percent);
      int midpoint = (currentVel - speed) / 2;
      if(abs(midpoint) < 2){
        motors.setVelocity(-speed, percent);
      }
      else{
        motors.setVelocity(-midpoint, percent);
      }
    }
};

void auton(){
  return;
}

void userControl(){
  Drivetrain drivebase(
                    (motor_group(leftDriveFront, leftDriveMiddle, leftDriveBack)),
                    (motor_group(rightDriveFront, rightDriveMiddle, rightDriveBack))
                    );
  Mechanism claw((motor_group(clawMotor)));  
  Mechanism arm((motor_group(armMotor)));

  drivebase.rightSideMotors.spin(forward);
  drivebase.leftSideMotors.spin(forward);

  while(true){
    int rightControllerAxis = Controller1.Axis2.position();
    int leftControllerAxis = Controller1.Axis3.position();
    int threshold = 3;
    
    claw.bindToControllerButton(Controller1.ButtonL1, Controller1.ButtonL2, 50);
    arm.bindToControllerButton(Controller1.ButtonR1, Controller1.ButtonR2, 100);
    
    if(abs(rightControllerAxis) >= threshold){
      drivebase.gradualMoveToTargetSpeed(drivebase.rightSideMotors, rightControllerAxis);
    }
    else{
      drivebase.setRightSideSpeed(0);
    }
    if(abs(leftControllerAxis) >= threshold){
      drivebase.gradualMoveToTargetSpeed(drivebase.leftSideMotors, leftControllerAxis);
    }
    else{
      drivebase.setLeftSideSpeed(0);
    }
    wait(100, msec);
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  userControl();
  Competition.autonomous(auton);
  Competition.drivercontrol(userControl);
  while(true){
    wait(100, msec);
  }
  /*
  while(true){
    int rightControllerAxis = Controller1.Axis2.position();
    int leftControllerAxis = Controller1.Axis3.position();
    int threshold = 0;
    
    claw.bindToControllerButton(Controller1.ButtonL1, Controller1.ButtonL2, 50);
    arm.bindToControllerButton(Controller1.ButtonR1, Controller1.ButtonR2, 100);

    if(abs(rightControllerAxis) >= threshold){
      gradualMoveToTargetSpeed(drivebase.rightSideMotors, rightControllerAxis);
    }
    if(abs(leftControllerAxis) >= threshold){
      gradualMoveToTargetSpeed(drivebase.leftSideMotors, leftControllerAxis);
    }
    wait(100, msec);
  }
  */
}
