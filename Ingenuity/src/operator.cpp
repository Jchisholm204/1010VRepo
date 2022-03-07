/* Ingenuity - operator.cpp
/* - main.h
* All operator control code (drive code) goes here
*/

/** IMPORTANT:
 * Do NOT assign anything to the master controllers down button
 * That button is reserved for ending the rerun recording early
 * 
 * The Button Can ONLY be assigned to something if it is unassigned from the rerun program,
 * In which case, you should delete this comment
 */ 

#include "main.h" //for operatorControl function and controllers
#include "ttl/ttl.hpp"
#include "robot/drive.hpp"
#include "robot/lift.hpp"
#include "Constants.hpp"

using namespace pros;

int maxDriveVelocity = 200; //The Maxiumum Velocity the Drivebase can move
bool conveyerON = false;
bool slowDriveON = false;

void operatorControl(){

	/**
	 * Drive Base Maximum Speed Control:
	 * 
	 * Used in order to slow robot when balancing on Platform,
	 * Used In addition to Expo Controller for additional accuracy
	 * 
	 * IMPORTANT:
	 * This Code was set up using a Closed Loop Velocity Limiter,
	 * This was done to allow the full power (torque) of the motor to be enabled,
	 * while still limiting the maximum speed of the motor.
	 * 
	 * The same results can be acheived with the use of a voltage limiter,
	 * However, if a vlimiter is used, the motors will have reduced torque as well.
	 * (The torque reduction will be mostly porportional to the speed reduction)
	 */

	//set drive to max speed (good for normal drive)
	if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)){
		slowDriveON = !slowDriveON;
	}

	//set the drive to really slow (3/8 max - good for platform)
	if(slowDriveON){
		maxDriveVelocity = kOperator::SlowDrive_Velocity;
	}
	else{
		maxDriveVelocity = kOperator::MaximumDrive_Velocity;
	}
	
	if(partner.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)){
		maxDriveVelocity = kOperator::MaximumDrive_Velocity;
	}
	else if(partner.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)){
		maxDriveVelocity = kOperator::SlowDrive_Velocity;
	}

	drivef.operator_Chassis(maxDriveVelocity); //run the operator drive program

	//Dock//////////////////////////////////////////////

	if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
		DockPiston.toggle(); //toggle the dock
	}
	if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)){
		LiftPiston.toggle();
	}

	//Conveyor//////////////////////////////////////////

	if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)){
		conveyerON = !conveyerON;
	}


	if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){
		conveyerON = false;
		conveyerMotor.move_velocity(-200);
	}
	else if(conveyerON){
		conveyerMotor.move_velocity(600);
	}
	else{
		conveyerMotor.move_velocity(0);
	}

	//Lift//////////////////////////////////////////////////////

	//Manual Control Of Lift
	if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){
		lift.manual(kOperator::Lift_Velocity);
	}
	else if(master.get_digital(E_CONTROLLER_DIGITAL_L2)){
		lift.manual(-kOperator::Lift_Velocity);
	}
	// Left Trigger Scuff Out Button
	if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)){
		lift.down();
	}

}