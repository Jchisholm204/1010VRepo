#include "main.h"
#include "dock.h"
#include "helpers.h"

int dock_state;

void Docker_Task_fn(void*param){
   int motorPower;
   int currentValue;
   int err = 0;
   int derr = 0;
   int err_last = 0;
   float KI = 0;
   float KP = 1.5;
   float KD = 0.5;
   float p;
   float i = 0;
   float d;
   int targetValue = 0;
   int MAXUP = -127;
   int MAXDOWN = 127;

   while(true){

///////Docker Position Controller/////////////
      switch(dock_state){
         case 0:
            //pot value when dock down
            targetValue = 400;
            break;
         case 1:
            //pos value when dock up
            targetValue = 0;
            currentValue = home_tare(dockerMotor, Docker_Endstop_Min, -100);
            break;
         default:
            currentValue = home_tare(dockerMotor, Docker_Endstop_Min, -80);
            break;
      };
///////Docker Position Controller/////////////

////////PID LOGIC//////////////////////////////////////
      currentValue = dockerMotor.get_position();
      err = targetValue - currentValue;
      err_last = err;
      derr = (err - err_last);
      p = (KP * err);
      d = (KD * derr);

      motorPower = p+i+d;

      if(motorPower < MAXUP){motorPower = MAXUP;}
      if(motorPower > MAXDOWN){motorPower = MAXDOWN;}
    //  motorPower = (motorPower > 1 ? 1 : motorPower < -1 ? -1 : motorPower);
      dockerMotor.move(motorPower);
/////////PID LOGIC//////////////////////////////////

      pros::delay(20);

   };
}