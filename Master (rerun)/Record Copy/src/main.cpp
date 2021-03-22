#include "main.h"
#include "drive.h"
#include "display.h"

Controller master(E_CONTROLLER_MASTER);
Controller partner(E_CONTROLLER_PARTNER);
Motor driveRB(8, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveRF(10, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveLB(7, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor driveLF(3, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
//  Define the Motors - Intakes
Motor intakeL(4, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor intakeR(9, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
// Define the Motors - Internal Rollers / Top Roller
Motor roller(2, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor flyWheel(1, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);

Chassis drivef;
Display display;
//int the chassis and display operators

void initialize() {
	driveLF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveLB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

	intakeL.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	intakeR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	roller.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

	display.createScreen();
	display.refresh();
	//call to create and refresh display elements


}


ADIDigitalIn LiL('a');
ADIDigitalIn LiR('b');
//pros::ADIUltrasonic sensor (PORT_PING, PORT_ECHO);
//port_ping	-- the port connected to the orange OUTPUT cable. This should be in port 1, 3, 5, or 7 (‘A’, ‘C’, ‘E’, ‘G’).
//port_echo	-- the port connected to the yellow INPUT cable. This should be in the next highest port following port_ping.
ADIUltrasonic lULT('c', 'd');
ADIUltrasonic rULT('e', 'f');
ADIUltrasonic bULT('g', 'h');

void disabled() {}

void competition_initialize() {}


void autonomous() {
}

void opcontrol() {
	int fwTarg =  0;
	int timer = 0;

	FILE * recFile = fopen("/usd/NEWrecord.txt", "w");
	//display.setActiveTab(op_tab);
	while (timer < 14500) {
		drivef.operator_Chassis();
		display.refresh();
		if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){
			roller.move_velocity(190);
			flyWheel.move_velocity(480);
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_L2)){
			roller.move_velocity(-190);
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
		delay(15);
		timer += 15;
		if(timer > 14500){ //stop all motors
			driveLB.move_velocity(0);
			driveLF.move_velocity(0);
			driveRB.move_velocity(0);
			driveRF.move_velocity(0);
			flyWheel.move_velocity(0);
			roller.move_velocity(0);
			intakeR.move_velocity(0);
			intakeR.move_velocity(0);
		}	
		fprintf(recFile, "%f\n", driveRB.get_actual_velocity());
		fprintf(recFile, "%f\n", driveRF.get_actual_velocity());
		fprintf(recFile, "%f\n", driveLB.get_actual_velocity());
		fprintf(recFile, "%f\n", driveLF.get_actual_velocity());

		fprintf(recFile, "%f\n", flyWheel.get_target_velocity());
		fprintf(recFile, "%f\n", roller.get_actual_velocity());
		
		fprintf(recFile, "%f\n", intakeL.get_target_velocity());
		fprintf(recFile, "%f\n", intakeR.get_target_velocity());
	}
	fclose(recFile);
	
}
