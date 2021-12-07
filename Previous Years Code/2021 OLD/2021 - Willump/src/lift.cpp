#include "main.h"
#include "helpers.h"
#include "drive.h"
#include "dock.h"
#include "lift.h"

int lift_state;

void Lift_Task_fn(void*param){
   int motorPower;
   int currentValue;
   int err = 0;
   int derr = 0;
   int err_last = 0;
   float KI = 0;
   float KP = 1.2;
   float KD = 1.6;
   float p;
   float i = 0;
   float d;
   int targetValue = 0;
   int MAXUP = 400;
   int MAXDOWN = 0;

   while(true){
      ///////Tower Lift Position Controller/////////////
      switch(lift_state){
         case 0:
            targetValue = 0;
            break;
         case 1:
            //pos value when dock up
            targetValue = 400;
            break;
         case 2:
            currentValue = home_tare(liftMotor, Lift_Endstop_Min, -100);
            break;
         default:
            lift_state = 2;
            break;
      };
///////Arm Position Controller/////////////

////////PID LOGIC//////////////////////////////////////
      currentValue = liftMotor.get_position();
      err = targetValue - currentValue;
      err_last = err;
      derr = (err - err_last);
      p = (KP * err);
      d = KD * derr;

      motorPower = p+i+d;

      if(motorPower < MAXUP){motorPower = MAXUP;}
      if(motorPower > MAXDOWN){motorPower = MAXDOWN;}
    //  motorPower = (motorPower > 1 ? 1 : motorPower < -1 ? -1 : motorPower);
      liftMotor.move(motorPower);
/////////PID LOGIC//////////////////////////////////
    pros::delay(20);
   }
}