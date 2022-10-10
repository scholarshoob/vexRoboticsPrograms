#include "main.h"
#include "api.h"
#include "display/lv_core/lv_obj.h"
#include "display/lv_themes/lv_theme.h"
#include "display/lv_themes/lv_theme_night.h"
#include "display/lvgl.h"
#include "pros/apix.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "robotConfig.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sys/_stdint.h>
#include <vector>

using namespace pros;

std::vector<int8_t> leftDrivePorts{1, 2, 3};
std::vector<int8_t> rightDrivePorts{8, 9, 10};
int flywheelPort = 4;
int intakePort = 5;

Controller controller(E_CONTROLLER_MASTER);

Motor *leftFrontMotor = nullptr;
Motor *leftMiddleMotor = nullptr;
Motor *leftBackMotor = nullptr;
Motor_Group *leftDrive = nullptr;

Motor *rightFrontMotor = nullptr;
Motor *rightMiddleMotor = nullptr;
Motor *rightBackMotor = nullptr;
Motor_Group *rightDrive = nullptr;

Motor *flywheelMotor = nullptr;
Motor *intakeMotor = nullptr;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void setMotorPort(Motor *&motor, int port) {
  if (motor) {
    delete motor;
  }
  motor = new Motor(port);
}

void setMotorGroupPort(Motor_Group *&motor_group, std::vector<int8_t> ports) {
  if (motor_group) {
    delete motor_group;
  }
  motor_group = new Motor_Group(ports);
}

void init() {

  lv_obj_clean(lv_scr_act());

  // Title Page
  lv_obj_t *titleLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(titleLabel, "Port Mappings");
  lv_obj_align(titleLabel, lv_scr_act(), LV_ALIGN_IN_TOP_MID, 0, 10);

  // Port Labels
  lv_obj_t *leftDrivePortLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(leftDrivePortLabel, "| 1 | 2 | 3 |");
  lv_obj_align(leftDrivePortLabel, lv_scr_act(), LV_ALIGN_IN_RIGHT_MID, -20,
               -50);

  lv_obj_t *rightDrivePortLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(rightDrivePortLabel, "| 8 | 9 | 10 |");
  lv_obj_align(rightDrivePortLabel, lv_scr_act(), LV_ALIGN_IN_RIGHT_MID, -20,
               0);

  lv_obj_t *flywheelPortLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(flywheelPortLabel, "| 5 |");
  lv_obj_align(flywheelPortLabel, lv_scr_act(), LV_ALIGN_IN_RIGHT_MID, -20, 50);

  lv_obj_t *intakePortLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(intakePortLabel, "| 6 |");
  lv_obj_align(intakePortLabel, lv_scr_act(), LV_ALIGN_IN_RIGHT_MID, -20, 100);

  // Port Labels
  lv_obj_t *leftDriveLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(leftDriveLabel, "Left Drive: ");
  lv_obj_align(leftDriveLabel, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 15, -50);

  lv_obj_t *rightDriveLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(rightDriveLabel, "Right Drive: ");
  lv_obj_align(rightDriveLabel, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 15, 0);

  lv_obj_t *flywheelLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(flywheelLabel, "Flywheel: ");
  lv_obj_align(flywheelLabel, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 15, 50);

  lv_obj_t *intakeLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(intakeLabel, "Intake: ");
  lv_obj_align(intakeLabel, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 15, 100);
}

void initialize() {
  init();

  setMotorGroupPort(leftDrive, leftDrivePorts);
  leftDrive->set_brake_modes(E_MOTOR_BRAKE_HOLD);

  setMotorGroupPort(rightDrive, rightDrivePorts);
  rightDrive->set_brake_modes(E_MOTOR_BRAKE_HOLD);

  setMotorPort(flywheelMotor, 5);
  flywheelMotor->set_brake_mode(E_MOTOR_BRAKE_COAST);

  setMotorPort(intakeMotor, 6);
  intakeMotor->set_brake_mode(E_MOTOR_BRAKE_HOLD);
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
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // Constantly repeat controller inputs
  while (true) {

    // Drive Control
    leftDrive->move(controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
    rightDrive->move(controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));

    // Intake Control
    if (controller.get_digital(E_CONTROLLER_DIGITAL_R1)) {
      intakeMotor->move(127);
    } else if (controller.get_digital(E_CONTROLLER_DIGITAL_R2)) {
      intakeMotor->move(-127);
    } else {
      intakeMotor->brake();
    }

    // Flywheel Control
    if (controller.get_digital(E_CONTROLLER_DIGITAL_L1)) {
      flywheelMotor->move(127);
    } else if (controller.get_digital(E_CONTROLLER_DIGITAL_L2)) {
      flywheelMotor->move(-127);
    } else {
      flywheelMotor->brake();
    }
    delay(20);
  }
}
