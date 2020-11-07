#include "main.h"
#include "drive.h"
#include "display.h"

Controller master(E_CONTROLLER_MASTER);
Motor driveRB(1, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor driveRF(2, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor driveLB(9, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveLF(10, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

Motor intakeL(101, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor intakeR(101, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

Motor roller(101, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor flyWheel(101, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);

Chassis drivef;
Display display;

void initialize() {
	driveLF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveLB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

	display.createScreen();
	display.refresh();
}

void disabled() {}

void competition_initialize() {}


void autonomous() {}

void opcontrol() {
	while (true) {
		drivef.operator_Chassis();
		pros::delay(20);
		display.refresh();
	}
}
