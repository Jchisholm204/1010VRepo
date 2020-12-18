#include "main.h"
#include "drive.h"
#include "display.h"
#include "intake.h"

// Define the Controllers
Controller master(E_CONTROLLER_MASTER);
Controller partner(E_CONTROLLER_PARTNER);

//  Define the Motors - Drive
Motor driveRB(8, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveRF(10, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveLB(7, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor driveLF(3, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
//  Define the Motors - Intakes
Motor intakeL(4, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);
Motor intakeR(9, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);
// Define the Motors - Internal Rollers / Top Roller
Motor roller(2, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor flyWheel(1, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);

// Define the limit switches for closing the intakes
ADIDigitalIn intakeRlimit('a');
ADIDigitalIn intakeLlimit('b');

Chassis drivef;
Display display;

int intakeStatus = 0;

void initialize() {
	driveLF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveLB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

	roller.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	flyWheel.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

	intakeL.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	intakeR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);


	display.createScreen();
	display.refresh();

	//int the intake task
	Task Intake_Task (intake_fn, (void*)"PROS", TASK_PRIORITY_DEFAULT,
				TASK_STACK_DEPTH_DEFAULT, "Intake Task");
	
	
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
			autoLength = 10000;
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
				autoLength = 10000;
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

double getDeg(Motor motor){
	return motor.get_position();
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
			autoLength = 10000;
			break;
	}
	printf("%d\n", SelectedAuto);
	printf("recording\n");
		// int Speed variable for controlling the top roller speed (0-600 rpm)
	int fwTarg = 0;
	while (timer < autoLength) {
		//  Tell the top roller to move with the velocity of the speed variable
		flyWheel.move_velocity(fwTarg);
		//printf("%d\n",SelectedAuto );
		drivef.operator_Chassis();
		//calls to run the operator chassis subset of the chassis controller
		display.refresh();
		//calls to update display elements

		printf("L: %d", getDeg(intakeL))
		//  Intake Control - R1 Closes / R2 Opens
		if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){ //toggle open
			intakeStatus = INTAKE_CLOSED;
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){ //close toggle
			intakeStatus = INTAKE_OPEN;
		}
		//  Internal Roller Control - L1 Intakes / L2 Outtakes
		if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){
			roller.move_velocity(200);
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_L2)){
			roller.move_velocity(-200);
		}
		else{
			roller.move_velocity(0);
		}
		//  Set up the Top roller speed control - Y = Stop / X = Full Speed / B = Slow Outtake (in case of jam)
		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)){
			fwTarg=0;
		}
		else if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)){
			fwTarg=600;
		}
		else if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
			fwTarg=-200;
		}

		delay(15);
		timer += 15;

		if(timer > autoLength){
			driveLB.move_velocity(0);
			driveLF.move_velocity(0);
			driveRB.move_velocity(0);
			driveRF.move_velocity(0);
			flyWheel.move_velocity(0);
			roller.move_velocity(0);
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
		fprintf(file, "%s\n", std::to_string(intakeStatus).c_str());
		//instead of using the motor values get the pid input
		//fprintf(file, "%f\n", getVelocity(intakeR));
		//fprintf(file, "%f\n", getVelocity(intakeL));
				////fast spinning roller
		fprintf(file, "%f\n", getVelocity(flyWheel));
	}
		fclose(file);
		printf("finished");
}
