/* Aura - main.cpp
/* - main.h
* Main File Containing all nessasary calls to operations

# Written By: Jacob Chisholm
# Written For: Ten Ton Vex Robotics Team 1010V

*/

#include "main.h"
#include "ttl/ttl.hpp"
#include "robot/display.h"
#include "robot/drive.hpp"
#include "robot/ports.hpp"
#include "tasking/lift.hpp"
#include "tasking/dock.hpp"
#include "autos.hpp"
#include "robot/vision.hpp"

//	CONTROLLERS
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

//	Define the Motors - Drive
pros::Motor driveRB(driveRB_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveRF(driveRF_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLB(driveLB_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLF(driveLF_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

//	Define the Motors - Conveyer
pros::Motor conveyerMotor(CONVEYER_MOTOR_PORT, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

//	Define the Motors - Mobile Goal Pickups (MOBO)
pros::Motor liftMotorL(LIFT_MOTOR_PORT_L, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor liftMotorR(LIFT_MOTOR_PORT_R, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor dockerMotor(DOCKER_MOTOR_PORT, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

//	Sensors
pros::ADIGyro posGyro(GYRO_POS_PORT);
pros::ADIGyro absGyro(GYRO_ABS_PORT);
pros::Imu gyro(GYRO_PORT);
pros::ADIAnalogIn LiftPOT(Lift_POT_PORT);
pros::ADIDigitalIn dock_limit_switch(Docker_Endstop_Min_PORT);
pros::Distance distFL(FL_LIDAR_PORT);
pros::Distance distFR(FR_LIDAR_PORT);
pros::Distance distBL(BL_LIDAR_PORT);
pros::Distance distBR(BR_LIDAR_PORT);

pros::Vision visionSensor(VISION_SENSOR_PORT, pros::E_VISION_ZERO_CENTER);

ttl::ADIPiston LiftPiston(LIFT_PISTON_PORT, LOW);
ttl::ADIPiston SidePiston(SIDE_PISTON_PORT, false);

Chassis drivef(127, 1.2, 1.4);
Display display;

void initialize() {

	pros::delay(1300); //wait 1.3 seconds for the ADIGyros to finish initialization

	display.createScreen(); // Create all of the basic screen elements
	display.refresh(); // Update battery data to the display for the first time
	//lv_btn_set_toggle(recording_enabled_btn, false); //make sure recording is OFF
	display.msg("Display Initialized, Giro ON", 800);

	//	Brake Modes - Drive
	driveLF.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	driveLB.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	driveRF.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	driveRB.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

	liftMotorL.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	liftMotorR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);


	if(Lift_Task_Enable == true){
		pros::Task Lift_Task(
			Lift_Task_fn, (void*)"PROS",
			TASK_PRIORITY_DEFAULT,
			TASK_STACK_DEPTH_DEFAULT,
			"Lift Task"
		);
	}

	if(Dock_Task_Enable == true){
		pros::Task Docker_Task(
			Dock_Task_fn, (void*)"PROS",
			TASK_PRIORITY_DEFAULT,
			TASK_STACK_DEPTH_DEFAULT,
			"Docker Task"
		);
	}
}

//runs while the robot is disabled
void disabled() {

	display.msg("Robot Disabled", 1000);
	display.setActiveTab(TAB_DISABLED); //set display to show disabled tab

	lv_btn_set_state(recording_enabled_btn, false); //disable recording - prevents accidental recording/erasing of autos

	while(true){
		display.refresh(); // updates battery capacity - yes thats all I checked
		pros::delay(100);
	}
}


void competition_initialize() {}


void autonomous() {
	SelectedAuto = 3;
	if(SelectedAuto != 3 && pros::usd::is_installed() == 0){
		display.msg("No SD Card Detected\nUnable to Playback Auto");
	}
	else if(SelectedAuto == 3){ // run normal skills if selected
		skillsAuto();
		display.msg("Skills Auto", 1000);
	}
	else if(SelectedAuto == 0){
		display.msg("No Auto Selected", 1000);
		pros::delay(100); //dont run an auto
	}
	else{
		display.msg(("Running Recorded Auto: "+std::to_string(SelectedAuto)).c_str(), 1000);
		reRunAuto(SelectedAuto); //run rerun auto
		display.msg(("Finished Running\nAuto: "+std::to_string(SelectedAuto)).c_str(), 1000);
	}
}


void opcontrol() {
	bool recording_enabled = lv_btn_get_state(recording_enabled_btn); //true if recording is enabled by display toggle
	int autoLength; // length to record auto for

	display.setActiveTab(TAB_OP); //change display to show operator tab

	if	(SelectedAuto == 4)	{	autoLength = 60*1000;/*60 sec for skills rerun*/	}
	else					{	autoLength = 15*1000; /*15 sec for match autos*/	}

	if(pros::usd::is_installed() == 0 && recording_enabled){
		display.msg("No SD Card Detected\nUnable to Record");
	}

	else if(recording_enabled && SelectedAuto/*Do NOT allow recording if no auto selected*/ != 0 && SelectedAuto/*or if norm skills selected*/ != 3){
		display.msg("Auto Recorded");
	}

	else if(recording_enabled && SelectedAuto == 0){ // error for no auto
		display.msg("No Auto Has Been Selected, Disable Bot and select auto to Continue");
	}

	else if(recording_enabled && SelectedAuto == 3){ // error for norm skills selected
		display.msg("Non ReRun Auto Selected\nDisable Bot to Continue");
	}

	else{ // Not trying to record? Run regular operatorControl without recording
		display.msg("Driver Control Enabled", 1000);
		while(true){
			display.refresh(); //update battery capacity
			operatorControl();
			pros::delay(20);
		}
	}
}