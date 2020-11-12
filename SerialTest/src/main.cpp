#include "main.h"

void initialize() {}
void disabled() {}
void competition_initialize() {}
void autonomous() {}
void opcontrol() {
	int hi = 0;
	while (true) {
		std::cin >> hi;
		std::cout << hi << std::endl;
		pros::delay(20);
	}
}
