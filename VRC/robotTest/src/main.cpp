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
// rDriveB              motor         1               
// rDriveM              motor         2               
// Controller1          controller                    
// rDriveF              motor         3               
// lDriveF              motor         8               
// lDriveM              motor         9               
// lDriveB              motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  float moveThreshold = 3.0;
  rDriveF.setStopping(brake);
  rDriveB.setStopping(brake);
  rDriveM.setStopping(brake);

  while(true){
    float rVel = Controller1.Axis2.position();
    float lVel = Controller1.Axis3.position();
    if(rVel >= moveThreshold){
      rDriveF.setVelocity(rVel, percent);
      rDriveB.setVelocity(rVel, percent);
      rDriveM.setVelocity(rVel, percent);
    }
    else if (rVel <= -moveThreshold){
      rDriveF.setVelocity(rVel, percent);
      rDriveB.setVelocity(rVel, percent);
      rDriveM.setVelocity(rVel, percent);
    }
    else if(rVel < moveThreshold && rVel > -moveThreshold){
      rDriveF.setVelocity(0, percent);
      rDriveB.setVelocity(0, percent);
      rDriveM.setVelocity(0, percent);      
    }

    if(lVel >= moveThreshold){
      lDriveF.setVelocity(lVel, percent);
      lDriveB.setVelocity(lVel, percent);
      lDriveM.setVelocity(lVel, percent);
    }
    else if (lVel <= -moveThreshold){
      lDriveF.setVelocity(lVel, percent);
      lDriveB.setVelocity(lVel, percent);
      lDriveM.setVelocity(lVel, percent);
    }
    else if(lVel < moveThreshold && lVel > -moveThreshold){
      lDriveF.setVelocity(0, percent);
      lDriveB.setVelocity(0, percent);
      lDriveM.setVelocity(0, percent);      
    }
    rDriveF.spin(forward);
    rDriveB.spin(forward);
    rDriveM.spin(forward);

    lDriveF.spin(forward);
    lDriveB.spin(forward);
    lDriveM.spin(forward);
  }
}
