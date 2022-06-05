/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\sylar                                            */
/*    Created:      Sun Nov 14 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// arm1                 motor         1               
// claw                 motor         2               
// intake               motor         3               
// arm2                 motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void moveArmRUp(){
  arm1.spin(forward);
}

void moveArmRDown(){
  arm1.spin(reverse);
}

void stopArmR(){
  arm1.setStopping(hold);
  arm1.stop();
}

void setArmRSpeed(int pct){
  arm1.setVelocity(pct, percent);
}

void moveArmLUp(){
  arm2.spin(forward);
}

void moveArmLDown(){
  arm2.spin(reverse);
}

void stopArmL(){
  arm2.setStopping(hold);
  arm2.stop();
}

void setArmLSpeed(int pct){
  arm2.setVelocity(pct, percent);
}

void moveClawUp(){
  claw.spin(forward);
}

void moveClawDown(){
  claw.spin(reverse);
}

void stopClaw(){
  claw.setStopping(hold);
  claw.stop();
}

void setClawSpeed(int pct){
  claw.setVelocity(pct, percent);
}

void moveIntakeIn(){
  intake.spin(forward);
}

void moveIntakeOut(){
  intake.spin(reverse);
}

void stopIntake(){
  intake.setStopping(hold);
  intake.stop();
}

void setIntakeSpeed(int pct){
  intake.setVelocity(pct, percent);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
}
