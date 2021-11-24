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
    //Dock(DOWN);
    //pros::delay(600);
    //drivef.move(100, 1000);
    //drivef.drive(100, 10000, lidarFR, lidarFL);
    //Dock(UP);
    //pros::delay(500);
    drivef.pointTurn(45, 1000, ORIGIN_LEFT);
    drivef.driveTurn(1800, 800, 100, 100, 3000);

}