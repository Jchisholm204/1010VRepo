#include "main.h"
#include "autons.h"
#include "drive.h"

void intakes(int vel){//hi
	intakeL.move_velocity(-vel);
	intakeR.move_velocity(-vel);
}

void skills(){
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
	drivef.move(-800, 1500);
	drivef.turn(-125, 1000);
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
	drivef.twrAlign(2000, 370, 300);
	//intakes(0);
	roller.move_velocity(200);
}