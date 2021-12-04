#ifndef _HELPERS_H_
#define _HELPERS_H_
#include "lift.h"

//also resets - look to dock/lift.cpp for more details
#define DOWN 1

#define UP 0

#define RESET 2

#define START_POS 5

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

//  Main Drive Function
extern void mainDrive(void);

#endif