/* Aura - lift.cpp
/* - main.h
/* - tasking/lift.hpp
* Everything to do with the front lift including its task and operator class
*/
#include "main.h"
#include "robot/display.h"
#include "robot/drive.hpp"
#include "tasking/lift.hpp"

Lift::Lift(int maximumVelocity, float nkP, float nkD, int iState, bool wait){
    maxVel=maximumVelocity;
    kP=nkP;
    kD=nkD;
    manual_exemption = false;
    if(wait == true){
        state = iState;
        state_prev = iState;
    }
    else{
        state = iState;
        state_prev = 99;
    }
}

Lift::Lift(int maximumVelocity, float nkP, float nkD){
    maxVel=maximumVelocity;
    kP=nkP;
    kD=nkD;
    manual_exemption = false;
    state = 5;
    state_prev = 99;
}

void Lift::manual(int velocity, bool enabled){
    manual_exemption = enabled;
    if(manual_exemption == true){
        liftMotorL.move_velocity(velocity);
        liftMotorR.move_velocity(velocity);
    }
}

void Lift::manual(int velocity){
    manual_exemption = true;
    liftMotorL.move_velocity(velocity);
    liftMotorR.move_velocity(velocity);
}

void Lift::PID(int maxVelocity, float nkP, float nkD){
    maxVel=maxVelocity;
    kP=nkP;
    kP=nkD;
}

void Lift::up(){
    state = LIFT_UP;
    state_prev = 99;
}

void Lift::down(){
    state = LIFT_DOWN;
    state_prev = 99;
}

void Lift::preset(int nstate){
    state = nstate;
    state_prev = 99;
}

void Lift::targ(int NewtargetValue){
    state_prev = state; //make sure the lift doesent revert to presets
    targetValue = NewtargetValue; //set new lift targetvalue
}


//lift interface
Lift lift(100, 1.8, 0.8, LIFT_UP, true);

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
      if(lift.manual_exemption == true){
         Oncelocal = false;
      }
      else if(lift.manual_exemption == false && Oncelocal == false){
         lift.targetValue = LiftPOT.get_value();
         Oncelocal = true;
      }
      else{
         if(lift.state != lift.state_prev){
            ///////Tower Lift Position Controller/////////////
            switch(lift.state){
               case LIFT_UP:
                  //starting position (all the way up [impacts intakes])
                  lift.targetValue = 580;
                  break;
               case LIFT_HOLD:
                  lift.targetValue = 3000;
                  break;
               case LIFT_DOWN:
                  lift.targetValue = 3900;
                  break;
               default:
                  //do not move the lift from its current position
                  lift.manual_exemption = false;
                  Oncelocal = false;
                  break;
            };
            ///////Arm Position Controller/////////////
        }
        lift.state_prev = lift.state;

   ////////PID LOGIC//////////////////////////////////////
        currentValue = LiftPOT.get_value();
        err = lift.targetValue - currentValue;
        derr = (err - err_last);
        err_last = err;
        p = (lift.kP * err);
        d = (lift.kD * derr);

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