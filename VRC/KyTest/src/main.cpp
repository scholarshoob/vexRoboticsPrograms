/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\sylar                                            */
/*    Created:      Mon Nov 08 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// rDriveF              motor         1               
// rDriveM              motor         2               
// rDriveB              motor         3               
// lDriveF              motor         11              
// lDriveM              motor         12              
// lDriveB              motor         13              
// Controller1          controller                    
// armMotor             motor         20              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "vex_motorgroup.h"
using namespace vex;

competition Competition;

class Mechanism{ 
  public:
    motor_group mechanismMotor;

    Mechanism(){}

    Mechanism(motor_group mg){
      mechanismMotor = mg;
      mechanismMotor.setVelocity(100, percent);
    }
    void spinMotor(int speed){
      mechanismMotor.spin(forward, speed, percent);
    }

    void stopMotor(){
      mechanismMotor.setStopping(hold);
      mechanismMotor.stop();
    }

    void bindToControllerButton(controller::button controllerButtonPositive, controller::button controllerButtonNegative, int speed){
      if(controllerButtonPositive.pressing() == true){
        spinMotor(speed);
      }
      if(controllerButtonNegative.pressing() == true){
        spinMotor(-speed);
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

    Drivetrain(){}
    
    Drivetrain(motor_group lmg, motor_group rmg){
      leftSideMotors = lmg;
      rightSideMotors = rmg;
    }

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

class Program{
  digital_out dig1 = digital_out(Brain.ThreeWirePort.A);
  public:
    Drivetrain drivebase;
    Mechanism arm;
    
    Program(){
      drivebase = Drivetrain(
      (motor_group(lDriveF, lDriveM, lDriveB)),
      (motor_group(rDriveF, rDriveM, rDriveB))
      );  
      arm = Mechanism((motor_group(armMotor)));
    }
  void auton(){
    return;
  }

  void userControl(){
    drivebase.rightSideMotors.spin(forward);
    drivebase.leftSideMotors.spin(forward);
    while(true){
      int rightControllerAxis = Controller1.Axis2.position();
      int leftControllerAxis = Controller1.Axis3.position();
      int threshold = 3;
      arm.bindToControllerButton(Controller1.ButtonL1, Controller1.ButtonL2, 100);
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
      if(Controller1.ButtonR1.pressing()){
        dig1.set(true);
      }
      else if(Controller1.ButtonR2.pressing()){
        dig1.set(false);
      }
    }
      wait(100, msec);
  }
};

void vexDumAuton(){
  Program programAuton;
  programAuton.auton();
}

void vexDumUserControl(){
  Program programUserControl;
  programUserControl.userControl();
}

int main(){
  vexcodeInit();
  Program program;
  program.userControl();
  Competition.autonomous(vexDumAuton);
  Competition.drivercontrol(vexDumUserControl);
  while(true){
    program.userControl();
    wait(100, msec);
  }
}
