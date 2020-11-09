#include "main.h"
#include "drive.h"
#include "display.h"

Controller master(E_CONTROLLER_MASTER);
Motor driveRB(11, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveRF(10, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveLB(12, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor driveLF(1, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

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

void disabled() {
	while(true){
		display.refresh();
		delay(100);
	}
}

void competition_initialize() {}


void autonomous() {

}

double getVelocity(Motor motor){
	return motor.get_actual_velocity();
}
void opcontrol() {
	int timer = 0;
	FILE* file = fopen("/usd/record.txt", "w");
	while (timer < 14500) {
		display.refresh();
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
		drivef.operator_Chassis();

		delay(15);
		timer += 15;

		if(timer > 14500){
			driveLB.move(0);
			driveLF.move(0);
			driveRB.move(0);
			driveRF.move(0);
			flyWheel.move(0);
			roller.move(0);
			intakeR.move(0);
			intakeL.move(0);
		}
	}
		fclose(file);
}
