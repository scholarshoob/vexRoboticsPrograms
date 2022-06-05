/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\sylar                                            */
/*    Created:      Sat Dec 18 2021                                           */
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
using namespace vex;

competition Competition;

void userControl() {
  digital_out dig1 = digital_out(Brain.ThreeWirePort.A);
  motor_group(leftDriveFront, leftDriveMiddle, leftDriveBack).spin(forward);
  motor_group(rightDriveFront, rightDriveMiddle, rightDriveBack).spin(forward);
  while (true) {

    motor_group(leftDriveFront, leftDriveMiddle, leftDriveBack)
        .setVelocity(Controller1.Axis3.position(), percent);
    motor_group(rightDriveFront, rightDriveMiddle, rightDriveBack)
        .setVelocity(Controller1.Axis2.position(), percent);

    if (Controller1.ButtonL1.pressing()) {
      armMotor.spin(forward, 100, percent);
    } else if (Controller1.ButtonL2.pressing()) {
      armMotor.spin(reverse, 100, percent);
    } else if (Controller1.ButtonL2.pressing() == false &&
               Controller1.ButtonL1.pressing() == false) {
      armMotor.setStopping(hold);
      armMotor.stop();
    }

    if (Controller1.ButtonR1.pressing()) {
      clawMotor.spin(forward, 100, percent);
    } else if (Controller1.ButtonR2.pressing()) {
      clawMotor.spin(reverse, 100, percent);
    } else if (Controller1.ButtonR2.pressing() == false &&
               Controller1.ButtonR1.pressing() == false) {
      clawMotor.setStopping(hold);
      clawMotor.stop();
    }
  }
}
void auton() {
  motor_group leftside =
      motor_group(leftDriveFront, leftDriveMiddle, leftDriveBack);
  motor_group rightside =
      motor_group(rightDriveFront, rightDriveMiddle, rightDriveBack);
  leftside.setVelocity(100, percent);
  rightside.setVelocity(100, percent);
  armMotor.spin(reverse, 100, percent);
  wait(0.7, seconds);
  armMotor.setStopping(hold);
  armMotor.stop();
  leftside.spinFor(2.1, turns, false);
  rightside.spinFor(2.1, turns, true);
  clawMotor.spin(reverse, 100, percent);
  wait(0.7, seconds);
  clawMotor.setStopping(hold);
  clawMotor.stop();
  rightside.spinFor(-2, turns, false);
  leftside.spinFor(-2, turns, true);
  clawMotor.spin(forward);
  wait(0.7, seconds);
  clawMotor.spin(reverse);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.drivercontrol(userControl);
  Competition.autonomous(auton);

  while (true) {
    wait(100, msec);
  }
}
