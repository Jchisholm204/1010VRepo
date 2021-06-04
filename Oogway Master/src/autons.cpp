#include "main.h"
#include "autons.h"
#include "drive.h"
#include "exr.h"

void intakes(int vel){//hi
	intakeL.move_velocity(-vel);
	intakeR.move_velocity(-vel);
}

void skills(){
}
void sadAuto(){
	flyWheel.move_velocity(600);
	pros::delay(500);
	roller.move_velocity(200);	
}
void leftAuto(){
	flyWheel.move_velocity(470);
	pros::delay(200);
	roller.move_velocity(200);
	pros::delay(1300);
	roller.move_velocity(0);
	drivef.move(-950, 1500);
	drivef.turn(115, 1200);
	pros::delay(150);
	intakes(100);
	drivef.move(600, 1200);
	intakes(200);
	drivef.move(150, 1000);
	intakes(200);
	flyWheel.move_velocity(570);
	roller.move_velocity(200);
	pros::delay(1200);
	intakes(0);
	pros::delay(500);
	//drivef.time(800, 50);
	//intakes(0);
	roller.move_velocity(0);
	drivef.move(-400, 1000);
}
void rightAuto(){
	flyWheel.move_velocity(470);
	pros::delay(200);
	roller.move_velocity(200);
	pros::delay(1300);
	roller.move_velocity(0);
	drivef.move(-950, 1500);
	drivef.turn(-115, 1200);
	pros::delay(150);
	intakes(100);
	drivef.move(600, 1200);
	intakes(200);
	drivef.move(150, 1000);
	intakes(200);
	flyWheel.move_velocity(570);
	roller.move_velocity(200);
	pros::delay(1200);
	intakes(0);
	pros::delay(500);
	//drivef.time(800, 50);
	//intakes(0);
	roller.move_velocity(0);
	drivef.move(-400, 1000);
	
}