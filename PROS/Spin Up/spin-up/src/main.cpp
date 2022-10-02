#include "main.h"
#include "api.h"
#include <string>
#include <sys/_stdint.h>
#include <vector>
#include "pros/misc.h"
#include "pros/motors.hpp"
#include "robotConfig.h"

using namespace pros;

std::vector<int8_t> leftDrivePorts {1, 2, 3};
std::vector<int8_t> rightDrivePorts {8, 9, 10};
int flywheelPort = 4;
int intakePort = 5;

Controller controller (E_CONTROLLER_MASTER);


Motor* leftFrontMotor = nullptr;
Motor* leftMiddleMotor = nullptr;
Motor* leftBackMotor = nullptr;
Motor_Group* leftDrive = nullptr;

Motor* rightFrontMotor = nullptr;
Motor* rightMiddleMotor = nullptr;
Motor* rightBackMotor = nullptr;
Motor_Group* rightDrive = nullptr;

Motor* flywheelMotor = nullptr;
Motor* intakeMotor = nullptr;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

std::string vectorToString(std::vector<int8_t> vector){
	std::string output;
	for(int i = 0; i < vector.size(); i++){
		output.append(std::to_string(vector.at(i)) + " | ");
	}
	return output;
} 

void setMotorPort(Motor* &motor, int port){
	if(motor) delete motor;
	motor = new Motor(port);
}

void setMotorGroupPort(Motor_Group* &motor_group, std::vector<int8_t> ports){
	if(motor_group) delete motor_group;
	motor_group = new Motor_Group(ports);
}

void drawPortMapping(){
	lcd::set_text(0, "Port Mappings:");
	lcd::set_text(1, " - Left Drive: " + vectorToString(leftDrivePorts));
	lcd::set_text(2, " - Right Drive: " + vectorToString(rightDrivePorts));
	lcd::set_text(3, " - Flywheel: " + std::to_string(flywheelPort));
	lcd::set_text(4, " - Intake: " + std::to_string(intakePort));
}

void initialize() {
	lcd::initialize();
	setMotorPort(flywheelMotor, 3);
	drawPortMapping();
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
	while (true) {
		flywheelMotor -> move(127);
		delay(20);
	}
}
