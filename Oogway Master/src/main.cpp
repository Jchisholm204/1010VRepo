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
	//call to create and refresh display elements


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

void intakes(int vel){//hi
	intakeL.move_velocity(-vel);
	intakeR.move_velocity(-vel);
}

void autonomous() {
    intakes(200);
	pros::delay(500);
	roller.move_velocity(90);
	pros::delay(1000);
	roller.move_velocity(0);
	drivef.drive(700, 2000);
	intakes(-100);
	drivef.turn(155, 2000);
	drivef.time(800, 150);
	flyWheel.move_velocity(550);
	drivef.twrAlign(2000, 450, 250);
	roller.move_velocity(200);
	pros::delay(450);
	roller.move_velocity(0);
	pros::delay(1000);
	drivef.turn(-18, 800);
	drivef.move(-2850, 5000);
	intakes(200);
	drivef.turn(-65, 1500); //46
	drivef.heading(110, 0, 1500);
	drivef.time(1000, 100);
	drivef.heading(100, 0, 1000);
	drivef.time(800, -100);
	drivef.heading(105, 0, 1500);
	intakes(-180);
	pros::delay(800);
	intakes(0);
	drivef.timeDrive(1500, 70, 75);
	flyWheel.move_velocity(460);
	//drivef.turn(10, 800);
	roller.move_velocity(200);
	pros::delay(1000);
	roller.move_velocity(0);
	drivef.move(-500, 1000);
	drivef.heading(0, 0, 2000);
	drivef.turn(-55, 1000);
	intakes(200);
	drivef.stop();
	pros::delay(500);
	drivef.move(1400, 3000);
	drivef.timeDrive(1000, 20, 80);
	drivef.timeDrive(800, 100, 80);
	drivef.twrAlign(2000, 350, 350);
	roller.move_velocity(200);

	


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
