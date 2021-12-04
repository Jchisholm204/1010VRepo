/*  skills.cpp
* Used for everything to do with skills autos:
*/

#include "main.h"
#include "autons.h"
#include "drive.h"
#include "lift.h"
#include "dock.h"
#include "helpers.h"

void skillsAuto(void){

}

void fnTestAuto(void){
    display.Msg("Running: fnTest", 1000);
    pros::delay(1000);
    display.Msg("This auto will test various functions of the robot", 1000);
    pros::delay(1000);

    display.Msg("Testing Piston States: false", 1000);
    lpState = false;
    pros::delay(1000);
    display.Msg("Testing Piston States: true", 1000);
    lpState = true;
    pros::delay(1000);
    display.Msg("Testing Piston States: false", 1000);
    lpState = false;
    pros::delay(1000);

    display.Msg("Running Intakes: (+)", 1000);
    intake(200);
    pros::delay(1000);
    display.Msg("Running Intakes: (-)", 1000);
    intake(-200);
    pros::delay(1000);
    intake(0);

    display.Msg("Testing Dock States: DOWN", 1000);
    Dock(DOWN);
    pros::delay(1000);
    display.Msg("Testing Dock States: UP", 1000);
    Dock(UP);
    pros::delay(1000);
    display.Msg("Testing Dock States: DOWN", 1000);
    Dock(DOWN);
    pros::delay(1000);

    display.Msg("Testing Lift States: DOWN", 1000);
    Lift(DOWN);
    pros::delay(1000);
    display.Msg("Testing Lift States: UP", 1000);
    Lift(UP);
    pros::delay(1000);
    display.Msg("Testing Lift States: DOWN", 1000);
    Lift(DOWN);
    pros::delay(1000);

}