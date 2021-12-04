#include "main.h"
#include "helpers.h"
#include "drive.h"
#include "dock.h"
#include "lift.h"

bool Once;

void mainDrive(void){

//DriveBase/////////////////////////////////////////
	drivef.operator_Chassis();

//Dock//////////////////////////////////////////////
	if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)){
		Dock(UP);
		dock_state_prev = 9;
	}
	else if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)){
		Dock(DOWN);
		dock_state_prev = 9;
	}
	if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){
		dock_manual_exemption = true;
		dockerMotor.move_velocity(80);
	}
	else if(master.get_digital(E_CONTROLLER_DIGITAL_L2)){
		dock_manual_exemption = true;
		dockerMotor.move_velocity(-80);
	}
	else{
		dock_manual_exemption = false;
	}

//Intakes//////////////////////////////////////////
	if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){
		intakeMotor.move_velocity(200);
		conveyerMotor.move_velocity(200);
	}
	else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){
		intakeMotor.move_velocity(-200);
		conveyerMotor.move_velocity(-200);
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

	//lift piston toggle
	if(master.get_digital(E_CONTROLLER_DIGITAL_LEFT) && lpState == false){
		lpState = true;
	}

	if(master.get_digital(E_CONTROLLER_DIGITAL_LEFT) && lpState == true){
		lpState = false;
	}

	if(master.get_digital(E_CONTROLLER_DIGITAL_Y)){
		lift_manual_exemption = true;
		liftMotor.move_velocity(80);
		Once = false;
	}
	else if(master.get_digital(E_CONTROLLER_DIGITAL_A)){
		lift_manual_exemption = true;
		liftMotor.move_velocity(-80);
		Once = false;
	}
	else if((master.get_digital(E_CONTROLLER_DIGITAL_A) != 1 && master.get_digital(E_CONTROLLER_DIGITAL_Y) != 1) && Once == false){
		Once = true;
		liftMotor.move_velocity(0);
		lift_manual_exemption = false;
	}
	else{
		lift_manual_exemption = false;
	}
}