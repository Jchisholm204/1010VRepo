#include "main.h"
#include "drive.h"
#include "display.h"
#include "run.h"
#include "intake.h"


Controller master(E_CONTROLLER_MASTER);
Controller partner(E_CONTROLLER_PARTNER);
Motor driveRB(8, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveRF(10, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveLB(7, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor driveLF(3, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

Motor intakeL(4, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);
Motor intakeR(9, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);

Motor roller(2, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor flyWheel(1, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);


ADIDigitalIn intakeRlimit('a');
ADIDigitalIn intakeLlimit('b');

Chassis drivef;
Display display;
//int the chassis and display operators

int intakeStatus = 0;
//int the variable for controlling the intakes

void initialize() {
	driveLF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveLB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	intakeL.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	intakeR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

	display.createScreen();
	display.refresh();
	//call to create and refresh display elements

	//visionINT();
	Task Intake_Task (intake_fn, (void*)"PROS", TASK_PRIORITY_DEFAULT,
				TASK_STACK_DEPTH_DEFAULT, "Intake Task");
				//int tasking for the intake grippers

}

void disabled() {}

void competition_initialize() {}


void autonomous() {
	autoRun();
//run the autorun file when the autonomous function is called by the match controller
}

void opcontrol() {
	int fwTarg = 0;
	//display.setActiveTab(op_tab);
	while (true) {
		flyWheel.move_velocity(fwTarg);
		//printf("%d\n",SelectedAuto );
		drivef.operator_Chassis();
		//calls to run the operator chassis subset of the chassis controller
		display.refresh();
		//calls to update display elements

		if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){ //toggle open
			intakeStatus = INTAKE_CLOSED;
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){ //close toggle
			intakeStatus = INTAKE_OPEN;
		}
		if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){
			roller.move_velocity(200);
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_L2)){
			roller.move_velocity(-200);
		}
		else{
			roller.move_velocity(0);
		}
		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)){
			fwTarg=0;
		}
		else if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)){
			fwTarg=600;
		}
		else if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
			fwTarg=-200;
		}
		//else loop to control the intakes and roller
		pros::delay(10);
		//visionLoop();
	}
}
