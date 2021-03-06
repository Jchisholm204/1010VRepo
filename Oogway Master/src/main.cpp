#include "main.h"
#include "drive.h"
#include "display.h"
#include "autons.h"
#include "exr.h"
	//CONTROLLERS
Controller master(E_CONTROLLER_MASTER);
Controller partner(E_CONTROLLER_PARTNER);
//	Define the Motors - Drive
Motor driveRB(6, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveRF(19, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveLB(5, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor driveLF(2, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
//  Define the Motors - Intakes
Motor intakeL(3, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor intakeR(17, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
// Define the Motors - Internal Rollers / Top Roller
Motor roller(10, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor flyWheel(18, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
//	Sensors - intake limit switches
ADIDigitalIn LiL('a');
ADIDigitalIn LiR('b');
//	Sensors - ball detectors
ADIUltrasonic ballDetector('e', 'f'); //legacy
Optical colorSensor(12);
//	Sensors - Tower Distance Sensors
Distance rLDR(1);
Distance lLDR(9);
//	Sensors - Rear Distance
Distance lbLDR(7);
Distance rbLDR(8);
//	Sensors - Gyro
Imu gyro(20);
//	Sensors - Auto Pent
ADIPotentiometer autoPot('g');
ADIDigitalIn stupidButton('h');
//	Operators - Chassis / Display
Chassis drivef;
Display display;

void initialize() {
	//	Brake Modes - Drive
	driveLF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveLB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	//	Brake Modes - Intakes
	intakeL.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	intakeR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	roller.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	//Operators - Initialization
	display.createScreen();
	display.refresh();
	//	Sensors - Initialization
	gyro.reset();
}

void disabled() {
	while(true){
		//allows the display to be used while robot is disabled
		display.disabledRefresh();
	}
}

void competition_initialize() {
	gyro.reset();
}

void autonomous() {
	//skills();
	leftAuto();
	//leftCycle();
	//sadAuto();
	//rightAuto();

}


void opcontrol() {
	int fwTarg =  0;
	//display.setActiveTab(op_tab);
	/*
		roller.move_velocity(200);
		flyWheel.move_velocity(200);
		cycle(4);
		roller.move_velocity(0);
		*/
	
	while (true) {
		/*
		if(stupidButton.get_value() == 1){
			intakeL.move_velocity(180 * (1 - LiL.get_value())); //stop intakes moving backwards if limit pressed
			intakeR.move_velocity(180 * (1 - LiR.get_value()));
		}
		else{
			intakes(autoPot.get_value()/20);
		}*/
		
		//printf("%d\n",SelectedAuto );
		printf("%d\n", autoPot.get_value());
		drivef.operator_Chassis();
		//calls to run the operator chassis subset of the chassis controller
		display.refresh();
		//calls to update display elements
		if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){
			roller.move_velocity(200);
			flyWheel.move_velocity(470);
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_L2)){
			roller.move_velocity(-200);
		}
		else{
			roller.move_velocity(0);
			flyWheel.move_velocity(0);
		}
		if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){
			intakeL.move_velocity(-200);
			intakeR.move_velocity(-200);
			//roller.move_velocity(20);
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){
			intakeL.move_velocity(180 * (1 - LiL.get_value())); //stop intakes moving backwards if limit pressed
			intakeR.move_velocity(180 * (1 - LiR.get_value()));
		}
		else{
			intakeL.move_velocity(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
			intakeR.move_velocity(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));
		}
		//else loop to control the intakes and roller
		
		delay(20);
		//visionLoop();
	}
	
}
