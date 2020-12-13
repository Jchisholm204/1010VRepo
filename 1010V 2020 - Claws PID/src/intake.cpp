#include "intake.h"
#include "main.h"


double zero_fn(int inr){
  bool iClosed = false;
  if(inr == intR){
    if(intakeRlimit.get_value() == true){
      intakeR.move_velocity(0);
      intakeR.tare_position();
      iClosed = true;
    }
    else if(intakeRlimit.get_value() == false){
      intakeR.move_velocity(-100);
    }
  }
  if(inr == intL){
    if(intakeLlimit.get_value() == true){
      intakeL.move_velocity(0);
      intakeL.tare_position();
      iClosed = true;
    }
    else if(intakeRlimit.get_value() == false) {
      intakeL.move_velocity(-100);
    }
  }
  if(inr == intB){
    if(intakeLlimit.get_value() == true){
      intakeL.move_velocity(0);
      intakeL.tare_position();
      iClosed = true;
    }
    else if(intakeRlimit.get_value() == false) {
      intakeL.move_velocity(-100);
    }
    if(intakeRlimit.get_value() == true){
      intakeR.move_velocity(0);
      intakeR.tare_position();
      iClosed = true;
    }
    else if(intakeRlimit.get_value() == false){
      intakeR.move_velocity(-100);
    } 
  }
  return iClosed;
}


void intake_fn(void*param){
  intakeR.tare_position();
  intakeL.tare_position();

  bool overide = false;
  int cap = 127;
  int targetValue = 0;

  int err1 = 0;
  int err_last1 = 0;
  int currentValue1;
  int motorPower1;
  int derr1;

  int err2 = 0;
  int err_last2 = 0;
  int currentValue2;
  int motorPower2;
  int derr2;


  while(true){
    /*
		if(partner.get_digital(E_CONTROLLER_DIGITAL_X)){
			zero_fn(intB);
			overide = true;
		}*/
    if(partner.get_digital_new_press(E_CONTROLLER_DIGITAL_L1) || partner.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)){
      master.clear();
      partner.clear();
      if(overide==true){
        overide=false;
        master.set_text(0, 0, "OVERRIDE DISENGAGED");
        partner.set_text(0, 0, "OVERRIDE DISENGAGED");
      };
      if(overide==false){
        overide=true;
        master.set_text(0, 0, "OVERRIDE ACTIVE");
        partner.set_text(0, 0, "OVERRIDE ACTIVE");
      };
    };
    if(partner.get_digital(E_CONTROLLER_DIGITAL_R1) && overide == true){
      intakeR.tare_position();
      intakeL.tare_position();
    }
    switch (intakeStatus)
    {
    case(INTAKE_HOLD):
      targetValue = 250;
      break;
    case(INTAKE_OPEN):
      targetValue = 360;
      break;
    case(INTAKE_CLOSED):
      targetValue = 0;
      break;
    default:
      intakeStatus = INTAKE_CLOSED;
      break;
    }
      /*    if(competition::is_autonomous()){

      }
    else*/ if(overide == true){
      intakeL.move_velocity(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
      intakeR.move_velocity(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));
    }
    else{
      if(intakeStatus == INTAKE_CLOSED){
        if(intakeRlimit.get_value() == true){
          intakeR.move_velocity(0);
        }
        else if(intakeRlimit.get_value() == false){
          intakeR.move_velocity(-100);
        }
        if(intakeLlimit.get_value() == true){
          intakeL.move_velocity(0);
        }
        else if(intakeRlimit.get_value() == false) {
          intakeL.move_velocity(-100);
        }
      }
      else{
        //Intake L
        currentValue1 = intakeL.get_position();
        //the claws are on a 3:1 gearbox, so "/" by 3 to be able to set the deg in actual
        err1 = targetValue - currentValue1; //error is delta of target and current positions
        derr1 = err1 - err_last1; //difference of errors over iterations
        err_last1 = err1; //store last error
        motorPower1 = (1 * err1) + (1.1 * derr1); //PD constants plus our variables
        motorPower1 = motorPower1 > 127 ? 127 : motorPower1 < -127 ? -127 : motorPower1; //caps output at +127, -127
        //motorPower > cap ?  cap :
        intakeL.move(motorPower1); //move the lift equal to motorPower

        //Intake R
        currentValue2 = intakeR.get_position();
        //the claws are on a 3:1 gearbox, so "/" by 3 to be able to set the deg in actual
        err2 = targetValue - currentValue2; //error is delta of target and current positions
        derr2 = err2 - err_last2; //difference of errors over iterations
        err_last2 = err2; //store last error
        motorPower2 = (1 * err2) + (1.1 * derr2); //PD constants plus our variables
        motorPower2 = motorPower2 > 127 ? 127 : motorPower2 < -127 ? -127 : motorPower2; //caps output at +127, -127
        //motorPower > cap ?  cap :

        intakeR.move(motorPower2); //move the lift equal to motorPower
      }
    }
    delay(10);
  }
}
