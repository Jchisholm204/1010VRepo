#include "main.h"
//#include "pros/adi.hpp"
//using namespace okapi;
//be mindfull of pros namespace
////////////////int Auto = 0;

void redstack(){ //red stacking auto
  intake.intake(100); //motor velocity [RED = MAX/MIN 100]
  driveF.MoveDistance(DIRECTION_FORWARD, 1000, 50, 3500); //direction, targetValue, speed, timeout
  intake.intake(0);//motor velocity [RED = MAX/MIN 100]
  driveF.MoveDistance(DIRECTION_BACK, 700, 100, 1000); //direction, targetValue, speed, timeout

  driveF.TurnDistance(DIRECTION_RIGHT, 150, 70, 970); //direction, targetValue, speed, timeout

  //intake.intake(-20);//motor velocity [RED = MAX/MIN 100]
  cubeTray.stack(800, 30); //absolute motor position, velocity
  driveF.MoveDistance(DIRECTION_FORWARD, 330, 100, 950); //direction, targetValue, speed, timeout
  //intake.intake(0);
  driveF.stopDriving();
  cubeTray.stack(935, 90); //absolute motor position, velocity
  pros::delay(1400);
  driveF.timeDrive(1000, -40); //time, motorpower [-127 - +127]
}
void bluestack(){ //blue stacking auto
  intake.intake(100);  //motor velocity [RED = MAX/MIN 100]
  driveF.MoveDistance(DIRECTION_FORWARD, 940, 50, 3200); //direction, targetValue, speed, timeout
  intake.intake(30);  //motor velocity [RED = MAX/MIN 100]
  driveF.MoveDistance(DIRECTION_BACK, 800, 100, 1000); //direction, targetValue, speed, timeout
  intake.intake(0);  //motor velocity [RED = MAX/MIN 100]
  driveF.TurnDistance(DIRECTION_LEFT, 130, 70, 890); //direction, targetValue, speed, timeout
  cubeTray.stack(800, 30); //absolute motor position, velocity
  driveF.MoveDistance(DIRECTION_FORWARD, 385, 100, 1300); //direction, targetValue, speed, timeout
  driveF.stopDriving();
  cubeTray.stack(935, 90); //absolute motor position, velocity
  pros::delay(1200);
  driveF.timeDrive(2000, -40); //time, motorpower [-127 - +127]
}
void mechautored(){
  driveF.timeGlide(500, 200);
  pros::delay(400);
  driveF.timeGlide(1100, -200);
  intake.intake(200);
  driveF.MoveDistance(DIRECTION_FORWARD, 940, 50, 3300);
  pros::delay(200);
  driveF.MoveDistance(DIRECTION_BACK, 900, 127, 3200);
  driveF.timeGlide(700, 200);
  driveF.MoveDistance(DIRECTION_FORWARD, 940, 50, 3300);
}
void skills(){
  intake.intake(100);
  driveF.MoveDistance(DIRECTION_FORWARD, 940, 40, 4000);
  driveF.TurnDistance(DIRECTION_RIGHT, 90, 80, 800);
  driveF.MoveDistance(DIRECTION_FORWARD, 200, 100, 800);
  driveF.TurnDistance(DIRECTION_LEFT, 130, 100, 1400);
  driveF.MoveDistance(DIRECTION_FORWARD, 200, 100, 800);
  driveF.TurnDistance(DIRECTION_RIGHT, 90, 80, 800);
  driveF.MoveDistance(DIRECTION_FORWARD, 940, 40, 4000);
  pros::delay(800);

}
void skerewit(){
  //driveF.timeGlide(500, -200);
  //driveF.timeGlide(800, 200);
  driveF.MoveDistance(DIRECTION_BACK, 300, 50, 1000);
  pros::delay(400);
  driveF.MoveDistance(DIRECTION_FORWARD, 200, 150, 1000);
  driveF.stopDriving();
}
void playoffsred(){
  intake.intake(200);
  driveF.timeGlide(600, 100);
  driveF.timeGlide(750, -100);
  arm.proLift(0, 100);
  driveF.MoveDistance(DIRECTION_FORWARD, 900, 45, 3200);
  driveF.stopDriving();
  delay(200);
  driveF.MoveDistance(DIRECTION_BACK, -900, 80, 2500);
  driveF.stopDriving();
/*
  driveLF.move_velocity(-200);
  driveRB.move_velocity(-200);
  pros::delay(1000);
  driveF.MoveDistance(DIRECTION_FORWARD, 900, 45, 3200);
  driveF.MoveDistance(DIRECTION_BACK, 200, 10, 800);
  driveF.stopDriving();
*/
}
void playoffsblue(){
  intake.intake(200);
  driveF.timeGlide(600, -100);
  driveF.timeGlide(750, 100);
  arm.proLift(0, 100);
  driveF.MoveDistance(DIRECTION_FORWARD, 900, 45, 3200);
  driveF.stopDriving();
  delay(200);
  driveF.MoveDistance(DIRECTION_BACK, -900, 80, 2500);
  driveF.stopDriving();
}
void flipout(){  //flipout - ALWAYS RUN
//Flipout ver-2
  cubeTray.stack(700, 100);
  pros::delay(1800);
  cubeTray.stack(200, 100);
  pros::delay(400);
  arm.proLift(400, 100);
  pros::delay(800);
  arm.proLift(0, 100);
  cubeTray.stack(0, 100);
  pros::delay(400);
}
void expand(){
  intake.intake(-200);
  arm.proLift(300, 1000);
  //pros::delay(750); //five*5 hour energy
  arm.proLift(0, 100);
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
//autonvoid
void autonomous() {
  expand();
  cubestackBLUE();
  //cubeTray.pid(510, 3000, 0.8, 0, 1.2);
  //Display
  //pros::lcd::print(1, "VOID: AUTON");
  //flipout();
  //skerewit();
  //mechautored();
  //playoffsred();
  //cubestackRED();
  //blue2();
  //stacky.move_absolute(TRAYUP);

}
