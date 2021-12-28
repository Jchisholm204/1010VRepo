#ifndef _AUTOS_HPP_
#define _AUTOS_HPP_
#include "api.h"

//Autons as given on the brain screen

#define NO_AUTO 0
#define RIGHT_AUTO 1
#define LEFT_AUTO 2
#define SKILLS_NORM_AUTO 3
#define SKILLS_RR_AUTO 4
#define TEST_AUTO 5


//Skills Norm Auto
extern void skillsAuto(void);

/**
 * @brief ReRun Motor Velociy Calculator
 * 
 * @param motor The Motor to calculate the velocity for
 * 
 * @param percent_actual 0.4 percent_actual = 40% actual + 60% target (velocities)
 * 
 * @return float - calculated velocity
 */
extern int VelocityCalc(pros::Motor motor, float percent_actual = 0.5);

/**
 * @brief Playback of ReRun Style Autons
 * @param reRunFile The Auto to Run
 * @return 1
 */
int reRunAuto(int reRunFile);

/**
 * @brief Full OpControl for Recording of ReRun Autos
 * @param reRunFile The Auto slot to record to
 * @param recording_disabled
 * @param allottedTime The time that the program will record for
 */
int recordAuto(int reRunFile, bool recording_disabled, int allottedTime);


#endif