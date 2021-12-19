#include "main.h"
#include "ReRun.hpp"

ttl::ReRun controller;

pros::Motor driveRB(1);

void ttl::ReRun::imu(){
	pros::Motor m1 = driveRB;
}

void initialize() {
}

void disabled() {}


void competition_initialize() {}

void autonomous() {}


void opcontrol() {

	while (true) {
		pros::delay(20);
	}
}
