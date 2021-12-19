/* Ingenuity - lift.cpp
/* - main.h
/* - tasking/lift.hpp
* Everything to do with the front lift including its task and operator class
*/
#include "main.h"
#include "robot/display.h"
#include "robot/drive.hpp"
#include "tasking/pneumatics.hpp"
#include "tasking/lift.hpp"

Lift::Lift(int maximumVelocity, float kP, float kD){
    maxVel=maximumVelocity;
    liftKp=kP;
    liftKd=kD;
    lift_manual_exemption = false;
    lift_state = 5;
    lift_state_prev = 5;
}

void Lift::manual(int velocity, bool enabled){
    lift_manual_exemption = enabled;
    if(lift_manual_exemption == true){
        liftMotorL.move_velocity(velocity);
        liftMotorR.move_velocity(velocity);
    }
}

void Lift::manual(int velocity){
    lift_manual_exemption = true;
    liftMotorL.move_velocity(velocity);
    liftMotorR.move_velocity(velocity);
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
Lift lift(100, 1.8, 0.8);

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
      if(lift.lift_manual_exemption == true){
         Oncelocal = false;
      }
      else if(lift.lift_manual_exemption == false && Oncelocal == false){
         lift.targetValue = LiftPOT.get_value();
         Oncelocal = true;
      }
      else{
         if(lift.lift_state != lift.lift_state_prev){
            ///////Tower Lift Position Controller/////////////
            switch(lift.lift_state){
               case 5:
                  //starting position (all the way up [impacts intakes])
                  lift.targetValue = 580;
                  break;
               case 0:
                  //pos value when holding holding mogo (half way up)
                  lift.targetValue = 3000;
                  break;
               case 1:
                  //pos value for grabbing mobo's (when all the way down)
                  lift.targetValue = 3900;
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
        currentValue = LiftPOT.get_value();
        err = lift.targetValue - currentValue;
        derr = (err - err_last);
        err_last = err;
        p = (lift.liftKp * err);
        d = (lift.liftKd * derr);

        motorPower = p+d;

        if(motorPower < -lift.maxVel){motorPower = -lift.maxVel;}
        if(motorPower > lift.maxVel){motorPower = lift.maxVel;}
      //  motorPower = (motorPower > 1 ? 1 : motorPower < -1 ? -1 : motorPower);
        liftMotorL.move(motorPower);
        liftMotorR.move(motorPower);
   /////////PID LOGIC//////////////////////////////////
      }
   pros::delay(20);
   }
}