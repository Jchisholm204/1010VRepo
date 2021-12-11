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

void intakes(int vrooom){
    intakeL.move_velocity(vrooom);
    intakeR.move_velocity(vrooom);
}

void testAuto(void){

    driveF.TurnDistance(DIRECTION_RIGHT, 100, 9191);
    driveF.TurnDistance(DIRECTION_LEFT, 100, 9191);
    driveF.stopDriving();
}

void skills(void){
    intakes(-200);
    roller.move_velocity(75);
    pros::delay(1200);
    roller.move_velocity(0);
    flyWheel.move_velocity(500);
    driveF.MoveDistance(DIRECTION_FORWARD, 360, 2500);
	intakeL.move_velocity(180 * (1 - LiL.get_value())); //stop intakes moving backwards if limit pressed
	intakeR.move_velocity(180 * (1 - LiR.get_value()));
    driveF.TurnDistance(DIRECTION_RIGHT, 430, 5000);
    intakes(0);
    driveF.MoveDistance(DIRECTION_FORWARD, 550, 4000);
    driveF.twrAlign(1000);
    //driveF.TurnDistance(DIRECTION_RIGHT, 45, 700); //align with walls
    roller.move_velocity(200);
    pros::delay(400);
    roller.move_velocity(0);
    flyWheel.move_velocity(0);
    pros::delay(2000);
    driveF.MoveDistance(DIRECTION_BACK, 1000, 3000);
    pros::delay(100);
    driveF.TurnDistance(DIRECTION_LEFT, 120, 1500);
    driveF.MoveDistance(DIRECTION_FORWARD, 710, 2000);
    intakes(-200);
    pros::delay(1100);
    roller.move_velocity(75);
    pros::delay(700);
    roller.move_velocity(0);
    //driveF.TurnDistance(DIRECTION_RIGHT, 50, ) //zootzoot
    intakes(100);
    driveF.MoveDistance(DIRECTION_BACK, 1700, 5000);
    intakes(0);
    driveF.TurnDistance(DIRECTION_RIGHT, 330, 3000);
    flyWheel.move_velocity(600);
    driveF.MoveDistance(DIRECTION_FORWARD, 500, 2000);
    roller.move_velocity(200);
    pros::delay(500);
    roller.move_velocity(0);
    driveF.stopDriving();
}

void RedAuto(void){

}

void BlueAuto(void){
    
}

/* //FUCKED


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
    
*/