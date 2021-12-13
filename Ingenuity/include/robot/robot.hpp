//Ingenuity - robot.hpp
#ifndef _ROBOT_HPP_
#define _ROBOT_HPP_

#include "main.h"

//SENSORS
extern pros::ADIGyro gyroAbs; //ADI Gyro // Used for absolute positioning based on the starting position of the robot
extern pros::ADIGyro gyroHead; //ADI Gyro // Used for turning from the robots current position
extern pros::ADIDigitalIn Docker_Endstop_Min; //ADI Limit Switch // For docker homing
extern pros::ADIAnalogIn Lift_POT; //ADI Potentiometer // For lift vertical positioning

extern pros::Imu imu; //

extern pros::Distance lidarFR;
extern pros::Distance lidarFL;
extern pros::Distance lidarBR;
extern pros::Distance lidarBL;

//MOTORS
extern pros::Motor driveRB;
extern pros::Motor driveRF;
extern pros::Motor driveLB;
extern pros::Motor driveLF;

extern pros::Motor dockerMotor;
extern pros::Motor liftMotor;

extern pros::Motor intakeMotor;
extern pros::Motor conveyerMotor;

//DISPLAY
extern lv_obj_t * op_tab;
extern lv_obj_t * sys_battery_meter;
extern lv_obj_t * bat_meter_label;

//CONTROLLERS
extern pros::Controller master;
extern pros::Controller parter;


//INITIALIZE FUNCTIONS
void robotInit(void);

void set_BrakeModes(void);



#endif