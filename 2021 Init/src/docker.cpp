#include "main.h"
#include "ixl.h"

int dock_state;

void Docker_Task_fn(void*param){
	float stackKP = 0.8; //was .7
	float stackKD = 1.2;  //was .02
   //same PID Logic as turnValue
   int motorPower;
   int startTime = millis();
   int currentValue = dockerPOT.get_value();
   int err = 0;
   int derr = 0;
   int err_last = 0;
   float KI = 0;
   float p;
   float i = 0;
   float d;
   int targetValue;

   int MAXUP = 100;
   int MAXDOWN = -100;

   while(true){
      switch(dock_state){
         case 1:
            //pot value when dock down
            targetValue = 100;
            break;
         case 0:
            //pos value when dock up
            targetValue = 0;
            break;
         default:
            break;
      }

      currentValue = dockerPOT.get_value();
      err = targetValue - currentValue;
      err_last = err;
      derr = (err - err_last);
      p = (stackKP * err);
      d = stackKD * derr;

      motorPower = p+i+d;

      if(motorPower > MAXUP){motorPower = MAXUP;}
      if(motorPower < MAXDOWN){motorPower = MAXDOWN;}
    //  motorPower = (motorPower > 1 ? 1 : motorPower < -1 ? -1 : motorPower);
      dockerMOBO.move(motorPower);
      delay(20);
   }
}