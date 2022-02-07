/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * Copyright (c) 2017-2021, Purdue University ACM SIGBots.
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
#include "ttl/ttl.hpp"
#include "robot/drive.hpp"

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
// using namespace pros;
// using namespace pros::literals;
// using namespace okapi;

extern Chassis drivef;

//PNEUMATICS
extern ttl::ADIPiston LiftPiston;
extern ttl::ADIPiston DockPiston;
extern ttl::ADIPiston SidePiston;

//MOTORS

extern pros::Motor driveRB;
extern pros::Motor driveRM;
extern pros::Motor driveRF;

extern pros::Motor driveLB;
extern pros::Motor driveLM;
extern pros::Motor driveLF;

extern pros::Motor liftMotor;

extern pros::Motor conveyerMotor;

//DISPLAY

extern lv_obj_t * op_tab;
extern lv_obj_t * sys_battery_meter;
extern lv_obj_t * bat_meter_label;

//CONTROLLERS

extern pros::Controller master;
extern pros::Controller partner;


//SENSORS

extern pros::ADIAnalogIn LiftPOT;

extern pros::ADIGyro absGyro; //resets at beginning of match
extern pros::ADIGyro posGyro; //resets upon turning

extern pros::Imu gyro; //imu Gyro

//for driving backwards
extern pros::Distance distFR;
extern pros::Distance distFL;
//for driving forwards
extern pros::Distance distBR;
extern pros::Distance distBL;

extern pros::Vision visBack; //mounted on the back of the robot
extern pros::Vision visFront; //mounted on the front of the robot


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
//Called by VEX Competition
void opcontrol(void);
//Called by User
void operatorControl(void);
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
