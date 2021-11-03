#include "main.h"

//int controllers
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller parter(pros::E_CONTROLLER_PARTNER);

//int motors
pros::Motor driveRB(1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveRF(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLB(3, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLF(4, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor towerMotorR(5, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor towerMotorL(6, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor conveyor(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake(8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

//int sensors
pros::ADIDigitalIn tower_limit_lower(1);
pros::ADIDigitalIn tower_limit_upper('b');

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	//set motor brake modes
	driveLF.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	driveLB.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	driveRF.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	driveRB.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

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
		//drive power
		int Y = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		//drive turning
		int X = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		//drive mechanum
		int Z = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

		driveLB.move(Y + X);
		driveLF.move(Y + X);
		driveRB.move(Y - X);
		driveRF.move(Y - X);

//////////code to run your tower
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
			towerMotorL.move_velocity(100);
			towerMotorR.move_velocity(100);
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
			towerMotorL.move_velocity(-100);
			towerMotorR.move_velocity(-100);
		}
		else{
			towerMotorL.move_velocity(0);
			towerMotorR.move_velocity(0);
		};


///////while true delay
		pros::delay(20);
	}
}
