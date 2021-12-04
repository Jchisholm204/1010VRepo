#ifndef _AUTONS_H_
#define _AUTONS_H_

extern void skillsAuto(void);

//exit codes
#define EXIT_CODE_SUCCESS 2
#define EXIT_CODE_ERROR 1
#define EXIT_CODE_0 0
#define EXIT_CODE_DONE 0

//ReRun Motor Velocity Calculator - returns int
//(motor, percent_actual) // percent_actual = 0.5 default
//0.4 percent_actual = 40% actual + 60% target (velocities)
// 0 percent_actual = use target velocity only
extern int VelocityCalc(pros::Motor motor, float percent_actual = 0.5);

// Playback of ReRun Autos
int reRunAuto(int reRunFile);

// Full OpControl for Recording of ReRun Autos
int recordAuto(int reRunFile, bool recording_disabled, int allottedTime);

#endif