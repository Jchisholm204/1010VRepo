/* Ingenuity - main.cpp
/* - main.h
* Main File Containing all nessasary calls to operations

# Written By: Jacob Chisholm
# Written For: Ten Ton Vex Robotics Team 1010V

*/

#include "main.h"
#include "ttl/ttl.hpp"
#include "robot/display.h"
#include "robot/drive.hpp"
#include "Constants.hpp"
#include "robot/lift.hpp"
#include "autos/rerun.hpp"
#include "Autos/skills.hpp"

//	CONTROLLERS
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

//	Define the Motors - Drive
pros::Motor driveRB(kPorts::driveRB, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveRM(kPorts::driveRM, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveRF(kPorts::driveRF, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor driveLB(kPorts::driveLB, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLM(kPorts::driveLM, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLF(kPorts::driveLF, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

//	Define the Motors - Conveyer
pros::Motor conveyerMotor(kPorts::CONVEYER, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

//	Define the Motors - Lift (Mobile Goal)
pros::Motor liftMotor(kPorts::LIFT, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

//Pistons
ttl::ADIPiston LiftPiston(kPorts::LIFT_PISTON, LOW);
ttl::ADIPiston DockPiston(kPorts::DOCK_PISTON, false);

//	Sensors
pros::Imu gyro(kPorts::Gyro);
pros::ADIAnalogIn LiftPOT(kPorts::Lift_Potentiometer);

//	Vision Sensors
pros::Vision visionSensor(8, pros::E_VISION_ZERO_CENTER);

//	Classes
Chassis drivef;
Display display;

void initialize() {
	display.createScreen(); // Create all of the basic screen elements
	display.refresh(); // Update battery data to the display for the first time
	lv_btn_set_toggle(recording_enabled_btn, false); //make sure recording is OFF
	//display.msg("Display Initialized, Giro ON", 800);

	//	Brake Modes - Drive
	driveLF.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	driveLM.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	driveLB.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	driveRF.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	driveRM.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	driveRB.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	driveRM.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	driveLM.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);


	if(Lift_Task_Enable == true){
		pros::Task Lift_Task(
			Lift_Task_fn, (void*)"PROS",
			TASK_PRIORITY_DEFAULT,
			TASK_STACK_DEPTH_DEFAULT,
			"Lift Task"
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
		recordAuto(SelectedAuto, !recording_enabled, autoLength);
		display.msg("Auto Recorded:\n" + SelectedAuto);
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