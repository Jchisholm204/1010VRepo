/* Ingenuity - lift.cpp
/* - main.h
/* - tasking/lift.hpp
* Everything to do with the front lift including its task and operator class
*/
#include "main.h"
#include "robot/display.h"
#include "robot/drive.hpp"
#include "robot/lift.hpp"
#include "Constants.hpp"

Lift::Lift(int maximumVelocity, float kP, float kD){
    maxVel=maximumVelocity;
    liftKp=kP;
    liftKd=kD;
    lift_manual_exemption = false;
    lift_state = 0;
    lift_state_prev = 0;
}

void Lift::manual(int velocity, bool enabled){
    lift_manual_exemption = enabled;
    if(lift_manual_exemption == true){
        liftMotor.move_velocity(velocity);
    }
}

void Lift::manual(int velocity){
    lift_manual_exemption = true;
    liftMotor.move_velocity(velocity);
}

void Lift::PID(int maxVelocity, float kP, float kD){
    maxVel=maxVelocity;
    liftKp=kP;
    liftKd=kD;
}

void Lift::up(){
    lift_state = LIFT_UP;
    lift_state_prev = 99;
}

void Lift::down(){
    lift_state = LIFT_DOWN;
    lift_state_prev = 99;
}

void Lift::preset(int state){
    lift_state = state;
    lift_state_prev = 99;
}

void Lift::targ(int NewtargetValue){
    lift_state_prev = lift_state; //make sure the lift doesent revert to presets
    targetValue = NewtargetValue; //set new lift targetvalue
}

//lift interface
Lift lift(kLift::Maximum_Velocity, kLift::kP, kLift::kD);

void Lift_Task_fn(void*param){
   int motorPower;
   int currentValue;
   int err = 0;
   int derr = 0;
   int err_last = 0;
   float p;
   float d;
   bool Oncelocal = false;

   while(true){
       printf("%d\n",LiftRotation.get_angle());
      if(lift.lift_manual_exemption == true){
         Oncelocal = false;
      }
      else if(lift.lift_manual_exemption == false && Oncelocal == false){
         lift.targetValue = LiftRotation.get_angle()/100;
         Oncelocal = true;
      }
      else{
         if(lift.lift_state != lift.lift_state_prev){
            ///////Tower Lift Position Controller/////////////
            switch(lift.lift_state){
               case 0:
                  lift.targetValue = kLift::TargetValue_Down;
                  break;
               case 1:
                  lift.targetValue = kLift::TargetValue_MidWay;
                  break;
                case 2:
                  lift.targetValue = kLift::TargetValue_Up;
                  break;
               default:
                  //do not move the lift from its current position
                  lift.lift_manual_exemption = false;
                  Oncelocal = false;
                  break;
            };
            ///////Arm Position Controller/////////////
        }
        lift.lift_state_prev = lift.lift_state;

   ////////PID LOGIC//////////////////////////////////////
        currentValue = LiftRotation.get_angle()/100;
        err = lift.targetValue - currentValue;
        derr = (err - err_last);
        err_last = err;
        p = (lift.liftKp * err);
        d = (lift.liftKd * derr);

        motorPower = p+d;

        if(motorPower < -lift.maxVel){motorPower = -lift.maxVel;}
        if(motorPower > lift.maxVel){motorPower = lift.maxVel;}
      //  motorPower = (motorPower > 1 ? 1 : motorPower < -1 ? -1 : motorPower);
        liftMotor.move(motorPower);
   /////////PID LOGIC//////////////////////////////////
      }
   pros::delay(20);
   }
}