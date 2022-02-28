#ifndef _RERUN_HPP_
#define _RERUN_HPP_
#include "api.h"

/**
 * ReRun .hpp
 * 
 * @author Jchisholm204
 * @copyright Jchisholm204 | 1010V | Ten Ton Robotics Academy
 * 
 * ReRun Autonomous Recording and Playback:
 * 
 * ABOUT:
 * ReRun is, at its base, a simple program that records a value at a given timestamp,
 * and then returns that same value at the same timestamp.
 * 
 * How it Works:
 * When the Recording option is enabled through the V5 Onboard Display, The Program starts recording motor velocities,
 * PID Targets, Piston States, and a few other things.  This continues for either 15, or 60 seconds, depending on what
 * auto is selected on the brains screen. Once Recording has finished, the program automaticaly disables driver input,
 * and further recording.
 * 
 * The Robot can then be put into autonomous mode.  When in autonomous mode, the program reads from the previously recorded
 * data, and applies the data into closed loop velocity controllers, PID Targetvalues, and piston states in order to essencially
 * recreate the exact movements of the robot during the recording period.
 * 
 * 
 * ReRun is an extremely useful program as it allows us to almost instantaniously make our autonomous programs.
 */

//ReRun Motor Velocity Calculator - returns float
//(motor, percent_actual) // percent_actual = 0.5 default
//0.4 percent_actual = 40% actual + 60% target (velocities)
// 0 percent_actual = use target velocity only
extern int VelocityCalc(pros::Motor motor, float percent_actual = 0.5);

// Playback of ReRun Autos
int reRunAuto(int reRunFile);

// Full OpControl for Recording of ReRun Autos
int recordAuto(int reRunFile, bool recording_disabled, int allottedTime);


#endif