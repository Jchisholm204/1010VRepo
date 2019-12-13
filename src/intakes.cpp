#include "main.h"
#include "intakes.h"
void Intake::intake(int speed) {
  //combine both motors into one with a function
  leftSuck.move_velocity(speed);
  rightSuck.move_velocity(speed);
}
void Intake::opintake(void){
  //Intake
  if(master.get_digital(E_CONTROLLER_DIGITAL_R1)) { //intake fast - master R1
    leftSuck.move_velocity(200);
    rightSuck.move_velocity(200);
  }
  else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)) { //outtake fast - master R2
    leftSuck.move_velocity(-200);
    rightSuck.move_velocity(-200);
  }
  else if(partner.get_digital(E_CONTROLLER_DIGITAL_R1)) { //intake fast - partner R1
    leftSuck.move_velocity(200);
    rightSuck.move_velocity(200);
  }
  else if(partner.get_digital(E_CONTROLLER_DIGITAL_R2)) {  //outtake fast - partner R2
    leftSuck.move_velocity(-200);
    rightSuck.move_velocity(-200);
  }

  else if(master.get_digital(E_CONTROLLER_DIGITAL_B)) { //slow outtake - right paddle
    leftSuck.move_velocity(-100);
    rightSuck.move_velocity(-100);
  }
  else if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {  //slow intake - left paddle
    leftSuck.move_velocity(60);
    rightSuck.move_velocity(60);
  }
  else {
    leftSuck.move_velocity(0);
    rightSuck.move_velocity(0);
  };

}
