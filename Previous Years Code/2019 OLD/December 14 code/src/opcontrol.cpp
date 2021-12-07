#include "main.h"
#include "tray.h"
#include "drive.h"
#include "intakes.h"
void opcontrol() {
	while(true) {
		//Identify Controller
		partner.print(0, 0, "Brian");
		master.print(0, 0, "Stewie");
		pros::lcd::print(0, "1010 Victory");
		//printf("Ultrasonic: %d \n", rightUltra.get_value());
		//printf("Tray: %d \n", stacky.get_position());
		//Drive
		driveF.OP_Chassis();
		//tray
		cubeTray.opTray();
		//lift
		arm.opLift();
		//intakes
		intake.opintake();
		delay(20);
	}
}
