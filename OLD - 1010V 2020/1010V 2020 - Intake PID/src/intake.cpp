#include "intake.h"
#include "main.h"
void intake_fn(void*param){
  intakeR.tare_position();
  intakeL.tare_position();

  bool overide = false;
  int cap;
  int targetValue;

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
    if(partner.get_digital(E_CONTROLLER_DIGITAL_L1)){
      overide = true;
      master.set_text(0, 0, "OVERRIDE ACTIVE");
      master.rumble(".")
    }
    else if(partner.get_digital(E_CONTROLLER_DIGITAL_L2)){
      overide = false;
      master.set_text(0, 0, "OVERRIDE DISENGAGED")
    }
    if(partner.get_digital(E_CONTROLLER_DIGITAL_R1)){
      intakeR.tare_position();
      intakeL.tare_position();
    }

    partner.set_text(0, 0, "Intake L: %d", intakeL.get_position());
    partner.set_text(1, 0, "Intake R: %d", intakeR.get_position());
/*    if(competition::is_autonomous()){

    }
    else*/ if(overide == true){
      intakeL.move_velocity(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y))
      intakeR.move_velocity(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y))
    }
    else{
      switch(intakeStatus){
        case INTAKE_FOLDED:
          targetValue = 0;
          break;

        case INTAKE_OPEN:
          targetValue = 120;
          break;

        case INTAKE_CLOSED:
          targetValue = 10;
          break;
        default:
          intakeStatus = INTAKE_CLOSED;
          break;

      };
//Intake L
      currentValue1 = (intakeL.get_position()/3);
      //the claws are on a 3:1 gearbox, so "/" by 3 to be able to set the deg in actual
      err1 = targetValue - currentValue1; //error is delta of target and current positions
      derr1 = err1 - err_last1; //difference of errors over iterations
      err_last1 = err1; //store last error
      motorPower1 = (0.9 * err1) + (1.6 * derr1); //PD constants plus our variables
      motorPower1 = motorPower1 > 127 ? 127 : motorPower1 < -127 ? -127 : motorPower1; //caps output at +127, -127
   //motorPower > cap ?  cap :
      intakeL.move(motorPower1); //move the lift equal to motorPower
//Intake R


      currentValue2 = (intakeR.get_position()/3);
      //the claws are on a 3:1 gearbox, so "/" by 3 to be able to set the deg in actual
      err2 = targetValue - currentValue2; //error is delta of target and current positions
      derr2 = err2 - err_last2; //difference of errors over iterations
      err_last2 = err2; //store last error
      motorPower2 = (0.9 * err2) + (1.6 * derr2); //PD constants plus our variables
      motorPower2 = motorPower2 > 127 ? 127 : motorPower2 < -127 ? -127 : motorPower2; //caps output at +127, -127
   //motorPower > cap ?  cap :

      intakeR.move(motorPower2); //move the lift equal to motorPower
    }
    delay(20);
  }
}
