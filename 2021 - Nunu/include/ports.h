#ifndef _PORTS_H_
#define _PORTS_H_
//////Port Configuration/////////////////////

//pnumatic controller port for lift claw
#define LIFT_INTAKE_PORT 3
//Gyro should be installed somewhere close to the center of the robot
#define GYRO_PORT 17 //0=undefined, (1-21)
//Min Limit Switch/Bumper/Endstop should be installed such that the dock/arm clicks it when it comes up
#define Docker_Endstop_Min_Port 1 //1-8 ('A'-'H')
#define Arm_Endstop_Min_Port 2 //1-8 ('A'-'H')
//Docker Tower Detection Sensor (Optical)
#define Docker_Optical_Port 1 //(1-21)

//Lidars (Distance Sensors)//
#define FL_LIDAR_PORT 20 //(1-21)
#define FR_LIDAR_PORT 21 //(1-21)

#define BL_LIDAR_PORT 6 //(1-21)
#define BR_LIDAR_PORT 8 //(1-21)

//Motors
#define driveRB_PORT 10 //(1-21)
#define driveRF_PORT 9 //(1-21)
#define driveLB_PORT 16 //(1-21)
#define driveLF_PORT 11 //(1-21)

#define CONVEYER_PORT 15 //(1-21)
#define INTAKE_PORT 12 //(1-21)

#define LIFT_PORT 18 //Side (1-21) (0=undefined)
#define DOCKER_PORT 3 //Docker mobo (1-21)


//////Motor Configuration////////////////

#define INTAKE_REVERSED true
#define CONVEYER_REVERSED true

#define MOBO_1_REVERSED false //Docker Reversed?
#define MOBO_2_REVERSED false //Side Mobo Reversed?

#endif