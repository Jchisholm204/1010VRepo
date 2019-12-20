#include "Intakes.h"
#include "main.h"
int intakeState;
void intakeClass::opintake(void){
  if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){
    intakeState = MoveIntake;
  }
  else if(master.get_digital(E_CONTROLLER_DIGITAL_L2)){
    intakeState = MoveOuttake;
  }
  else if(master.get_digital(E_CONTROLLER_DIGITAL_B)){
    intakeState = MoveSlowOut;
  }
  else if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
    intakeState = MoveSlowIn;
  }
  else{
    intakeState = MoveStop;
  };
  switch(intakeState){
    case MoveIntake:
      RightIntake.move_velocity(200);
      LeftIntake.move_velocity(200);
      break;
    case MoveOuttake:
      RightIntake.move_velocity(-200);
      LeftIntake.move_velocity(-200);
      break;
    case MoveSlowIn:
      RightIntake.move_velocity(80);
      LeftIntake.move_velocity(80);
      break;
    case MoveSlowOut:
      RightIntake.move_velocity(-100);
      LeftIntake.move_velocity(-100);
      break;
    case MoveStop:
      RightIntake.move_velocity(0);
      LeftIntake.move_velocity(0);
      break;
    case MoveTower:
      RightIntake.move_velocity(200);
      LeftIntake.move_velocity(200);
      break;
  };
}
void intakeClass::suck(int velocity){
  RightIntake.move_velocity(velocity);
  LeftIntake.move_velocity(velocity);
}
