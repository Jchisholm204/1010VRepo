/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * Copyright (c) 2017-2019, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

/**
 * If defined, some commonly used enums will have preprocessor macros which give
 * a shorter, more convenient naming pattern. If this isn't desired, simply
 * comment the following line out.
 *
 * For instance, E_CONTROLLER_MASTER has a shorter name: CONTROLLER_MASTER.
 * E_CONTROLLER_MASTER is pedantically correct within the PROS styleguide, but
 * not convienent for most student programmers.
 */
#define PROS_USE_SIMPLE_NAMES

/**
 * If defined, C++ literals will be available for use. All literals are in the
 * pros::literals namespace.
 *
 * For instance, you can do `4_mtr = 50` to set motor 4's target velocity to 50
 */
#define PROS_USE_LITERALS
#include "api.h"
#include "Intakes.h"
#include "chassis.h"
#include "lift.h"
#include "tray.h"
//#include "display.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
/**
 * You should add more #includes here
 */
//#include "okapi/api.hpp"
//#include "pros/api_legacy.h"

/**
 * If you find doing pros::Motor() to be tedious and you'd prefer just to do
 * Motor, you can use the namespace with the following commented out line.
 *
 * IMPORTANT: Only the okapi or pros namespace may be used, not both
 * concurrently! The okapi namespace will export all symbols inside the pros
 * namespace.
 */
using namespace pros;
// using namespace pros::literals;
// using namespace okapi;
extern intakeClass intakes;
extern Chassis drivef;
//extern Display cinema;


extern Controller master;
extern Controller partner;
///Motor Definitions
extern Motor driveRF;
extern Motor driveRB;

extern Motor driveLF;
extern Motor driveLB;

extern Motor TrayMotor;
extern Motor ArmMotor;
///////////////////Intakes
extern Motor RightIntake;
extern Motor LeftIntake;
///////////////////Sensors
extern ADIDigitalIn TrayDownLimit;
//extern ADIDigitalIn TrayUpLimit;
extern ADIDigitalIn armLimit;
extern ADIAnalogIn trayPos;
extern ADILineSensor bottom;
extern ADILineSensor top;
extern ADIGyro gyro;
///////////////////////Global Variables
extern int intakeState;
extern int liftState;
extern bool autoRunning;
///////////////DriveTrain Definitions
#define DIRECTION_FORWARD 1
#define DIRECTION_BACK -1
#define DIRECTION_LEFT 1
#define DIRECTION_RIGHT -1
#define R 1
#define L 2
/////////////Tray
extern int TrayAutoTarget;
extern ADIAnalogIn TrayPos;
extern bool TrayZero;

// //////////////////////////display
extern int autoCase;
//////screen objects
//cube sensors
extern lv_obj_t * HighCube;
extern lv_obj_t * LowCube;
//limit switches
extern lv_obj_t * tryLmt;
extern lv_obj_t * armLmt;
//battery persentage
extern lv_obj_t * battery;

/**
 * Prototypes for the competition control tasks are redefined here to ensure
 * that they can be called from user code (i.e. calling autonomous from a
 * button press in opcontrol() for testing purposes).
 */
#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
//#include <iostream>
#endif

#endif  // _PROS_MAIN_H_
