#include "main.h"
#include "drive.h"
#include "display.h"
#include "autons.h"

Controller master(E_CONTROLLER_MASTER);
Controller partner(E_CONTROLLER_PARTNER);
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

	gyro.reset();


}

ADIDigitalIn LiL('a');
ADIDigitalIn LiR('b');
Distance distance_sensor(13);
Distance rLDR(1);
Distance lLDR(9);
Distance lbLDR(7);
Distance rbLDR(8);
Imu gyro(20);

void disabled() {}

void competition_initialize() {
	gyro.reset();
}

void autonomous() {
	//skills();
	//leftAuto();
	sadAuto();
	//rightAuto();

}


void opcontrol() {
	int fwTarg =  0;
	//display.setActiveTab(op_tab);
	while (true) {
		//printf("%d\n",SelectedAuto );
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

		/*//  Set up the Top roller speed control - Y = Stop / X = Full Speed / B = Slow Outtake (in case of jam)
		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)){
			fwTarg=0;
		}
		else if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)){
			fwTarg=470;
		}
		else if(partner.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)){
			fwTarg+=10;
		}
		else if(partner.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)){
			fwTarg-=10;
		}
		else if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
			fwTarg=-100;
		}

		flyWheel.move_velocity(fwTarg);
		printf("fwTarg: %d\n", fwTarg);
*/

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
