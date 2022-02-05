//Ingenuity - ports.hpp
#ifndef _PORTS_HPP_
#define _PORTS_HPP_


//pnumatic controllers
#define LIFT_PISTON_PORT 0
#define DOCK_PISTON_PORT 0
#define SIDE_PISTON_PORT 0


//#SENSORS#

//Gyro should be installed somewhere close to the center of the robot
#define GYRO_PORT 0 // (1-21)

#define Lift_POT_PORT 0

//Vision Ports
#define VISION_BACK_PORT 0
#define VISION_FRONT_PORT 0

//ADI Gyro Ports (redundant / used because PROS broke Inertial Sensors)
#define GYRO_ABS_PORT 0
#define GYRO_POS_PORT 0

//Lidars (Distance Sensors)//
#define FL_LIDAR_PORT 0
#define FR_LIDAR_PORT 0

#define BL_LIDAR_PORT 0
#define BR_LIDAR_PORT 0

//#MOTORS#
#define driveRB_PORT 0
#define driveRM_PORT 0
#define driveRF_PORT 9

#define driveLB_PORT 0
#define driveLM_PORT 0
#define driveLF_PORT 0

#define CONVEYER_PORT 0

#define LIFT_PORT 0


#endif