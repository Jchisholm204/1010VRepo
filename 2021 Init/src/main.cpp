#include "main.h"
#include "drive.h"
#include "display.h"
#include "autons.h"
#include "ports.h"
#include "docker.h"
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
Motor sideMOBO(MOBO_1_PORT, E_MOTOR_GEARSET_36, MOBO_1_REVERSED, E_MOTOR_ENCODER_DEGREES);
Motor dockerMOBO(MOBO_2_PORT, E_MOTOR_GEARSET_36, MOBO_2_REVERSED, E_MOTOR_ENCODER_DEGREES);

//	Sensors - Gyro
Imu gyro(GYRO_PORT);
pros::ADIAnalogIn dockerPOT(DOCKER_POT_PORT);
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
		
		delay(20);
	}
	
}
