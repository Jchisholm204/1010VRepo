/* Ingenuity - operator.cpp
/* - main.h
* All operator control code (drive code) goes here
*/

#include "main.h" //for operatorControl function and controllers
#include "ttl/ttl.hpp"
#include "robot/drive.hpp"
#include "robot/lift.hpp"

using namespace pros;

int maxDriveVelocity = 200; //The Maxiumum Velocity the Drivebase can move

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
	if(partner.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)){
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

	//dont let the drive speed go below 1/8 of Max or above Max
	if(maxDriveVelocity>200){
		maxDriveVelocity = 200;
	}
	if(maxDriveVelocity < 25){
		maxDriveVelocity = 25;			
	}

	drivef.operator_Chassis(maxDriveVelocity); //run the operator drive program

	//Dock//////////////////////////////////////////////

	if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){
		DockPiston.toggle(); //toggle the dock
	}

	//Conveyor//////////////////////////////////////////

	if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){
		conveyerMotor.move_velocity(600);
	}
	else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){
		conveyerMotor.move_velocity(-200);
	}
	else{
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
	if(partner.get_digital(E_CONTROLLER_DIGITAL_Y)){
		lift.manual(100);
	}
	else if(partner.get_digital(E_CONTROLLER_DIGITAL_A)){
		lift.manual(-100);
	}

	//Control of Lift Pneumatic
	if(partner.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)){
		DockPiston.set_state(LOW);
	}
	else if(partner.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)){
		DockPiston.set_state(HIGH);
	}

}