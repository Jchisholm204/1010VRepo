#include "main.h"
#include "ext.h"
#include "setup.h"
bool Docker_Homing_Complete = false;
int dock_state;

void Dock(int state){
   dock_state = state;
}

void Intake(int velocity){
   intakeMotor.move_velocity(velocity);
   conveyerMotor.move_velocity(velocity);
}

void Docker_Task_fn(void*param){
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
   int targetValue = 0;

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
            targetValue = Dock_PID_MaxVal;
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
      else if(Docker_Homing_Complete == false){
         dockerMOBO.move_velocity(-100);
      };

      currentValue = dockerMOBO.get_position();
      err = targetValue - currentValue;
      err_last = err;
      derr = (err - err_last);
      p = (DOCK_PID_KP * err);
      d = DOCK_PID_KD * derr;

      motorPower = p+i+d;

      if(motorPower > DOCK_MAX_UP){motorPower = DOCK_MAX_UP;}
      if(motorPower < DOCK_MAX_DOWN){motorPower = DOCK_MAX_DOWN;}
    //  motorPower = (motorPower > 1 ? 1 : motorPower < -1 ? -1 : motorPower);
      dockerMOBO.move(motorPower);
      pros::delay(DOCK_TASK_LOOP_DELAY);
   };
}

void Arm_Task_fn(void*param){
   pros::delay(ARM_LOOP_DELAY);
}