#include "main.h"
#include "lift.h"

void ArmLift_fn(void*param){
  int err = 0;
  int err_last = 0;
  int currentValue;
  int targetValue;
  int motorPower;
  int cap;
  int derr;
  int trayTarget;
  bool TrayZero;

  while(true){
    if(partner.get_digital(E_CONTROLLER_DIGITAL_L2)){
      ArmMotor.move_velocity(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
      if(partner.get_digital(E_CONTROLLER_DIGITAL_L1)){ArmMotor.tare_position();}
    }
    else{
      switch(liftState){
        case armDown:
          targetValue = 0;
          break;

        case armLow:
          targetValue = 500;
          break;

        case armHigh:
          targetValue = 650;
          break;

        case armDeScore:
          targetValue = 410;
          break;

        default:
          liftState = 0;
          break;

      };
//hi
      currentValue = ArmMotor.get_position();
      err = targetValue - currentValue; //error is delta of target and current positions
      err_last = err; //store last error
      derr = err - err_last; //difference of errors over iterations
      motorPower = (0.9 * err) + (1.6 * derr); //PD constants plus our variables
      motorPower = motorPower > 127 ? 127 : motorPower < -127 ? -127 : motorPower; //caps output at +127, -127
   //motorPower > cap ?  cap :

      ArmMotor.move(motorPower); //move the lift equal to motorPower
    }
  }
}
