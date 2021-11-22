#include "main.h"
#include "helpers.h"
#include "drive.h"
#include "dock.h"
#include "lift.h"



void mainDrive(void){

//DriveBase/////////////////////////////////////////
	drivef.operator_Chassis();

//Dock//////////////////////////////////////////////
	if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){
		Dock(UP);
	}
	else if (master.get_digital(E_CONTROLLER_DIGITAL_L2)){
		Dock(DOWN);
	}

//Intakes//////////////////////////////////////////
	if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){
		intakeMotor.move_velocity(600);
		conveyerMotor.move_velocity(600);
	}
	else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){
		intakeMotor.move_velocity(-400);
		conveyerMotor.move_velocity(-400);
	}
	else{
		intakeMotor.move_velocity(0);
		conveyerMotor.move_velocity(0);
	};

//Lift//////////////////////////////////////////////////////
	if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
		Lift(DOWN);
	}
	else if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)){
		Lift(UP);
	}
	else if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)){
		Lift(TOWER);
	}
}