#include "main.h"
#include "drive.h"
#include "display.h"
#include "autons.h"
#include "lift.h"
#include "dock.h"
#include "ports.h"
#include "helpers.h"
#include "display/lvgl.h"

//	CONTROLLERS
Controller master(E_CONTROLLER_MASTER);
Controller partner(E_CONTROLLER_PARTNER);

//	Define the Motors - Drive
Motor driveRB(driveRB_PORT, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveRF(driveRF_PORT, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveLB(driveLB_PORT, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor driveLF(driveLF_PORT, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

//	Define the Motors - Conveyer and Intake
Motor intakeMotor(INTAKE_PORT, E_MOTOR_GEARSET_06, INTAKE_REVERSED, E_MOTOR_ENCODER_DEGREES);
Motor conveyerMotor(CONVEYER_PORT, E_MOTOR_GEARSET_06, CONVEYER_REVERSED, E_MOTOR_ENCODER_DEGREES);

//	Define the Motors - Mobile Goal Pickups (MOBO)
Motor liftMotor(LIFT_PORT, E_MOTOR_GEARSET_36, MOBO_1_REVERSED, E_MOTOR_ENCODER_DEGREES);
Motor dockerMotor(DOCKER_PORT, E_MOTOR_GEARSET_36, MOBO_2_REVERSED, E_MOTOR_ENCODER_DEGREES);

//	Sensors
pros::Imu gyro(GYRO_PORT);
pros::ADIDigitalIn Docker_Endstop_Min(Docker_Endstop_Min_Port);
pros::ADIAnalogIn Lift_POT(Lift_POT_Port);
pros::Optical Docker_Optical(Docker_Optical_Port);
pros::Distance lidarFL(FL_LIDAR_PORT);
pros::Distance lidarFR(FR_LIDAR_PORT);
pros::Distance lidarBL(BL_LIDAR_PORT);
pros::Distance lidarBR(BR_LIDAR_PORT);

//	Pneumatics
pros::ADIDigitalOut LiftPiston(LIFT_INTAKE_PORT);


//	Operators - Chassis / Display
Chassis drivef;
Display display;

void initialize() {

	display.createScreen(); // Create all of the basic screen elements
	display.refresh(); // Update battery data to the display for the first time
	//lv_btn_set_toggle(recording_enabled_btn, false); //make sure recording is OFF

	//	Brake Modes - Drive
	driveLF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveLB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

	//	Sensors - Initialization
	//gyro.reset(); //broken

	//	Start tasks
	if(Dock_Task_Enable == true){
		pros::Task Docker_Task(
			Docker_Task_fn, (void*)"PROS", //PROS Constant Value
			TASK_PRIORITY_DEFAULT, //Default Priority
			TASK_STACK_DEPTH_DEFAULT, //Default Depth (data it stores)
			"Mobile Goal Dock Task" //Task Name
		);
	}
	if(Lift_Task_Enable == true){
		pros::Task Lift_Task(
			Lift_Task_fn, (void*)"PROS",
			TASK_PRIORITY_DEFAULT,
			TASK_STACK_DEPTH_DEFAULT,
			"Lift Task"
		);
	}
}

void disabled() {
	display.Msg("Robot Disabled", 1000);
	display.setActiveTab(TAB_DISABLED);
	lv_btn_set_state(recording_enabled_btn, false);
	while(true){
		display.refresh(); // updates battery capacity - yes thats all I checked
		pros::delay(100);
	}
}

void competition_initialize() {
}

void autonomous() {
	if(SelectedAuto != 3 && pros::usd::is_installed() == 0){
		printf("NO SD CARD\nCannot Run ReRun Auto\nNot Running Auto");
		display.createErrorBox("No SD Card Detected\nUnable to Playback Auto");
	}
	else if(SelectedAuto == 3){ // run normal skills if selected
		skillsAuto();
		display.Msg("Skills Auto", 1000);
	}
	else if(SelectedAuto == 0){
		display.Msg("No Auto Selected", 1000);
		pros::delay(100); //dont run an auto
	}
	else{
		display.Msg(("Running Recorded Auto: "+std::to_string(SelectedAuto)).c_str(), 1000);
		reRunAuto(SelectedAuto); //run rerun auto
		display.Msg(("Finished Running\nAuto: "+std::to_string(SelectedAuto)).c_str(), 1000);
	}
}


void opcontrol() {
	bool recording_enabled = lv_btn_get_state(recording_enabled_btn); //true if recording is enabled by display toggle
	int autoLength; // length to record auto for
	int exitStatus; // for displaying exit codes
	//printf("%d", recording_enabled);

	display.setActiveTab(TAB_OP);

	if(SelectedAuto == 4){
		autoLength = 60*1000; // 60 sec for skills rerun
	}
	else{
		autoLength = 15*1000; // 15 sec for match autos
	}
	if(pros::usd::is_installed() == 0 && recording_enabled){
		printf("NO SD CARD");
		display.createErrorBox("No SD Card Detected\nUnable to Record");
	}
	else if(recording_enabled && SelectedAuto/*Do NOT allow recording if no auto selected*/ != 0 && SelectedAuto/*or if norm skills selected*/ != 3){
		//run the record program
		recordAuto(SelectedAuto, false, autoLength);
		//printf("%d\t", exitStatus);
		display.createErrorBox("Auto Recorded");
	}
	else if(recording_enabled && SelectedAuto == 0){ // error for no auto
		exitStatus = EXIT_FAILURE;
		printf("NO AUTO SELECTED");
		display.createErrorBox("No Auto Has Been Selected, Disable Bot and select auto to Continue");

	}
	else if(recording_enabled && SelectedAuto == 3){ // error for norm skills selected
		exitStatus = EXIT_FAILURE;
		printf("NORM SKILLS SELECTED");
		//display.createErrorBox("Non ReRun Auto Selected\nDisable Bot to Continue");
	}
	else{ // Not trying to record? Run mainDrive without recording
		exitStatus = EXIT_CODE_0;
		printf("%d\t", exitStatus);
		display.Msg("Driver Control Enabled", 1000);
		while(true){
			display.refresh(); //update battery capacity
			//printf("%d\t%d\t%d\t%d\n", VelocityCalc(driveRB, 1), VelocityCalc(driveRF, 1), VelocityCalc(driveLB, 1), VelocityCalc(driveLF, 1));
			mainDrive();
			pros::delay(20);
		}
	}
}
