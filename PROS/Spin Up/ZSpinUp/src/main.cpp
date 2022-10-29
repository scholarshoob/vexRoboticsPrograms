#include "main.h"
#include "api.h"
#include "display/lvgl.h"
#include "pros/adi.h"
#include "pros/misc.h"
#include "pros/motors.hpp"

using namespace pros;

Controller controller(E_CONTROLLER_MASTER);

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
  lv_label_set_text(pneumaticsLabel, "Pneumatics[3-Wire] (Sequencer, Latch) : ");
  lv_obj_align(pneumaticsLabel, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 15, 100);
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() { displayScreenText(); }

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
  static char latch = 'B';
  pros::c::adi_pin_mode(latch, OUTPUT);
  pros::c::adi_digital_write(latch, true);
}

void triggerSequencer() {
  static char sequencer = 'A';
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
void autonomous() {}

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
void opcontrol() {
  // Controller
  Controller controller(E_CONTROLLER_MASTER);

  // Left Drive
  Motor lDriveF(1);
  Motor lDriveM(2);
  Motor lDriveB(3);
  Motor_Group lDrive({lDriveF, lDriveM, lDriveB});
  lDrive.set_reversed(true);

  // Right Drive
  Motor rDriveF(8);
  Motor rDriveM(9);
  Motor rDriveB(10);
  Motor_Group rDrive({rDriveF, rDriveM, rDriveB});

  // Feature Motors
  Motor flywheel(5);
  Motor intake(6);

  // Constantly repeat controller inputs
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

    // Flywheel Control
    if (controller.get_digital(E_CONTROLLER_DIGITAL_L1)) {
      flywheel.move(127);
    } else if (controller.get_digital(E_CONTROLLER_DIGITAL_L2)) {
      flywheel.move(-127);
    } else {
      flywheel.brake();
    }

    // Activate Sequencer
    if (controller.get_digital(E_CONTROLLER_DIGITAL_X)) {
      triggerSequencer();
    }

    // Trigger End-Of-Match Release
    if (controller.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {
      triggerLatch();
    }

    delay(20);
  }
}
