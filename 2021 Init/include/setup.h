#ifndef _PORTS_H_
#define _PORTS_H_

extern const std::string TEAM_NAME;

#define GYRO_PORT 0
#define Docker_Endstop_Min_Port 1

#define driveRB_PORT 20
#define driveRF_PORT 19
#define driveLB_PORT 16
#define driveLF_PORT 17

#define CONVEYER_PORT 7
#define INTAKE_PORT 6

#define INTAKE_REVERSED true
#define CONVEYER_REVERSED true

#define MOBO_1_PORT 0 //Docker
#define MOBO_2_PORT 5 //Side mobo

#define MOBO_1_REVERSED false //Docker Reversed?
#define MOBO_2_REVERSED false //Side Mobo Reversed?

#endif