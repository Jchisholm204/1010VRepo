/* Ingenuity - main.cpp
/* - main.h
* Main File Containing all nessasary calls to operations
*/
#include "main.h"
#include "robot/display.h"
#include "robot/drive.hpp"
#include "robot/ports.hpp"
#include "tasking/pneumatics.hpp"

//	CONTROLLERS
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

//	Define the Motors - Drive
pros::Motor driveRB(driveRB_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveRF(driveRF_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLB(driveLB_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLF(driveLF_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

//	Define the Motors - Conveyer and Intake
pros::Motor intakeMotor(INTAKE_PORT, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor conveyerMotor(CONVEYER_PORT, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

//	Define the Motors - Mobile Goal Pickups (MOBO)
pros::Motor liftMotor(LIFT_PORT, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor dockerMotor(DOCKER_PORT, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

//	Sensors
pros::ADIGyro posGyro(GYRO_POS_PORT);
pros::ADIGyro absGyro(GYRO_ABS_PORT);
pros::Imu gyro(GYRO_PORT);
pros::ADIDigitalIn Docker_Endstop_Min(Docker_Endstop_Min_PORT);
pros::ADIAnalogIn Lift_POT(Lift_POT_PORT);
pros::Distance lidarFL(FL_LIDAR_PORT);
pros::Distance lidarFR(FR_LIDAR_PORT);
pros::Distance lidarBL(BL_LIDAR_PORT);
pros::Distance lidarBR(BR_LIDAR_PORT);

pros::ADIDigitalOut LiftPiston(LIFT_PISTON_PORT);
pros::ADIDigitalOut DockPiston(DOCK_PISTON_PORT);
pros::ADIDigitalOut SidePiston(SIDE_PISTON_PORT);

Chassis drivef;
Display display;

void initialize() {


}


void disabled() {
	display.Msg("Robot Disabled", 1000);
	display.setActiveTab(TAB_DISABLED);
	lv_btn_set_state(recording_enabled_btn, false);
	//lift_state = START_POS;
	while(true){
		display.refresh(); // updates battery capacity - yes thats all I checked
		pros::delay(100);
	}
}


void competition_initialize() {}


void autonomous() {
	SelectedAuto = 3;
	if(SelectedAuto != 3 && pros::usd::is_installed() == 0){
		printf("NO SD CARD\nCannot Run ReRun Auto\nNot Running Auto");
		display.createErrorBox("No SD Card Detected\nUnable to Playback Auto");
	}
	else if(SelectedAuto == 3){ // run normal skills if selected
		//skillsAuto();
		display.Msg("Skills Auto", 1000);
	}
	else if(SelectedAuto == 0){
		display.Msg("No Auto Selected", 1000);
		pros::delay(100); //dont run an auto
	}
	else{
		display.Msg(("Running Recorded Auto: "+std::to_string(SelectedAuto)).c_str(), 1000);
		//reRunAuto(SelectedAuto); //run rerun auto
		display.Msg(("Finished Running\nAuto: "+std::to_string(SelectedAuto)).c_str(), 1000);
	}
}


void opcontrol() {
bool recording_enabled = lv_btn_get_state(recording_enabled_btn); //true if recording is enabled by display toggle
	int autoLength; // length to record auto for
	int exitStatus; // for displaying exit codes
	//printf("%d", recording_enabled);
	//lift_state = DOWN;

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
		//recordAuto(SelectedAuto, false, autoLength);
		//printf("%d\t", exitStatus);
		display.createErrorBox("Auto Recorded");
	}
	else if(recording_enabled && SelectedAuto == 0){ // error for no auto
		printf("NO AUTO SELECTED");
		display.createErrorBox("No Auto Has Been Selected, Disable Bot and select auto to Continue");

	}
	else if(recording_enabled && SelectedAuto == 3){ // error for norm skills selected
		printf("NORM SKILLS SELECTED");
		//display.createErrorBox("Non ReRun Auto Selected\nDisable Bot to Continue");
	}
	else{ // Not trying to record? Run mainDrive without recording
		printf("%d\t", exitStatus);
		display.Msg("Driver Control Enabled", 1000);
		while(true){
			display.refresh(); //update battery capacity
			//printf("%d\t%d\t%d\t%d\n", VelocityCalc(driveRB, 1), VelocityCalc(driveRF, 1), VelocityCalc(driveLB, 1), VelocityCalc(driveLF, 1));
			//printf("%d\n", testA.get_state());
			operatorControl();
			pros::delay(20);
		}
	}
}
