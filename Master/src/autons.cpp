#include "main.h"
#include "autons.h"
#include "drive.h"
Chassis driveF;
void expanSn(int timeout){
        intakeL.move_velocity(-200);
		intakeR.move_velocity(-200);
        flyWheel.move_velocity(600);
        pros::delay(timeout);
}

void testAuto(void){


    expanSn(1000);
    flyWheel.move_velocity(0);
    roller.move_velocity(50);
   driveF.MoveDistance(DIRECTION_FORWARD, 100, 750);
   roller.move_velocity(0);
   driveF.TurnDistance(DIRECTION_RIGHT, 280, 2000);
   intakeL.move_velocity(180 * (1 - LiL.get_value())); //stop intakes moving backwards if limit pressed
   intakeR.move_velocity(180 * (1 - LiR.get_value()));
   driveF.MoveDistance(DIRECTION_FORWARD, 400, 2500);
   driveF.TurnDistance(DIRECTION_RIGHT, 100, 2000);
   flyWheel.move_velocity(470);
   driveF.MoveDistance(DIRECTION_FORWARD, 300, 2000);
   roller.move_velocity(200);
   pros::delay(1000);


   //driveF.MoveDistance(DIRECTION_BACK, 200, 2000);
    

}

void RedAuto(void){

}

void BlueAuto(void){
    
}