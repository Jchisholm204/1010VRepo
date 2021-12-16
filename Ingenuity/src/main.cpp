/* Ingenuity - main.cpp
/* - main.h
* Main File Containing all nessasary calls to operations
*/
#include "main.h"
#include "robot/display.h"
#include "robot/drive.hpp"
#include "robot/ports.hpp"

//	CONTROLLERS
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

//	Define the Motors - Drive
pros::Motor driveRB(driveRB_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveRF(driveRF_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLB(driveLB_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLF(driveLF_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

//	Define the Motors - Conveyer and Intake
pros::Motor intakeMotor(INTAKE_PORT, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor conveyerMotor(CONVEYER_PORT, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

//	Define the Motors - Mobile Goal Pickups (MOBO)
pros::Motor liftMotor(LIFT_PORT, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor dockerMotor(DOCKER_PORT, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

//	Sensors
pros::ADIGyro posGyro(GYRO_POS_PORT);
pros::ADIGyro absGyro(GYRO_ABS_PORT);
pros::Imu gyro(GYRO_PORT);
pros::ADIDigitalIn Docker_Endstop_Min(Docker_Endstop_Min_PORT);
pros::ADIAnalogIn Lift_POT(Lift_POT_PORT);
pros::Distance lidarFL(FL_LIDAR_PORT);
pros::Distance lidarFR(FR_LIDAR_PORT);
pros::Distance lidarBL(BL_LIDAR_PORT);
pros::Distance lidarBR(BR_LIDAR_PORT);

void initialize() {


}


void disabled() {
	
}


void competition_initialize() {}


void autonomous() {

}


void opcontrol() {

}
