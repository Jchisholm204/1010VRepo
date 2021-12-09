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
   Dock(DOWN);
   pros::delay(1000);
   drivef.move(-450, 1000, true);
   Dock(UP);
   pros::delay(1000);
   drivef.move(500, 1000, true);
   drivef.turn(100, 3000);
   //drivef.time(500, -100);
   drivef.flip(Front);
   //drivef.drive(500, 3000, true);
   Lift(UP);
   intake(600);
   drivef.move(1150, 3000, true);
   drivef.turn(90, 2000);
   //drivef.move(1500, 1500, true);
   drivef.driveTurn(1700, 30, 1700, 30, 8500, true);
   Lift(DOWN);
   drivef.move(-200, 900, true);
   drivef.turn(-90, 2000);
   //drivef.move(300, 1500, true);
   drivef.time(1600, 50);
   intake(0);
   Lift(UP);

   pros::delay(1000);

   drivef.turn(-45, 3000);
   drivef.move(1400, 4000, true);
   drivef.turn(-20, 2000);
   Dock(DOWN); //drop first ring goal
   drivef.move(500, 1000);
   drivef.turn(65, 3000);
   Lift(DOWN);


}