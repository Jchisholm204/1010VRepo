#ifndef _AUTOS_HPP_
#define _AUTOS_HPP_
#include "api.h"

extern void skillsAuto(void);

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