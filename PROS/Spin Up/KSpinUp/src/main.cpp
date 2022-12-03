#include "main.h"
#include "api.h"
#include "display/lvgl.h"
#include "pros/adi.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include <cmath>

using namespace pros;

Controller controller(E_CONTROLLER_MASTER);

// Left Drive
Motor lDriveF(1);
Motor lDriveM(2);
Motor lDriveB(3);
Motor_Group lDrive({lDriveF, lDriveM, lDriveB});

// Right Drive
Motor rDriveF(8);
Motor rDriveM(9);
Motor rDriveB(10);
Motor_Group rDrive({rDriveF, rDriveM, rDriveB});
Motor flywheel(5);
Motor intake(6);

void displayScreenText() {
  lv_obj_clean(lv_scr_act());

  // Port Labels
  lv_obj_t *leftDrivePortLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(leftDrivePortLabel, "| 1 | 2 | 3 |");
  lv_obj_align(leftDrivePortLabel, lv_scr_act(), LV_ALIGN_IN_RIGHT_MID, -20,
               -100);

  lv_obj_t *rightDrivePortLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(rightDrivePortLabel, "| 8 | 9 | 10 |");
  lv_obj_align(rightDrivePortLabel, lv_scr_act(), LV_ALIGN_IN_RIGHT_MID, -20,
               -50);

  lv_obj_t *flywheelPortLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(flywheelPortLabel, "| 5 |");
  lv_obj_align(flywheelPortLabel, lv_scr_act(), LV_ALIGN_IN_RIGHT_MID, -20, 0);

  lv_obj_t *intakePortLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(intakePortLabel, "| 6 |");
  lv_obj_align(intakePortLabel, lv_scr_act(), LV_ALIGN_IN_RIGHT_MID, -20, 50);

  lv_obj_t *pneumaticsPortLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(pneumaticsPortLabel, "| A | B |");
  lv_obj_align(pneumaticsPortLabel, lv_scr_act(), LV_ALIGN_IN_RIGHT_MID, -20,
               100);

  // Port Labels
  lv_obj_t *leftDriveLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(leftDriveLabel, "Left Drive (F, M, B) : ");
  lv_obj_align(leftDriveLabel, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 15, -100);

  lv_obj_t *rightDriveLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(rightDriveLabel, "Right Drive (F, M, B) : ");
  lv_obj_align(rightDriveLabel, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 15, -50);

  lv_obj_t *flywheelLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(flywheelLabel, "Flywheel: ");
  lv_obj_align(flywheelLabel, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 15, 0);

  lv_obj_t *intakeLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(intakeLabel, "Intake: ");
  lv_obj_align(intakeLabel, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 15, 50);

  lv_obj_t *pneumaticsLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(pneumaticsLabel,
                    "Pneumatics[3-Wire] (Sequencer, Latch) : ");
  lv_obj_align(pneumaticsLabel, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 15, 100);
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  lDrive.set_brake_modes(E_MOTOR_BRAKE_COAST);
  rDrive.set_brake_modes(E_MOTOR_BRAKE_COAST);
  flywheel.set_brake_mode(E_MOTOR_BRAKE_COAST);
  lDrive.set_reversed(true);
  flywheel.set_reversed(true);
  displayScreenText();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous
 * selector on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

void triggerLatch() {
  static char latch = 'G';
  pros::c::adi_pin_mode(latch, OUTPUT);
  pros::c::adi_digital_write(latch, true);
}

void triggerSequencer() {
  static char sequencer = 'H';
  pros::c::adi_pin_mode(sequencer, OUTPUT);
  pros::c::adi_digital_write(sequencer, true);
  delay(100);
  pros::c::adi_digital_write(sequencer, false);
}
/**
 * Runs the user autonomous code. This function will be started in its own
 * task with the default priority and stack size whenever the robot is enabled
 * via the Field Management System or the VEX Competition Switch in the
 * autonomous mode. Alternatively, this function may be called in initialize
 * or opcontrol for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start
 * it from where it left off.
 */

uint32_t getMsForRotations(motor_gearset_e gearSet, float rotations) {
  int rpm = 100;
  if (gearSet == E_MOTOR_GEARSET_36) {
    rpm = 100;
  } else if (gearSet == E_MOTOR_GEARSET_18) {
    rpm = 200;
  } else if (gearSet == E_MOTOR_GEARSET_06) {
    rpm = 600;
  }
  float rps = rpm / 60;
  float rpms = rps / 1000;
  return (rotations / rpms);
}

void robot(char operation, float rotations) {
  switch (operation) {
  case 'm':
    if (rotations > 0) {
      rDrive.move(127);
      lDrive.move(127);
    } else if (rotations < 0) {
      rDrive.move(-127);
      lDrive.move(-127);
    }
    break;
  case 't':
    if (rotations > 0) {
      rDrive.move(-127);
      lDrive.move(127);
    } else if (rotations < 0) {
      rDrive.move(127);
      lDrive.move(-127);
    }
    break;
  case 'r':
    if (rotations > 0) {
      rDrive.move(127);
    } else {
      rDrive.move(-127);
    }
    break;
  case 'l':
    if (rotations > 0) {
      lDrive.move(127);
    } else {
      lDrive.move(-127);
    }
    break;
  }
  delay(getMsForRotations(E_MOTOR_GEARSET_06, std::abs(rotations)));
  if (operation == 'l') {
    lDrive.brake();
  } else if (operation == 'r') {
    rDrive.brake();
  } else {
    rDrive.brake();
    lDrive.brake();
  }
  delay(500);
}

void autonomous() {
  flywheel.move(127);
  delay(3000);
  triggerSequencer();
  delay(1500);
  triggerSequencer();
  delay(500);
  flywheel.brake();

  robot('m', 2.5);
  robot('t', 1.6);
  robot('m', -3.7);
  lDrive.move(-127);
  delay(2000);
  lDrive.brake();
  intake.move(-127);
  delay(700);
  intake.brake();
  robot('m', 0.5);
}

/**
 * Runs the operator control code. This function will be started in its own
 * task with the default priority and stack size whenever the robot is enabled
 * via the Field Management System or the VEX Competition Switch in the
 * operator control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart
 * the task, not resume it from where it left off.
 */

void runFlywheel(void *param) {
  bool flywheelOn = false;
  int flywheelVolts[2] = {127, 96};
  int flywheelSpeedSelector = 0;
  while (true) {
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT)) {
      if (flywheelSpeedSelector == 0) {
        flywheelSpeedSelector = 1;
      } else {
        flywheelSpeedSelector--;
      }
    } else if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)) {
      if (flywheelSpeedSelector == 1) {
        flywheelSpeedSelector = 0;
      } else {
        flywheelSpeedSelector++;
      }
    }
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)) {
      flywheelOn = !flywheelOn;
    }
    if (controller.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {
      flywheelOn = false;
      flywheel.move(-127);
    }
    // Emergency Flywheel Reverse

    if (flywheelOn == true) {
      flywheel.move(flywheelVolts[flywheelSpeedSelector]);

    } else if (flywheelOn == false &&
               controller.get_digital(E_CONTROLLER_DIGITAL_DOWN) == false) {
      flywheel.brake();
    }
    delay(20);
  }
}

void opcontrol() {
  task_t flywheelTask =
      c::task_create(runFlywheel, (void *)"PROS", TASK_PRIORITY_DEFAULT,
                     TASK_STACK_DEPTH_DEFAULT, "RunFlywheel");
  while (true) {
    // Drive Control
    lDrive.move(controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
    rDrive.move(controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));

    // Intake Control
    if (controller.get_digital(E_CONTROLLER_DIGITAL_R1)) {
      intake.move(127);
    } else if (controller.get_digital(E_CONTROLLER_DIGITAL_R2)) {
      intake.move(-127);
    } else {
      intake.brake();
    }
    // Activate Sequencer
    if (controller.get_digital(E_CONTROLLER_DIGITAL_L2)) {
      triggerSequencer();
      delay(200);
    }

    // Trigger End-Of-Match Release
    if (controller.get_digital(E_CONTROLLER_DIGITAL_Y)) {
      triggerLatch();
    }

    delay(20);
  }
}
