#ifndef _SETUP_H_
#define _SETUP_H_
/*///SETUP FILE///
*Please Read through this file before continuing:
*It is used to configure almost every aspect of the robot
*
*USED TO: (Not in Order)
**Declare ports
**Set Team Name
**Set Program Name
**Configure Auto Selections
**Select Autos
**Reverse Motors
*/

//////Team Name Configuration//////////////////
static const char* TEAM_ORG = "Ten Ton Robotics";
static const char* TEAM_NAME = "1010V";

//////Auto Configuration///////////////////////

//This will declare auto selections avaible on the brain screen
static const char* autoOptions = "No Auto\nTest\nExample";
//Auto Selection through the brain screen is currenly unavalible

//Define Autos here in numerical order
#define NO_AUTO 0
#define TEST_AUTO 1
#define EXAMPLE_AUTO 2

//Used to select a default Auto
static const int RunningAuto = NO_AUTO;//Select an auto from above

//////Drive Configuration////////////////////

//Mechanum Wheels -- Set to 1 to Enable
static const int Mechanum_Wheels_Enable = 0

//////Port Configuration/////////////////////

//Gyro should be installed somewhere close to the center of the robot
#define GYRO_PORT 0 //0=undefined, (1-21)
//Docker Min Limit Switch/Bumper/Endstop should be installed such that the dock clicks it when it comes up
#define Docker_Endstop_Min_Port 1 //1-8 ('A'-'H')

#define driveRB_PORT 20 //(1-21)
#define driveRF_PORT 19 //(1-21)
#define driveLB_PORT 16 //(1-21)
#define driveLF_PORT 17 //(1-21)

#define CONVEYER_PORT 7 //(1-21)
#define INTAKE_PORT 6 //(1-21)

#define MOBO_1_PORT 0 //Docker (1-21) (0=undefined)
#define MOBO_2_PORT 5 //Side mobo (1-21)



//////Motor Configuration////////////////

#define INTAKE_REVERSED true
#define CONVEYER_REVERSED true

#define MOBO_1_REVERSED false //Docker Reversed?
#define MOBO_2_REVERSED false //Side Mobo Reversed?



//////De_Sync Configuration/////////////
#define ON true
#define OFF false
/*
Desync allows the driver to termpoarily disable either the
Conveyer or the Intake motors

Buttom must be held down in order for DeSync to occur
Buttons are currently UP arrow and X key on the controller
Buttons can be adjusted in main.cpp opcontrol
*/

//Allows the Conveyer motor to be stopped
const bool Conveyer_DeSync_Enable = ON;
//Allows the Intake motor to Be stopped
const bool Intake_DeSync_Enable = ON;

////Dock Maximum/Mimimum PID Values/////////
//Dock Maximum Value = Make this where you want the dock to go when it is down
static const int Dock_PID_MaxVal = 500;
//Dock Minimun Value = Do NOT mess with this value unless you knwo what you are doing
static const int Dock_PID_MinVal = 0;
//Dock_PID_MinVal should do nothing provided you have a limit switch the dock clicks in its upwards position
//Messing with this value can mess up the docks homing sequence

#endif