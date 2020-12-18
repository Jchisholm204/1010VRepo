#include "intake.h"
#include "main.h"

//  Intake Reset Function - returns true or false
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

 // Intake PID Task
void intake_fn(void*param){
  //  Reset the motor encoders to zero when the task starts for the first time
  intakeR.tare_position();
  intakeL.tare_position();

  //  Int common variables
  bool overide = false;
  int cap = 127;
  int targetValue = 0;

  // Int Left Specific Variables
  int err1 = 0;
  int err_last1 = 0;
  int currentValue1;
  int motorPower1;
  int derr1;

  //  Int Right Specific Variables
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

    //  Toggle control for the intake override - lets us use joysticks instead of the PID
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
    //  IF Override is on and Partner R1 is pressed reset the motor encoders to zero
    if(partner.get_digital(E_CONTROLLER_DIGITAL_R1) && overide == true){
      intakeR.tare_position();
      intakeL.tare_position();
    }


    //  Switch Case for controlling intake PID input
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
    //  Override = joysticks / else = POS Controlled
    else*/ if(overide == true){
      intakeL.move_velocity(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
      intakeR.move_velocity(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));
    }
    else{
      //  Use limit switches to close / else use PID
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
      else{ //Run identical PIDs on the L and R intakes, but use 2 pids so that if one gets stuck it will autocorrect
        //Intake L
        currentValue1 = intakeL.get_position();
        err1 = targetValue - currentValue1; //error is delta of target and current positions
        derr1 = err1 - err_last1; //difference of errors over iterations
        err_last1 = err1; //store last error
        motorPower1 = (1 * err1) + (1.1 * derr1); //PD constants plus our variables
        motorPower1 = motorPower1 > 127 ? 127 : motorPower1 < -127 ? -127 : motorPower1; //caps output at +127, -127
        intakeL.move(motorPower1); //move the lift equal to motorPower

        //Intake R
        currentValue2 = intakeR.get_position();
        err2 = targetValue - currentValue2; //error is delta of target and current positions
        derr2 = err2 - err_last2; //difference of errors over iterations
        err_last2 = err2; //store last error
        motorPower2 = (1 * err2) + (1.1 * derr2); //PD constants plus our variables
        motorPower2 = motorPower2 > 127 ? 127 : motorPower2 < -127 ? -127 : motorPower2; //caps output at +127, -127
        intakeR.move(motorPower2); //move the lift equal to motorPower
      }
    }
    delay(10); //delay - stops the brain from overheating
  }
}
