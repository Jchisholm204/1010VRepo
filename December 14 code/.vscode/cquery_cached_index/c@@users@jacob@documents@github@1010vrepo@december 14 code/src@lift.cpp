//#include "main.h"
#include "lift.h"
#include "main.h"
#include "intakes.h"
//int HOLD_POS_ARM = lifty.get_position();
int STARTINGPOS = lifty.get_position(); //get starting position of the motor
int targetboi;
int lasttarg;
ADIDigitalIn boistop('a'); //int boistop = arm down limit switch
void operatorLift(){}
void RobotLift::opLift(void){
  int HOLDARM;  //int chamber value for pid control
  /*
  if(master.get_digital(E_CONTROLLER_DIGITAL_L1)) { //move arm up - master L1
    lifty.move_velocity(100);
  }

  else if(master.get_digital(E_CONTROLLER_DIGITAL_L2) && !boistop.get_value()) { //move arm down && !arm limit switch  - master L2
    lifty.move_velocity(-100);
  }
  else if(partner.get_digital(E_CONTROLLER_DIGITAL_DOWN)){ //set zero position of the motor to adjust the height mid match
    //lifty.move_absolute(STARTINGPOS, 100);
    lifty.tare_position();
  }
  */
if(partner.get_digital(E_CONTROLLER_DIGITAL_RIGHT)){
  if(partner.get_digital(E_CONTROLLER_DIGITAL_L1)){
    lifty.move_velocity(100);
  }
  else if(partner.get_digital(E_CONTROLLER_DIGITAL_L2)){
    lifty.move_velocity(-100);
  }
  else if(partner.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
    lifty.tare_position();
    STARTINGPOS = lifty.get_position();
  }
  else{
    HOLDARM = lifty.get_position();
    lifty.move_absolute(HOLDARM, 0);
  }

}
else{
    if(master.get_digital(E_CONTROLLER_DIGITAL_L2)) { //move arm down && !arm limit switch  - master L2
      //lasttarg = targetboi;
      targetboi = 0;
      //lifty.move_velocity(-100);
      //targetboi = 0;
      //lifty.move_absolute(STARTINGPOS, 100);
    }
    else if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)) { //move arm up - master L1
      //lifty.move_velocity(100);
      targetboi+= 1;
    }
    else if(targetboi == 1){
      lifty.move_absolute(430 + STARTINGPOS, 100);
      //proLift(LOWTOWER, 100);
      outTake = true;
    }

    else if(targetboi == 2){
      lifty.move_absolute(580 + STARTINGPOS, 100);
      //proLift(MIDTOWER, 100);
    }
    else if(targetboi == 3){
      lifty.move_absolute((390 + STARTINGPOS), 100);
      //proLift((LOWTOWER - 70), 100);
    }
    else if(targetboi == 4){
      targetboi = 0;
    }
    else if(targetboi == 0){
      lifty.move_absolute(STARTINGPOS, 100);
      //proLift(STARTINGPOS, 90);
    };
  }
}
void RobotLift::proLift(int targetValue, int timeout){
		float stackKP = 0.7;
		float stackKD = 0.02;
    //same PID Logic as turnValue
    int motorPower;
    int startTime = millis();
    int currentValue = 0;
    int err = 0;
    int derr = 0;
    int err_last = 0;
    int err_sum = 0;
    float KI = 0;
    float p;
    float i = 0;
    float d;
    //stacky.tare_position();
    while((millis() - startTime) < timeout){
      currentValue = lifty.get_position();
      err = targetValue - currentValue;
      err_last = err;
      derr = (err - err_last);
      p = (stackKP * err);
      //err_sum += err;
      d = stackKD * derr;

      motorPower = p+d;

      if(motorPower > 127){motorPower = 127;}
      if(motorPower < -127){motorPower = -127;}
    //  motorPower = (motorPower > 1 ? 1 : motorPower < -1 ? -1 : motorPower);
      lifty.move(motorPower);
      delay(20);
    }
}
void RobotLift::zero(void){
  int startTime = millis();
  int boi = 0;
  while((millis() - startTime) < 2000){
    if(boistop.get_new_press()){
      boi = 1;
    }
    else if(boi == 1){
      lifty.move_velocity(0);
    }
    else if(boi == 0){
    lifty.move_velocity(-80);
    };
  }
}
