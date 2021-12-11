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
   drivef.turn(100, 1200);
   //drivef.time(500, -100);
   drivef.flip(Front);
   //drivef.drive(500, 3000, true);
   Lift(UP);
   intake(600);
   drivef.move(1165, 3000, true);
   drivef.turn(90, 2000);
   //drivef.move(1500, 1500, true);
   drivef.driveTurn(1700, 30, 1700, 30, 8500, true);
   Lift(DOWN);
   drivef.move(-190, 1200, true);
   drivef.turn(-92, 2000);
   //drivef.heading(/*heading*/90, /*offsett 10 deg because it starts slanted*/10, 2000); //turns 100*
   //drivef.move(300, 1500, true);
   drivef.time(1800, 140);
   drivef.stop();
   pros::delay(100);
   intake(0);
   //Lift(UP);

   pros::delay(1000);

   //drivef.pid(-50, 50, 2000, 0.7, 0.4);
   drivef.driveTurn(-220, 120, -220, 120, 1500, true);
   drivef.turn(-50, 3000);
   //drivef.heading(45, 10, 2000);
   
   drivef.move(1600, 4000, true);
   //drivef.turn(-10, 2000);
   Dock(DOWN); //drop first ring goal
   pros::delay(2000);

   drivef.move(400, 2000, true);
   //drivef.turn(30, 1500);
   //Lift(DOWN);
   //pros::delay(2000); //the last thing u tested u removed this

   //drivef.move(-250, 1500, false);
   //drivef.turn(90, 2500);

   reRunAuto(3); //run driveback
   drivef.pid(500, 100, 5000, 1.4, 6.5); //drive up on platform

   
//u didnt test this yet

}