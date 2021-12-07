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
**Configure System Tasking*
*/

//////Team Name Configuration//////////////////
static const char* TEAM_ORG = "Ten Ton Robotics";
static const char* TEAM_NAME = "1010V";

//////Auto Configuration///////////////////////

//This will declare auto selections avaible on the brain screen
static const char* autoOptions = "No Auto\nRight";
//Display Auto selection does not work is Use_Screen_Auto_Selection = false

//Define Autos here in numerical order
#define NO_AUTO 0
#define Right_AUTO 1
#define Left_Auto 2

//Used to select a default Auto
static const int RunningAuto = Right_AUTO;//Select an auto from above
//does not work if Use_Screen_Auto_Selection = true

//Set to true to use the display auto selector // False to set auto with "RunningAuto" variable
const bool Use_Screen_Auto_Selection = false;

//////Drive Configuration////////////////////

//Mechanum Wheels -- Set to 1 to Enable
static const int Mechanum_Wheels_Enable = 0;

//////Port Configuration/////////////////////

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

#define MOBO_1_PORT 18 //Side (1-21) (0=undefined)
#define MOBO_2_PORT 3 //Docker mobo (1-21)


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

//////Dock Configuration Values/////////
/*
* Notes about this section:
*   The dock may be used for the dock on Amogo, or alternatively, for some other lift where a PID controller is needed
*   This means that the "dock" function can be used for almost any type of lift provided it uses one (1) motor
*
*   In order for this function to operate properly, there must be a limit switch installed in the MIN (minimum/lowest)
*   position on your dock/arm
*   The limit switch port is configured as "Docker_Endstop_Min_Port" under the "Ports" section of this file
*
*   If you fail to corectly install or configure the limit switch, your robot may break
*   I am not responsible for broken motors/gearboxes
*/

//Dock Maximum Value = Make this where you want the dock to go when it is down
static const int Dock_PID_MaxVal = 480; //440 without elastics // 520 with 2
//Dock Minimun Value = Do NOT mess with this value unless you knwo what you are doing
static const int Dock_PID_MinVal = 0;
//Dock_PID_MinVal should do nothing provided you have a limit switch the dock clicks in its upwards position
//Messing with this value can mess up the docks homing sequence

//Docker Reset Feature - reset dock to default position during opcontrol
const bool Docker_Reset_Feature_Enable = true;

//Dock max movement settings//
// (0) to (127)
static const int DOCK_MAX_UP = -127;
// (0) to (-127)
static const int DOCK_MAX_DOWN = 127;

//Dock PID Settings//
static const float DOCK_PID_KP = 1.2;
static const float DOCK_PID_KD = 1.6;

///Dock Tower Detection -- detects if there is a tower in the dock and slows it down
//very useful for not tipping rings off of towers
const bool Dock_Tower_Detection_Enable = true;
static const int Dock_Tower_Detection_Trigger_Value = 100;
static const int Dock_Tower_Loaded_MAXDOWN = 90;
static const int Dock_Tower_Loaded_MAXUP = -127;

//////Arm Configuration Settings//////////////////////////////////////////////////////////////
//Same as Dock..
static const int Arm_PID_Zero = -5;
static const int Arm_PID_Val_Tower = 400;
static const int Arm_PID_Val_Platform = 450;

static const int ARM_MAX_UP = -127;
static const int ARM_MAX_DOWN = 127;

static const float ARM_PID_KP = 1.2;
static const float ARM_PID_KD = 1.6;


//Arm Task Override
const bool Arm_Task_Override = false;


//////Configure System Tasking//////////////
/*
* This section of the configuration file is used to disable the initalization of the display and docker tasks
* This would only be nessasary to use if you need to free up brain reasources
* The Screen task should never be disabled unless there is a need to replace it with another task
*   If the screen task is disabled, the LCD will fail to function, showing only a black screen
* The dock task may be disabled to conserve system reasources provided your robot does not have a dock or lift of any kind
*/

//Dock Task -- set to true to enable
const bool Dock_Task_Enable = true;

//Dock Task Delay -- set to 20 ms for best results
#define DOCK_TASK_LOOP_DELAY 20

//Display Task -- set to true to enable
const bool Display_Task_Enable = false;

//Display refresh rate -- Set to larger value to save system reasources or smaller value to make screen more responcive
#define DISPLAY_REFRESH_RATE 500 //defined in (ms) delay
//For best results, use values between 20 and 500, values over 500 may become unresponcive, values under will use more processing power

//Main Loop Delay -- set to 20 ms for best results
#define MAIN_LOOP_DELAY 20

//Arm Task - used for the front or side arm
const bool Arm_Task_Enable = true;


//Arm Task Delay -- set to 20 ms for best results
#define ARM_LOOP_DELAY 20

#endif