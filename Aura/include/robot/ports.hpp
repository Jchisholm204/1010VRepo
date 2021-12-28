/**
 * @file robot/ports.hpp 
 * 
 * Aura  -  ports.hpp
 * 
 * Header File Containing Motor and Sensor Ports
 * 
 */
#ifndef _PORTS_HPP_
#define _PORTS_HPP_


//pnumatic controllers
#define LIFT_PISTON_PORT 0
#define DOCK_PISTON_PORT 0
#define SIDE_PISTON_PORT 0


//#SENSORS#

//Gyro should be installed somewhere close to the center of the robot
#define GYRO_PORT 15 // (1-21)

//Min Limit Switch/Bumper/Endstop should be installed such that the dock/arm clicks it when it comes up
#define Docker_Endstop_Min_PORT 1

#define Lift_POT_PORT 2

#define VISION_SENSOR_PORT 21
#define VISION_BACK_PORT 0
#define VISION_FRONT_PORT 0

#define GYRO_ABS_PORT 3
#define GYRO_POS_PORT 4

//Lidars (Distance Sensors)//
#define FL_LIDAR_PORT 0
#define FR_LIDAR_PORT 1 

#define BL_LIDAR_PORT 6
#define BR_LIDAR_PORT 8

//#MOTORS#
#define driveRB_PORT 10
#define driveRF_PORT 9
#define driveLB_PORT 16
#define driveLF_PORT 11

#define CONVEYER_MOTOR_PORT 13

#define LIFT_MOTOR_PORT_L 17
#define LIFT_MOTOR_PORT_R 33

#define DOCKER_MOTOR_PORT 3


#endif