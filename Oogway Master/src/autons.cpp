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
	int turnDir;
	if(autoPot.get_value() < 2000){
		turnDir = 50;
	}
	else if(autoPot.get_value() > 2000){
		turnDir = -50;
	}
	drivef.drive(1200, 5000);
	drivef.turn(turnDir, 4500);
	flyWheel.move_velocity(600);
	//drivef.time(800, 120);
	drivef.move(100, 5000);
	roller.move_velocity(200);
}
void leftAuto(){
	flyWheel.move_velocity(470);
	pros::delay(200);
	roller.move_velocity(200);
	pros::delay(1300);
	roller.move_velocity(0);
	drivef.move(-1000, 1800);
	drivef.turn(115, 1200);
	pros::delay(150);
	intakes(120);
	drivef.move(600, 1200);
	intakes(200);

	drivef.move(150, 1000);
	drivef.twrAlign(1000, 280, 410);

	intakes(200);
	flyWheel.move_velocity(570);
	roller.move_velocity(200);
	cycle(2);
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
	drivef.turn(-110, 1200);
	pros::delay(150);
	intakes(120);
	drivef.move(600, 1200);
	intakes(200);

	//drivef.move(150, 1000); //move into the tower and prepare to cycle
	drivef.twrAlign(1000, 410, 280);

	intakes(200);
	flyWheel.move_velocity(570);
	roller.move_velocity(200);
	//pros::delay(1000);
	cycle(2);
	//pros::delay(500);
	roller.move_velocity(0);
	drivef.move(-400, 1000);
	
}
void rightFront(){
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
	pros::delay(1000);
	flyWheel.move_velocity(-10);
	roller.move_velocity(100);
	//drivef.time(800, 50);
	//intakes(0);
	drivef.move(-400, 1000);
	drivef.turn(180, 2000);
	drivef.move(400, 1000);

}
void leftFront(){

}