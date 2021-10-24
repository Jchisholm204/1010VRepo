#include "main.h"
#include "drive.h"
#include "display.h"
#include "autons.h"
#include "ports.h"
#include "ext.h"
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
Motor sideMOBO(MOBO_1_PORT, E_MOTOR_GEARSET_36, MOBO_1_REVERSED, E_MOTOR_ENCODER_DEGREES);
Motor dockerMOBO(MOBO_2_PORT, E_MOTOR_GEARSET_36, MOBO_2_REVERSED, E_MOTOR_ENCODER_DEGREES);

//	Sensors - Gyro
Imu gyro(GYRO_PORT);
pros::ADIDigitalIn Docker_Endstop_Min(Docker_Endstop_Min_Port);
//	Operators - Chassis / Display
Chassis drivef;
Display display;

void initialize() {
	//	Brake Modes - Drive
	driveLF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveLB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	//Operators - Initialization
	display.createScreen();
	display.refresh();
	//	Sensors - Initialization
	gyro.reset();

	pros::Task Docker_Task(
		Docker_Task_fn, (void*)"PROS", //PROS Constant Value
		TASK_PRIORITY_DEFAULT, //Default Priority
		TASK_STACK_DEPTH_DEFAULT, //Default Depth (data it stores)
		"MOBO Dock Task" //Task Name
	);
}

void disabled() {
	while(true){
		//allows the display to be used while robot is disabled
		display.refresh();
	}
}

void competition_initialize() {
	gyro.reset();
}

void autonomous() {

}


void opcontrol() {
	bool intakeDeSync = false;
	bool conveyerDeSync = false;
	while (true) {
		drivef.operator_Chassis();
		//calls to run the operator chassis subset of the chassis controller
		display.refresh();
		//calls to update display elements

		if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){
			dock_state = POS_UP;
		}
		else if (master.get_digital(E_CONTROLLER_DIGITAL_L2))
		{
			dock_state = POS_DOWN;
		}

		if(master.get_digital(E_CONTROLLER_DIGITAL_X)){
			intakeDeSync = true;
		}
		else{
			intakeDeSync = false;
		}

		if(master.get_digital(E_CONTROLLER_DIGITAL_UP)){
			conveyerDeSync = true;
		}
		else{
			conveyerDeSync = false;
		}

		if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){
			intakeMotor.move_velocity(200*(1-conveyerDeSync));
			conveyerMotor.move_velocity(200*(1-intakeDeSync));
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){
			intakeMotor.move_velocity(-200*(1-conveyerDeSync));
			conveyerMotor.move_velocity(-200*(1-intakeDeSync));
		}
		else{
			intakeMotor.move_velocity(0);
			conveyerMotor.move_velocity(0);
		}
		
		delay(20);
	}
	
}
