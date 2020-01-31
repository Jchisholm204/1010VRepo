#include "main.h"
#include "chassis.h"
#include "Intakes.h"
#include "tray.h"
#include "lift.h"
//#include "display.h"
//define controllers
Controller master(E_CONTROLLER_MASTER);
Controller partner(E_CONTROLLER_PARTNER);
/////////////////define the drive motors
///////left drive motors
Motor driveLF(12/*Port*/, E_MOTOR_GEARSET_18/*Gearset(red/blue/green)*/, false/*motor reversed?*/, E_MOTOR_ENCODER_DEGREES/*set encoder units to be used*/);
Motor driveLB(14, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
////right drive motors
Motor driveRF(11, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveRB(15, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
////////////////////define the arm and tray motors
Motor ArmMotor(18, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);
Motor TrayMotor(13, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);
//////////////////define the intake motors
Motor LeftIntake(17, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_ROTATIONS);
Motor RightIntake(16, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_ROTATIONS);

////////////////Classes
intakeClass intakes;
Chassis drivef;
//Display cinema;
//////////////////ADI port assighnment
ADIDigitalIn TrayDownLimit('a');
ADIDigitalIn armLimit('b');
ADIAnalogIn trayPos('c');
ADILineSensor top('d');
ADILineSensor bottom('e');
ADIGyro gyro('f');
//////////Int global Variables
int liftState;
int autoCase;
int currentTestMotor = 0;
//////////////////////////void int
void initialize() {
	///set brake modes for the motors
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

	//cinema.createDisplay();
	//cinema.refresh();
}

void disabled() {}

void competition_initialize() {}
void flipOut(){

}
void autonomous() {
/////run flipout code no matter the auto
	flipOut();

}

void opcontrol() {
	//int armLift = 0;

	while(true){
///////call to drive and intake functions
		intakes.opintake(); //run intake op
		drivef.OP_Chassis(); //run drive code
		//cinema.refresh(); //refresh the screen

//////arm control
		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)){
			liftState += 1; //increases lift state variable by 1 and moves list to next higher position
		}
		else if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)){
			liftState = 0; //resets lift state variable / moves lift all the way down
		}

		delay(15);  //delay the loop so that it doesent use too many reasources
	}
}
