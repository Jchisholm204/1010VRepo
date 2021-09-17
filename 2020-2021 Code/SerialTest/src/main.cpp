#include "main.h"

void initialize() {}
void disabled() {}
void competition_initialize() {}
void autonomous() {}
void opcontrol() {
	int hi = 0;
	int bye = 0;
	pros::Motor moro = pros::Motor(1);
	while (true) {
		std::cin >> hi;
		std::cout << hi;
		moro.move(hi);
		pros::delay(20);
	}
}
