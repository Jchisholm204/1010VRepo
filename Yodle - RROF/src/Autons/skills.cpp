/*  skills.cpp
* Used for everything to do with skills autos:
*/

#include "main.h"
#include "autons.h"
#include "robot/drive.h"
#include "tasking/lift.h"
#include "tasking/dock.h"
#include "robot/helpers.h"


void skillsAuto(void){
    /*
    Dock(DOWN);
    drivef.flip(Back);
    pros::delay(600);
    //drivef.move(100, 1000);
    drivef.drive(550, 1200);
    Dock(UP);
    pros::delay(500);
    drivef.flip(Front); //finish picking up tower
    //drivef.turn(45, 1200);
    drivef.timeDrive(800, 40, -100); //turn away from platform
    drivef.turnDrive(45, 100, 200, 3000); //turn to face away from near platform wall
    drivef.drive(1000, 3000); // drive away from near platfor wall with lidars to line up with rings
    drivef.turn(90, 1400); //turn towards rings
    */
   drivef.flip(Front);
   drivef.drive(400, 5000);
   drivef.turn(180, 2000);
   drivef.flip(Back);
   drivef.drive(500, 5000);
}