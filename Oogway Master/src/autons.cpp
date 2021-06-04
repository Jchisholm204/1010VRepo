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
	drivef.move(-800, 1500);
	drivef.turn(125, 1000);
	pros::delay(150);
	drivef.move(600, 1500);
	intakes(200);
	roller.move_velocity(100);
	pros::delay(1800);
	intakes(-200);
	roller.move_velocity(0);
	pros::delay(1100);
	intakes(0);
	//drivef.time(800, 50);
	drivef.twrAlign(2000, 300, 370);
	intakes(0);
	roller.move_velocity(200);
}
void rightAuto(){
	flyWheel.move_velocity(470);
	pros::delay(200);
	roller.move_velocity(200);
	pros::delay(1300);
	roller.move_velocity(0);
	drivef.move(-950, 1500);
	drivef.turn(-125, 1200);
	pros::delay(150);
	intakes(80);
	drivef.move(450, 1200);
	intakes(200);
	roller.move_velocity(100);
	pros::delay(1800);
	roller.move_velocity(0);
	pros::delay(1100);
	//drivef.time(800, 50);
	drivef.twrAlign(2000, 370, 300);
	//intakes(0);
	roller.move_velocity(200);
}