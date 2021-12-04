#include "main.h"
#include "dock.h"
#include "helpers.h"

int dock_state;

bool dock_manual_exemption = false;

int dock_state_prev;

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
   dock_state = 3; //make dock reset upon startup
   bool Oncelocal = false;
   while(true){
      if(dock_manual_exemption == true){
         Oncelocal = false;
      }
      else if(dock_manual_exemption == false && Oncelocal == false){
         targetValue = dockerMotor.get_position();
         Oncelocal = true;
      }
      else{
         if(dock_state != dock_state_prev){
      ///////Docker Position Controller/////////////
            switch(dock_state){
               case 1:
                  //pot value when dock down
                  targetValue = -510;
                  break;
               case 0:
                  //pos value when dock up
                  targetValue = -410;
                  //currentValue = home_tare(dockerMotor, Docker_Endstop_Min, -100);
                  //targetValue = currentValue;
                  break;
               default:
                  //currentValue = home_tare(dockerMotor, Docker_Endstop_Min, -80);
                  dock_state = 0;
                  break;
            };
         }
         dock_state_prev = dock_state;
   ///////Docker Position Controller/////////////

   ////////PID LOGIC//////////////////////////////////////
         currentValue = dockerMotor.get_position();
         err = targetValue - currentValue;
         derr = (err - err_last);
         err_last = err;
         p = (KP * err);
         d = (KD * derr);

         motorPower = p+i+d;

         if(motorPower < MAXUP){motorPower = MAXUP;}
         if(motorPower > MAXDOWN){motorPower = MAXDOWN;}
      //  motorPower = (motorPower > 1 ? 1 : motorPower < -1 ? -1 : motorPower);
         dockerMotor.move(motorPower);
   /////////PID LOGIC//////////////////////////////////
      }
      pros::delay(20);

   };
}