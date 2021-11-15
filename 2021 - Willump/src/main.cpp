#include "main.h"
#include "drive.h"
#include "display.h"
#include "autons.h"
#include "lift.h"
#include "dock.h"
#include "ports.h"
#include "helpers.h"

//	CONTROLLERS
Controller master(E_CONTROLLER_MASTER);
Controller partner(E_CONTROLLER_PARTNER);

//	Define the Motors - Drive
Motor driveRB(driveRB_PORT, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveRF(driveRF_PORT, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveLB(driveLB_PORT, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor driveLF(driveLF_PORT, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

//	Define the Motors - Conveyer and Intake
Motor intakeMotor(INTAKE_PORT, E_MOTOR_GEARSET_18, INTAKE_REVERSED, E_MOTOR_ENCODER_DEGREES);
Motor conveyerMotor(CONVEYER_PORT, E_MOTOR_GEARSET_18, CONVEYER_REVERSED, E_MOTOR_ENCODER_DEGREES);

//	Define the Motors - Mobile Goal Pickups (MOBO)
Motor liftMotor(LIFT_PORT, E_MOTOR_GEARSET_36, MOBO_1_REVERSED, E_MOTOR_ENCODER_DEGREES);
Motor dockerMotor(DOCKER_PORT, E_MOTOR_GEARSET_36, MOBO_2_REVERSED, E_MOTOR_ENCODER_DEGREES);

//	Sensors
pros::Imu gyro(GYRO_PORT);
pros::ADIDigitalIn Docker_Endstop_Min(Docker_Endstop_Min_Port);
pros::ADIDigitalIn Lift_Endstop_Min(Arm_Endstop_Min_Port);
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

	display.createScreen();
	display.refresh();
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
}

void competition_initialize() {
}

void autonomous() {
	int AutoSelectionVariable = 0;

	//Switch Case Runs Auto//
	switch(AutoSelectionVariable){
		case 1:
			rightAuto();
			break;
		case 2:
			leftAuto();
			break;
		default:
			pros::delay(100);
	}
}


void opcontrol() {
	bool intakeDeSync = false;
	bool conveyerDeSync = false;

	while (true) {
		display.refresh();
		//std::cout << Docker_Optical.get_proximity();
		drivef.operator_Chassis();
		//calls to run the operator chassis subset of the chassis controller

		if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){
			Dock(UP);
		}
		else if (master.get_digital(E_CONTROLLER_DIGITAL_L2))
		{
			Dock(DOWN);
		}

		if(master.get_digital(E_CONTROLLER_DIGITAL_UP)){
			intakeDeSync = true;
		}
		else{
			intakeDeSync = false;
		}

		if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
			conveyerDeSync = true;
		}
		else{
			conveyerDeSync = false;
		}

		if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){
			intakeMotor.move_velocity(200*(1-intakeDeSync));
			conveyerMotor.move_velocity(200*(1-conveyerDeSync));
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){
			intakeMotor.move_velocity(-200*(1-intakeDeSync));
			conveyerMotor.move_velocity(-200*(1-conveyerDeSync));
		}
		else{
			intakeMotor.move_velocity(0);
			conveyerMotor.move_velocity(0);
		};

		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
			Lift(DOWN);
		}
		else if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)){
			Lift(UP);
		}

		delay(20);
	}
	
}
