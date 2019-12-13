/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * Copyright (c) 2017-2018, Purdue University ACM SIGBots.
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
#include "pros/apix.h"
#include "drive.h"
#include "tray.h"
#include "lift.h"
#include "intakes.h"

/**
 * You should add more #includes here
 */
#include "okapi/api.hpp"
//#include "pros/api_legacy.h"
/**
 * If you find doing pros::Motor() to be tedious and you'd prefer just to do
 * Motor, you can use the namespace with the following commented out line.
 *
 * IMPORTANT: Only the okapi or pros namespace may be used, not both
 * concurrently! The okapi namespace will export all symbols inside the pros
 * namespace.
 */using namespace pros;
 //using namespace pros::literals;
// using namespace okapi;

//Diagnostics
#define INTAKE_OVERHEATING 5

#define DIRECTION_FORWARD 1
#define DIRECTION_BACK -1
#define DIRECTION_LEFT 1
#define DIRECTION_RIGHT -1

#define LOWTOWER 500 //430
#define MIDTOWER 580 //580
#define MAXDOWN -100
#define MAXUP 90
#define STACKING_POS 250
#define TRAYUP 550, 60
#define R 1
#define L 2
extern int diagnosticsCase;
extern Chassis driveF;
extern Tray cubeTray;
extern RobotLift arm;
extern Intake intake;

extern int currentLiftPreset;
extern int startingPOS;
extern bool outTake;

extern Controller master;
extern Controller partner;

extern Motor driveLF;
extern Motor driveLB;

extern Motor driveRF;
extern Motor driveRB;

extern Motor ChassisMotors[4];

extern Motor lifty;
extern Motor stacky;

extern Motor leftSuck;
extern Motor rightSuck;

extern Vision visionBOI;

extern ADIUltrasonic leftUltra;
extern ADIUltrasonic rightUltra;

extern ADIGyro gyro;

extern ADIPotentiometer liftyPent;
extern ADIDigitalIn stackyPent;
extern ADIDigitalIn downis;
extern ADIDigitalIn boistop;

extern bool toggled;
extern bool off;
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
