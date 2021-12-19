#include "main.h"
#include "robot/helpers.h"
#include "robot/drive.h"
#include "tasking/dock.h"
#include "tasking/lift.h"



void mainDrive(void){
	bool Once;

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
		lift_state_prev = 9;
	}
	else if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)){
		Lift(UP);
		lift_state_prev = 9;
	}
	
	if(master.get_digital(E_CONTROLLER_DIGITAL_Y)){
		lift_manual_exemption = true;
		liftMotor.move_velocity(80);
		Once = false;
	}
	else if(master.get_digital(E_CONTROLLER_DIGITAL_A) && Lift_POT.get_value() < 3900){
		lift_manual_exemption = true;
		liftMotor.move_velocity(-80);
		Once = false;
	}/*
	else if((master.get_digital(E_CONTROLLER_DIGITAL_A) != 1 && master.get_digital(E_CONTROLLER_DIGITAL_Y) != 1) && Once == false){
		Once = true;
		liftMotor.move_velocity(0);
		lift_manual_exemption = false;
	}*/
	else{
		lift_manual_exemption = false;
	}
}