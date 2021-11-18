#ifndef _HELPERS_H_
#define _HELPERS_H_
#include "lift.h"

//also resets - look to dock/lift.cpp for more details
#define DOWN 0

#define UP 1

#define RESET 2

//Spin the intakes with a given velocity (max 600)
//Desync - Only spin the conveyer motor
extern void intake(int velocity, bool desync = false);

/*Adjust the current dock state:
*Possible values:
**DOWN = 0
**UP = 1
**RESET = 2*/
extern void Dock(int state);

/*Adjust the current front lift state:
*Possible values:
**DOWN = 0
**UP = 1*/
extern void Lift(int Liftstate);

//3D Printer Style Homing for lifts
extern int home_tare(pros::Motor motor, pros::ADIDigitalIn limit_switch, int homeSpeed);

//ReRun Motor Velocity Calculator - returns float
//(motor, percent_actual) // percent_actual = 0.5 default
//0.4 percent_actual = 40% actual + 60% target (velocities)
// 0 percent_actual = use target velocity only
extern int VelocityCalc(pros::Motor motor, int percent_actual = 0.5);

//  Main Drive Function
extern void mainDrive(void);

#endif