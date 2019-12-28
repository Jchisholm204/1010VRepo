#include "main.h"
#include "Intakes.h"
#include "autons.h"
Controller master(E_CONTROLLER_MASTER);
Controller partner(E_CONTROLLER_PARTNER);

Motor driveLF(12, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor driveLB(14, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

Motor driveRF(11, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveRB(15, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

Motor ArmMotor(18, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);
Motor TrayMotor(13, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);

Motor LeftIntake(17, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_ROTATIONS);
Motor RightIntake(16, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_ROTATIONS);

intakeClass intakes;

void initialize() {
	TrayMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	ArmMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	RightIntake.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	LeftIntake.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveLF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveLB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	pros::lcd::initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	oneCubeAuto();
}

void opcontrol() {
	while(true){
		intakes.opintake();
	}
}
