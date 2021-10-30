#include "main.h"
#include "ext.h"
#include "setup.h"
bool Docker_Homing_Complete = false;
int dock_state;
int arm_state;

void Dock(int state){
   dock_state = state;
}

void Arm(int state){
   arm_state = state;
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
   int MAXUP = DOCK_MAX_UP;
   int MAXDOWN = DOCK_MAX_DOWN;

//////DOCK HOMING SEQUENCE/////////////////
   while(Docker_Homing_Complete == false  && Docker_Endstop_Min.get_value() == 0){
      dockerMOBO.move_velocity(-100);
      if(Docker_Endstop_Min.get_value() == 1){
         dockerMOBO.move_velocity(0);
         dockerMOBO.tare_position();
         currentValue = dockerMOBO.get_position();
         Docker_Homing_Complete = true;
      }
   };
   dockerMOBO.move_velocity(0);
   dockerMOBO.tare_position();
   currentValue = dockerMOBO.get_position();
   Docker_Homing_Complete = true;
/////DOCK HOMING SEQUENCE///////////////////

   while(true){

///////Docker Position Controller/////////////
      switch(dock_state){
         case 1:
            //pot value when dock down
            targetValue = Dock_PID_MaxVal;
            break;
         case 0:
            //pos value when dock up
            targetValue = Dock_PID_MinVal;
            Docker_Homing_Complete = false;
            break;
         default:
            Docker_Homing_Complete = false;
            break;
      };
///////Docker Position Controller/////////////

/////////////HOMING/////////////////////////////////////
      if(Docker_Endstop_Min.get_value() == 1){
         currentValue = dockerMOBO.get_position();
         Docker_Homing_Complete = true;
      }
      else if(Docker_Homing_Complete == false){
         dockerMOBO.move_velocity(-100);
      };
//////////HOMING////////////////////////////////////


////////Change Max Dock Speed Depending on if there is a tower///////
      if(Docker_Optical.get_proximity() < Dock_Tower_Detection_Trigger_Value && Dock_Tower_Detection_Enable == true){
         MAXDOWN = Dock_Tower_Loaded_MAXDOWN;
         MAXUP = Dock_Tower_Loaded_MAXUP;
      }
      else if(dock_state == POS_UP){
         MAXDOWN = DOCK_MAX_DOWN;
         MAXUP = DOCK_MAX_UP;
      }
////////Change Dock Speed if there is a tower/////////////////////////

////////PID LOGIC//////////////////////////////////////
      currentValue = dockerMOBO.get_position();
      err = targetValue - currentValue;
      err_last = err;
      derr = (err - err_last);
      p = (DOCK_PID_KP * err);
      d = DOCK_PID_KD * derr;

      motorPower = p+i+d;

      if(motorPower < MAXUP){motorPower = MAXUP;}
      if(motorPower > MAXDOWN){motorPower = MAXDOWN;}
    //  motorPower = (motorPower > 1 ? 1 : motorPower < -1 ? -1 : motorPower);
      dockerMOBO.move(motorPower);
/////////PID LOGIC//////////////////////////////////

      pros::delay(DOCK_TASK_LOOP_DELAY);

   };
}

void Arm_Task_fn(void*param){
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
   int MAXUP = ARM_MAX_UP;
   int MAXDOWN = ARM_MAX_DOWN;
   bool Arm_Homing_Complete = false;


//////ARM HOMING SEQUENCE/////////////////
//copied from docker
   while(Arm_Homing_Complete == false  && Arm_Endstop_Min.get_value() == 0){
      sideMOBO.move_velocity(-40);
      if(Arm_Endstop_Min.get_value()==1){
         Arm_Homing_Complete = true;
         sideMOBO.move_velocity(0);
      }
   };
   sideMOBO.move_velocity(0);
   sideMOBO.tare_position();
   currentValue = sideMOBO.get_position();
   Arm_Homing_Complete = true;
/////ARM HOMING SEQUENCE///////////////////

   while(true){
      ///////Arm Position Controller/////////////
      switch(arm_state){
         case 0:
            targetValue = Arm_PID_Zero;
            break;
         case 1:
            //pos value when dock up
            targetValue = Arm_PID_Val_Tower;
            break;
         case 2:
            targetValue = Arm_PID_Val_Platform;
            break;
         default:
            arm_state = 0;
            break;
      };
///////Arm Position Controller/////////////

////////PID LOGIC//////////////////////////////////////
      currentValue = sideMOBO.get_position();
      err = targetValue - currentValue;
      err_last = err;
      derr = (err - err_last);
      p = (ARM_PID_KP * err);
      d = ARM_PID_KD * derr;

      motorPower = p+i+d;

      if(motorPower < MAXUP){motorPower = MAXUP;}
      if(motorPower > MAXDOWN){motorPower = MAXDOWN;}
    //  motorPower = (motorPower > 1 ? 1 : motorPower < -1 ? -1 : motorPower);
      sideMOBO.move(motorPower);
/////////PID LOGIC//////////////////////////////////

   }
   pros::delay(ARM_LOOP_DELAY);
}