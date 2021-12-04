#include "main.h"
#include "helpers.h"
#include "drive.h"
#include "dock.h"
#include "lift.h"

int lift_state = 5;
int lift_state_prev;
bool lift_manual_exemption = false;

void Lift_Task_fn(void*param){
   int motorPower;
   int currentValue;
   int err = 0;
   int derr = 0;
   int err_last = 0;
   float KI = 0;
   float KP = 1;
   float KD = 1.55; //1.5
   float p;
   float i = 0;
   float d;
   int targetValue;
   int MAXUP = -127;
   int MAXDOWN = 127;

   while(true){
      if(lift_manual_exemption == true){
         targetValue = Lift_POT.get_value();
      }
      else{
         if(lift_state != lift_state_prev){
            ///////Tower Lift Position Controller/////////////
            switch(lift_state){
               case 5:
                  //starting position (all the way up [impacts intakes])
                  targetValue = 580;
                  break;
               case 0:
                  //pos value when holding holding mogo (half way up)
                  targetValue = 3000;
                  break;
               case 1:
                  //pos value for grabbing mobo's (when all the way down)
                  targetValue = 3900;
                  break;
               default:
                  //restore case 0
                  lift_state = 1;
                  break;
            };
   ///////Arm Position Controller/////////////
         }
         lift_state_prev = lift_state;

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
      }
   pros::delay(20);
   }
}