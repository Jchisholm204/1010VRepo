#include "main.h"
#include "chassis.h"
#include "Intakes.h"
#include "autons.h"
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

void autonomous() {

}

void opcontrol() {
	int timer = 0; //timer ensures we dont go over 14.5 seconds
	FILE* mvfile = fopen("/usd/example.txt", "w");
	FILE* armf = fopen("/usd/armfile.txt", "w");
	FILE* intakef = fopen("/usd/intake.txt", "w");
	FILE* typefile = fopen("/usd/namefile.txt", "w");
	fprintf(typefile, "UNNAMED AUTO FILE\n");
	fprintf(typefile,
		"This file is used for a discription of the auto, PLEASE DELETE THIS LINE AFTER USE!\n"
	);
	/*
	none of these files need to be changed, it is recomended that you use multiple SD cards,
	however, you could also just swap the files on and off of the SD.
	If you know what you are doing you could also reconfigure these files into one
	I chose not to do this so that I could modify the arm file to work with my PID
	*/
		while(timer < 14500){
	/////////////////////////DATA COLECTION
			//////drive
				fprintf(intakef, "%d\n", intakeState);
				fprintf(armf, "%d\n", liftState);
				fprintf(mvfile, "%d\n", driveRB.get_voltage());
				fprintf(mvfile, "%d\n", driveRF.get_voltage());
				fprintf(mvfile, "%d\n", driveLB.get_voltage());
				fprintf(mvfile, "%d\n", driveLF.get_voltage());
				printf("%d\n", driveRB.get_voltage());
			////tray
				fprintf(mvfile, "%d\n", TrayMotor.get_voltage());
			///inatkes
				fprintf(mvfile, "%d\n", LeftIntake.get_voltage());
				fprintf(mvfile, "%d\n", RightIntake.get_voltage());
			////arm
				fprintf(mvfile, "%d\n", ArmMotor.get_voltage());
	///////////////////////////REGULAR OPCONTROL//////////////////////

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
			timer += 15;
			if(timer > 14500){ //stop all motors
				driveLB.move(0);
				driveLF.move(0);
				driveRB.move(0);
				driveRF.move(0);
				TrayMotor.move(0);
				ArmMotor.move(0);
				RightIntake.move(0);
				LeftIntake.move(0);
				//close the files
				fclose(mvfile);
				fclose(armf);
				fclose(intakef);
			}
		}
}
