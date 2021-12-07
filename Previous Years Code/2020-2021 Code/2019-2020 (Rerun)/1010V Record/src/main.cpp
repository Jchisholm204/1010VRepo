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
//////////////start Lift Task
	Task Lift_Task (ArmLift_fn, (void*)"PROS", TASK_PRIORITY_DEFAULT,
				TASK_STACK_DEPTH_DEFAULT, "Lift Task");

	//cinema.createDisplay();
	//cinema.refresh();
}
//auto controller = okapi::AsyncControllerFactory::velPID(1, 0.001, 0.0001);
void disabled() {}

void competition_initialize() {}

void autonomous() {

}
int controllertarget;
int expotray(int joystickVal, float driveExp, int joyDead, int motorMin) { //exponential incrementation of joystick values
        int joySign;
        int joyMax = 128 - joyDead;
        int joyLive = abs(joystickVal) - joyDead;
        if (joystickVal > 0) {joySign = 1;}
        else if (joystickVal < 0) {joySign = -1;}
        else {joySign = 0;}
        int power = joySign * (motorMin + ((127 - motorMin) * (pow(joyLive, driveExp) / pow(joyMax, driveExp))));
        return power;
}
void opcontrol() {

	//controller.setTarget(100);
	//controllertarget = controller.getTarget();
	//controller.getOutput();
	int timer = 0; //timer ensures we dont go over 14.5 seconds
	FILE* file = fopen("/usd/NEWrecord.txt", "w");
	/*
	The fopen statement here is used to write an autonomous file to the SD card.
	I typicaly record my files acording to the format "UpRED" for unprotected red, or "pBLUE" for protected blue
	In PROS, files are accessed through /usd/filename.txt
	EX:
	FILE * file = fopen("/usd/UpBLUE.txt", "w");
	Would create a recording for unprotected blue
	*/
		while(timer < 14500){
	/////////////////////////DATA COLECTION
			//////drive
				fprintf(file, "%f\n", driveRB.get_actual_velocity());
				fprintf(file, "%f\n", driveRF.get_actual_velocity());
				fprintf(file, "%f\n", driveLB.get_actual_velocity());
				fprintf(file, "%f\n", driveLF.get_actual_velocity());
				printf("%d\t", RightIntake.get_target_velocity());
				printf("%f\n", RightIntake.get_actual_velocity());
			////tray
				fprintf(file, "%f\n", ArmMotor.get_actual_velocity());
			///intakes
				fprintf(file, "%f\n", LeftIntake.get_actual_velocity());
				fprintf(file, "%f\n", RightIntake.get_actual_velocity());
			////arm
				fprintf(file, "%f\n", TrayMotor.get_actual_velocity());
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


			int LIFTEXP = expotray((partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) * 0.95), 1.5 /*DSiveExp*/, 2 /*JoyDead*/, 10 /*MotorMin*/); //tray expo

			if(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) > 0 &&! TrayDownLimit.get_value()){ //if the joystick is above 0 (moving up); watch to see that the up limit isnt toggled
				 TrayMotor.move_velocity(LIFTEXP); //move the tray motor with the expo output
			 }
			 else if(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) < 0){ //if the joystick is in the down position; stop the action if the down switch it toggled
				 TrayMotor.move_velocity(LIFTEXP); //move the tray motor with the expo output
			 }
			 else{
				 TrayMotor.move_velocity(0);
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
			}
		}
		fclose(file);
}
