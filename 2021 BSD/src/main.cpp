#include "main.h"
#include "drive.h"
#include "display.h"
#include "autons.h"
//	CONTROLLERS
Controller master(E_CONTROLLER_MASTER);
Controller partner(E_CONTROLLER_PARTNER);
//	Define the Motors - Drive
Motor driveRB(6, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveRF(19, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveLB(5, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor driveLF(2, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
//	Sensors - Gyro
Imu gyro(20);
//	Operators - Chassis / Display
Chassis drivef;
Display display;

void initialize() {
	//	Brake Modes - Drive
	driveLF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveLB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	//Operators - Initialization
	display.createScreen();
	display.refresh();
	//	Sensors - Initialization
	gyro.reset();
}

void disabled() {
	while(true){
		//allows the display to be used while robot is disabled
		display.refresh();
	}
}

void competition_initialize() {
	gyro.reset();
}

void autonomous() {

}


void opcontrol() {
	while (true) {
		drivef.operator_Chassis();
		//calls to run the operator chassis subset of the chassis controller
		display.refresh();
		//calls to update display elements
		delay(20);
	}
	
}
