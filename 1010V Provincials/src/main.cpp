#include "main.h"
#include "chassis.h"
#include "Intakes.h"
#include "autons.h"
#include "tray.h"
#include "lift.h"
Controller master(E_CONTROLLER_MASTER);
Controller partner(E_CONTROLLER_PARTNER);

Motor driveLF(12, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor driveLB(14, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

Motor driveRF(11, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveRB(15, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

Motor ArmMotor(18, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);
Motor TrayMotor(13, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);

Motor LeftIntake(17, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_ROTATIONS);
Motor RightIntake(16, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_ROTATIONS);

////////////////Classes
intakeClass intakes;
Chassis drivef;
//////////////////ADI
ADIDigitalIn TrayDownLimit('a');
ADIDigitalIn armLimit('b');
ADIAnalogIn trayPos('c');
ADILineSensor top('d');
ADILineSensor bottom('e');
ADIGyro gyro('f');
//////////Int Variables
int liftState;
int autoCase;
int currentTestMotor = 0;
//////////////////////////void int
void initialize() {
	TrayMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	ArmMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	RightIntake.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	LeftIntake.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveLF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveLB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
//////////////start Tray Task
	Task Tray_Task (trayPreset_fn, (void*)"PROS", TASK_PRIORITY_DEFAULT,
				TASK_STACK_DEPTH_DEFAULT,	"Tray Task");
//////////////start Lift Task
	Task Lift_Task (ArmLift_fn, (void*)"PROS", TASK_PRIORITY_DEFAULT,
				TASK_STACK_DEPTH_DEFAULT, "Lift Task");
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	flipOut();

	//autoCase = 1; //select auto with switch case

	switch(autoCase){
		case 1:
			oneCubeAuto();
			break;
		case 2:
			redUnprotected();
			break;
		case 3:
			blueUnprotected();
			break;
		case 4:
			redThreePnt();
			break;
		case 5:
			blueThreePnt();
			break;
		default:
			printf("AutoCase Error");
	}
}

void opcontrol() {
	int armLift = 0;
	while(true){
		intakes.opintake(); //run intake op
		drivef.OP_Chassis(); //run drive code
		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)){
			liftState += 1; //increases lift state variable by 1 and moves list to next higher position
		}
		else if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)){
			liftState = 0; //resets lift state variable / moves lift all the way down
		}
		delay(15);
	}
}
