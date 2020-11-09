#include "main.h"
//#include "pros/adi.hpp"
//using namespace okapi;
//be mindfull of pros namespace
////////////////int Auto = 0;

void expand(){
  intake.intake(-200);
  arm.proLift(300, 1000);
  //pros::delay(750); //five*5 hour energy
  arm.proLift(0, 100);
}
void oneCube(){
  driveF.MoveSlow(DIRECTION_BACK, 300, 40, 4000);
  driveF.MoveSlow(DIRECTION_FORWARD, 200, 40, 4000);
}
void cubestackBLUE(){
  intake.intake(200);
  driveF.MoveDistance(DIRECTION_FORWARD, 850, 90, 2000);
  driveF.angleDrive(2, -200, 2000);
  driveF.MoveSlow(DIRECTION_FORWARD, 900, 90, 1850);
  driveF.MoveDistance(DIRECTION_BACK, 600, 100, 1000);
  driveF.TurnDistance(DIRECTION_LEFT, 920, 50, 1000);
  intake.intake(-50);
  driveF.timeGlide(900, -70); //was 600 was 700
  driveF.stopDriving();
  intake.intake(0);
  driveF.MoveSlow(DIRECTION_FORWARD, 270, 40, 800);
  driveF.stopDriving();
  //stacky.move_absolute(TRAYUP);
  cubeTray.pid(530, 2700, 0.4, 0, 1.2);
  intake.intake(-50);
  pros::delay(200);
  driveF.timeDrive(750, -30);
  stacky.move_absolute(0, 100);
  driveF.timeDrive(1250, -60);

  //cubeTray.stack(800, 2000);


}
void cubestackRED(){
  intake.intake(200);
  driveF.MoveDistance(DIRECTION_FORWARD, 850, 90, 2150);
  driveF.angleDrive(1, -200, 2000);
  driveF.MoveSlow(DIRECTION_FORWARD, 900, 90, 1850);
  driveF.MoveDistance(DIRECTION_BACK, 600, 100, 1000);
  driveF.TurnDistance(DIRECTION_RIGHT, 920, 50, 1000);
  intake.intake(-50);
  driveF.timeGlide(900, 70); //was 600 was 700
  driveF.stopDriving();
  intake.intake(0);
  driveF.MoveSlow(DIRECTION_FORWARD, 270, 40, 800);
  driveF.stopDriving();
  //stacky.move_absolute(TRAYUP);
  cubeTray.pid(530, 3000, 0.4, 0, 1.2);
  intake.intake(-50);
  pros::delay(200);
  driveF.timeDrive(750, -30);
  //stacky.move_absolute(0, 100);
  driveF.timeDrive(1250, -60);

  //cubeTray.stack(800, 2000);


}
void red(){
  driveF.drive(driveRB.get_position(), 800, 2000, 1.5, 0.0001, 0.001);
  driveF.angleDrive(R, -200, 1900);
  driveF.drive(driveRB.get_position(), 1000, 3200, 1.5, 0.0001, 0.001);
  driveF.drive(driveRB.get_position(), -600, 1200, 1.2, 0.0001, 0.001);
}
void red2(){
  intake.intake(200);
  driveF.MoveSlow(DIRECTION_FORWARD, 800, 40, 3000);
  driveF.TurnDistance(DIRECTION_LEFT, 1000, 60, 3000);
  driveF.timeGlide(1000, 150);
  driveF.MoveSlow(DIRECTION_FORWARD, 465, 40, 2000);
  intake.intake(-200);
  delay(1500);
  driveF.timeDrive(1000, -50);
}
void blue2(){
  intake.intake(200);
  driveF.MoveSlow(DIRECTION_FORWARD, 800, 40, 3000);
  driveF.TurnDistance(DIRECTION_RIGHT, 1000, 60, 3000);
  driveF.timeGlide(1000, -150);
  driveF.MoveSlow(DIRECTION_FORWARD, 465, 40, 2000);
  intake.intake(-200);
  delay(1500);
  driveF.timeDrive(1000, -50);
}
void cubestackSKILLS(){
  intake.intake(200);
  driveF.MoveSlow(DIRECTION_FORWARD, 900, 90, 4000);
  driveF.angleDrive(1, -200, 2200);
  driveF.MoveSlow(DIRECTION_FORWARD, 940, 90, 2500);
  driveF.MoveSlow(DIRECTION_BACK, 630, 100, 3000);
  driveF.TurnDistance(DIRECTION_RIGHT, 920, 50, 1000);
  intake.intake(-50);
  driveF.timeGlide(900, 70); //was 600 was 700
  driveF.stopDriving();
  intake.intake(0);
  driveF.MoveSlow(DIRECTION_FORWARD, 270, 40, 1000);
  driveF.stopDriving();
  //stacky.move_absolute(TRAYUP);
  cubeTray.pid(530, 3000, 0.4, 0, 1.2);
  intake.intake(-50);
  pros::delay(200);
  driveF.timeDrive(750, -30);
  stacky.move_absolute(0, 100);
  driveF.MoveSlow(DIRECTION_BACK, 100, 40, 1000);
  intake.intake(200);
  driveF.TurnDistance(DIRECTION_LEFT, 1000, 40, 2000);
  driveF.MoveSlow(DIRECTION_FORWARD, 800, 40, 3500);
  intake.intake(-20);
  arm.proLift(500, 1000);
  intake.intake(-100);
  driveF.MoveSlow(DIRECTION_BACK, 200, 40, 3000);

  //cubeTray.stack(800, 2000);


}
//autonvoid
void autonomous() {
  expand();
  //cubestackRED();
  //cubestackSKILLS();
  //cubeTray.pid(510, 3000, 0.8, 0, 1.2);
  //Display
  //pros::lcd::print(1, "VOID: AUTON");
  //flipout();
  //skerewit();
  //
  //mechautored();
  //playoffsred();
  //cubestackRED();
  //blue2();
  //stacky.move_absolute(TRAYUP);

}
