/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\sylar                                            */
/*    Created:      Mon Feb 28 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// rightFlywheel        motor         1               
// leftFlywheel         motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while(true){
    if(Controller1.ButtonR1.pressing()){
      rightFlywheel.setVelocity(100, percent);
      leftFlywheel.setVelocity(100, percent);
      rightFlywheel.spin(forward);
      leftFlywheel.spin(forward);
    }
    else{
      rightFlywheel.stop();      
      leftFlywheel.stop();
    }
  }
}
