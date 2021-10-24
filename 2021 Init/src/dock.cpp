#include "main.h"
#include "ext.h"
bool Docker_Homing_Complete = false;
int dock_state;

void Docker_Task_fn(void*param){
	float stackKP = 0.8; //was .7
	float stackKD = 1.2;  //was .02
   //same PID Logic as turnValue
   int motorPower;
   int startTime = millis();
   int currentValue;
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

   //HOMING SEQUENCE
   while(Docker_Homing_Complete == false  && Docker_Endstop_Min.get_value() == 0){
      dockerMOBO.move_velocity(-100);
      if(Docker_Endstop_Min.get_value() == 1){
         dockerMOBO.move_velocity(0);
         dockerMOBO.tare_position();
         currentValue = dockerMOBO.get_position();
         Docker_Homing_Complete = true;
      }
   };

   while(true){
      //Docker Position Controller
      switch(dock_state){
         case 1:
            //pot value when dock down
            targetValue = 500;
            break;
         case 0:
            //pos value when dock up
            targetValue = 0;
            Docker_Homing_Complete = false;
            break;
         default:
            Docker_Homing_Complete = false;
            break;
      };

      if(Docker_Endstop_Min.get_value() == 1){
         currentValue = dockerMOBO.get_position();
         Docker_Homing_Complete = true;
      }
      else if(Docker_Homing_Complete == false && Docker_Endstop_Min.get_value() == 0){
         dockerMOBO.move_velocity(-100);
      };

      currentValue = dockerMOBO.get_position();
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
   };
}