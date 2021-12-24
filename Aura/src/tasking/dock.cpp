/* Aura - dock.cpp
/* - main.h
/* - tasking/dock.hpp
* Everything to do with the rear mogo lifter (dock)
*/
#include "main.h"
#include "robot/display.h"
#include "robot/drive.hpp"
#include "tasking/dock.hpp"

Docker::Docker(int maximumVelocity, float nkP, float nkD, int iState, bool wait){
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

Docker::Docker(int maximumVelocity, float nkP, float nkD){
    maxVel=maximumVelocity;
    kP=nkP;
    kD=nkD;
    manual_exemption = false;
    state = 5;
    state_prev = 99;
}

void Docker::manual(int velocity, bool enabled){
    manual_exemption = enabled;
    if(manual_exemption == true){
        dockerMotor.move_velocity(velocity);
    }
}

void Docker::manual(int velocity){
    manual_exemption = true;
    dockerMotor.move_velocity(velocity);
}

void Docker::PID(int maxVelocity, float nkP, float nkD){
    maxVel=maxVelocity;
    kP=nkP;
    kP=nkD;
}

void Docker::up(){
    state = DOCK_UP;
    state_prev = 99;
}

void Docker::down(){
    state = DOCK_DOWN;
    state_prev = 99;
}

void Docker::preset(int nstate){
    state = nstate;
    state_prev = 99;
}

void Docker::targ(int NewtargetValue){
    state_prev = state; //make sure the dock doesent revert to presets
    targetValue = NewtargetValue; //set new dock targetvalue
}

int Docker::home_tare(int homeSpeed){
    bool homing_complete = false;
    dockerMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    while(homing_complete == false){
        if(dock_limit_switch.get_value() == 1){
            dockerMotor.move_velocity(0);
            dockerMotor.tare_position();
            homing_complete = true;
        }
        else{
            dockerMotor.move_velocity(homeSpeed);
        }
    }
    return dockerMotor.get_position();
}

//dock interface
Docker dock(100, 1.8, 0.8, DOCK_UP, false);

void Dock_Task_fn(void*param){
   int motorPower;
   int currentValue;
   int err = 0;
   int derr = 0;
   int err_last = 0;
   float p;
   float d;
   bool Oncelocal = false;

   while(true){
      if(dock.manual_exemption == true){
         Oncelocal = false;
      }
      else if(dock.manual_exemption == false && Oncelocal == false){
         dock.targetValue = dockerMotor.get_position();
         Oncelocal = true;
      }
      else{
         if(dock.state != dock.state_prev){
            ///////Tower dock Position Controller/////////////
            switch(dock.state){
               case DOCK_DOWN:
                  dock.targetValue = 480;
                  break;
               case DOCK_UP:
                  dock.targetValue = 0;
                  currentValue = dock.home_tare(-100);
                  break;
               default:
                  //do not move the dock from its current position
                  dock.manual_exemption = false;
                  Oncelocal = false;
                  break;
            };
        }
        dock.state_prev = dock.state;

   ////////PID LOGIC//////////////////////////////////////
        currentValue = LiftPOT.get_value();
        err = dock.targetValue - currentValue;
        derr = (err - err_last);
        err_last = err;
        p = (dock.kP * err);
        d = (dock.kP * derr);

        motorPower = p+d;

        if(motorPower < -dock.maxVel){motorPower = -dock.maxVel;}
        if(motorPower > dock.maxVel){motorPower = dock.maxVel;}

        dockerMotor.move(motorPower);

   /////////PID LOGIC//////////////////////////////////
      }
   pros::delay(20);
   }
}