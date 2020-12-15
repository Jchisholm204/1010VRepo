#include "main.h"
#include "drive.h"
#include "display.h"
#include "run.h"
#include "intake.h"
//jj

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

// int the chassis and display operators
Chassis drivef;
Display display;

// int the variable for controlling the intakes
int intakeStatus = 0;


void initialize() {
	// set brake modes - controlls what the motor will do when given a value of 0
	driveLF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveLB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	intakeL.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	intakeR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

	//call to create and refresh display elements
	display.createScreen();
	display.refresh();
	
	// Task for running the intake PID controller
	Task Intake_Task (intake_fn, (void*)"PROS", TASK_PRIORITY_DEFAULT,
				TASK_STACK_DEPTH_DEFAULT, "Intake Task");

}

void disabled() {}

void competition_initialize() {}


void autonomous() {
	autoRun();
//run the autorun file when the autonomous function is called by the match controller
}

void opcontrol() {
	// int Speed variable for controlling the top roller speed (0-600 rpm)
	int fwTarg = 0;
	//display.setActiveTab(op_tab);
	while (true) {
		//  Tell the top roller to move with the velocity of the speed variable
		flyWheel.move_velocity(fwTarg);
		//printf("%d\n",SelectedAuto );
		drivef.operator_Chassis();
		//calls to run the operator chassis subset of the chassis controller
		display.refresh();
		//calls to update display elements

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

		pros::delay(10);
		//visionLoop();
	}
}
