//Ingenuity - ports.hpp
#ifndef _PORTS_H_
#define _PORTS_H_


//pnumatic controller port for lift claw
#define LIFT_INTAKE_PORT 3

//#SENSORS#

//Gyro should be installed somewhere close to the center of the robot
#define GYRO_PORT 15 // (1-21)

//Min Limit Switch/Bumper/Endstop should be installed such that the dock/arm clicks it when it comes up
#define Docker_Endstop_Min_PORT 1

#define Lift_POT_PORT 2


#define GYRO_ABS_PORT 3
#define GYRO_HEAD_PORT 4

//Lidars (Distance Sensors)//
#define FL_LIDAR_PORT 21
#define FR_LIDAR_PORT 1 

#define BL_LIDAR_PORT 6
#define BR_LIDAR_PORT 8

//#MOTORS#
#define driveRB_PORT 10
#define driveRF_PORT 9
#define driveLB_PORT 16
#define driveLF_PORT 11

#define CONVEYER_PORT 13
#define INTAKE_PORT 12

#define LIFT_PORT 17
#define DOCKER_PORT 3


#endif