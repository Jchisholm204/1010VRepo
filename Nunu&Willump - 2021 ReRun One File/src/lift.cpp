#include "main.h"
#include "helpers.h"
#include "drive.h"
#include "dock.h"
#include "lift.h"

int lift_state = 2;

void Lift_Task_fn(void*param){
   int motorPower;
   int currentValue;
   int err = 0;
   int derr = 0;
   int err_last = 0;
   float KI = 0;
   float KP = 1;
   float KD = 1.55;
   float p;
   float i = 0;
   float d;
   int targetValue;
   int MAXUP = -127;
   int MAXDOWN = 127;

   while(true){
      ///////Tower Lift Position Controller/////////////
      switch(lift_state){
         case 0:
            //default state
            targetValue = 1900;
            break;
         case 1:
            //pos value when dock down
            targetValue = 300;
            break;
         case 5:
            //pos value for grabbing mobo's
            targetValue = 470;
            break;
         default:
            //restore case 0
            lift_state = 0;
            break;
      };
///////Arm Position Controller/////////////

////////PID LOGIC//////////////////////////////////////
      currentValue = Lift_POT.get_value();
      //printf("%d\n", currentValue);
      err = targetValue - currentValue;
      derr = (err - err_last);
      err_last = err;
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