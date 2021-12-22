/* Ingenuity - operator.cpp
/* - main.h
* All operator control code (drive code) goes here
*/

#include "main.h" //for operatorControl function and controllers
#include "robot/display.h"
#include "robot/drive.hpp"
#include "tasking/pneumatics.hpp"
#include "tasking/lift.hpp"

using namespace pros;

int maxDriveVelocity = 200;

void operatorControl(){

	//DriveBase/////////////////////////////////////////

	//adjust the drive speed based on the joystick position (good for platfom)
	if(partner.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT)){
		maxDriveVelocity += partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
	}
	//set drive to max speed (good for normal drive)
	else if(partner.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)){
		maxDriveVelocity = 200;
	}
	//set the drive to really slow (1/4 max - good for platform)
	else if(partner.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)){
		maxDriveVelocity = 50;
	}
	//half the max drive speed (good for climbing)
	else if(partner.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT)){
		maxDriveVelocity = 100;
	}

	//dont let the drive speed go below 1/8 of Max or Max
	if(maxDriveVelocity>200){
		maxDriveVelocity = 200;
	}
	if(maxDriveVelocity < 25){
		maxDriveVelocity = 25;			
	}

	drivef.operator_Chassis(maxDriveVelocity); //run the operator drive program

	//Dock//////////////////////////////////////////////

	if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)){
		//Dock_Piston_State = !Dock_Piston_State; //toggle the dock
		dockTestPiston.toggle();
	}

	//Intakes//////////////////////////////////////////

	if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){
		intakeMotor.move_velocity(600);
		conveyerMotor.move_velocity(600);
	}
	else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){
		intakeMotor.move_velocity(-200);
		conveyerMotor.move_velocity(-400);
	}
	else{
		intakeMotor.move_velocity(0);
		conveyerMotor.move_velocity(0);
	};

	//Lift//////////////////////////////////////////////////////

	//preset control of lift
	if(partner.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)){
		lift.up();
	}
	else if(partner.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)){
		lift.down();
	}
	
	//manual control of lift
	if(master.get_digital(E_CONTROLLER_DIGITAL_Y)){
		lift.manual(100);
	}
	else if(master.get_digital(E_CONTROLLER_DIGITAL_A)){
		lift.manual(-100);
	}

}