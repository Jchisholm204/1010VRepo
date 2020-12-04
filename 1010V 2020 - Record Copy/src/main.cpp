#include "main.h"
#include "drive.h"
#include "display.h"

Controller master(E_CONTROLLER_MASTER);
Motor driveRB(11, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveRF(10, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveLB(12, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor driveLF(1, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

Motor intakeL(8, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);
Motor intakeR(9, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);

Motor roller(7, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor flyWheel(6, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);

Chassis drivef;
Display display;


void initialize() {
	driveLF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveLB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

	display.createScreen();
	display.refresh();

	////Auton Initializers
	printf("Selected Auto:...Unknown");
	printf("GameMode: ...int\n");
	switch (SelectedAuto) { //get the auto selected on the display
		case 1:
			autoLength = 14500;
			break;
		case 2:
			autoLength = 14500;
			break;
		case 3:
			autoLength = 59500;
			break;
		default:
			autoLength = 14500;
			break;
	}
}

void disabled() {
	while(true){
		display.refresh();
		printf("Selected Auto:""%d\t", SelectedAuto);
		printf("GameMode: Disabled\n");
		switch (SelectedAuto) { //get the auto selected on the display
			case 1:
				autoLength = 14500;
				break;
			case 2:
				autoLength = 14500;
				break;
			case 3:
				autoLength = 59500;
				break;
			default:
				autoLength = 14500;
				break;
		}
		delay(800);//long delay as the robot should be disabled
	}
}

void competition_initialize() {}


void autonomous() {

}

//make a get velocity return fuction..
//because it doesent work normaly for some reason
double getVelocity(Motor motor){
	return motor.get_actual_velocity();
}

//ignore this
//	return std::to_string(status).c_str();

void opcontrol() {
	int timer = 0;
	FILE*file;
	switch (SelectedAuto) { //get the auto selected on the display and open the corisponding file
		case 1:
			file = fopen("/usd/red.txt", "w");
			autoLength = 14500;
			break;
		case 2:
			file = fopen("/usd/blue.txt", "w");
			autoLength = 14500;
			break;
		case 3:
			file = fopen("/usd/skills.txt", "w");
			autoLength = 59500;
			break;
		default: //if there is not auto file selected, record to the test file
			file = fopen("/usd/record.txt", "w");
			autoLength = 14500;
			break;
	}
	printf("%d\n", SelectedAuto);
	printf("recording\n");

	while (timer < autoLength) {
		//display.refresh();
		drivef.operator_Chassis();

		delay(15);
		timer += 15;

		if(timer > autoLength){
			driveLB.move_velocity(0);
			driveLF.move_velocity(0);
			driveRB.move_velocity(0);
			driveRF.move_velocity(0);
			flyWheel.move_velocity(0);
			roller.move_velocity(0);
			intakeR.move_velocity(0);
			intakeL.move_velocity(0);
		}
		/////////////////////////DATA COLECTION
				//////drive
		fprintf(file, "%f\n", getVelocity(driveRB));
		fprintf(file, "%f\n", getVelocity(driveRF));
		fprintf(file, "%f\n", getVelocity(driveLB));
		fprintf(file, "%f\n", getVelocity(driveLF));
				////roller
		fprintf(file, "%f\n", getVelocity(roller));
				///intakes
		fprintf(file, "%f\n", getVelocity(intakeR));
		fprintf(file, "%f\n", getVelocity(intakeL));
				////fast spinning roller
		fprintf(file, "%f\n", getVelocity(flyWheel));
	}
		fclose(file);
		printf("finished");
}