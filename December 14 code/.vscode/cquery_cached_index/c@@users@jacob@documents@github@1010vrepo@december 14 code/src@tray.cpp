#include "main.h"
#include "tray.h"
int stackTarget;
int Zero;
int boi;
int expo (int joystickVal, float driveExp, int joyDead, int motorMin) { //exponential incrementation of joystick values
        int joySign;
        int joyMax = 128 - joyDead;
        int joyLive = abs(joystickVal) - joyDead;
        if (joystickVal > 0) {joySign = 1;}
        else if (joystickVal < 0) {joySign = -1;}
        else {joySign = 0;}
        int power = joySign * (motorMin + ((127 - motorMin) * (pow(joyLive, driveExp) / pow(joyMax, driveExp))));
        return power;
}
ADIDigitalIn downis('b');
//ADIPotentiometer trayPent ('d');
int LOWSTOP = 0;
int POSSAVE;
int LIFTVEL;
void Tray::opTray(void){
  	int LIFTEXP = expo(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y), 1.5 /*DriveExp*/, 8 /*JoyDead*/, 15 /*MotorMin*/); //tray expo
    if(LIFTEXP < MAXDOWN){LIFTVEL = MAXDOWN;}
    else if(LIFTEXP > MAXUP){LIFTVEL = MAXUP;}
    else {LIFTVEL = LIFTEXP;};
    /* //old logic
    if(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) > 0) {
			stacky.move(LIFTEXP);
			LOWSTOP = 0;
		}
		else if(downis.get_value() == true) {
			LOWSTOP = 1;
			stacky.move_velocity(0);
		}
		else if(LOWSTOP == 0) {
			stacky.move(LIFTEXP);
		};
    */

    if(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) > 0){ //tray up
      stacky.move_velocity(LIFTEXP);
    }
    else if(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) < 0 &&! downis.get_value()){ //tray down
      stacky.move_velocity(LIFTEXP);
    }
    else if(partner.get_digital(E_CONTROLLER_DIGITAL_B)){
      //Zero = true;
    }
    else{
      POSSAVE = stacky.get_position(); //get current tray position
      stacky.move_absolute(POSSAVE, 0); //hold current tray position
    };
/*
    if(master.get_digital(E_CONTROLLER_DIGITAL_X)){
      //cubeTray.prostack(565, 2200);
      //stacky.move_absolute(920, 80);
      stackTarget = 565;
    }
    else if(master.get_digital(E_CONTROLLER_DIGITAL_A)){
      //cubeTray.prostack(0, 1000);
      Zero = true;
    };
    */
}
int startPOS = stacky.get_position();
void Tray::stack(int trayTarget, int timeout) {
  float stackKP = 0.8; //was .7
  float stackKD = 1.2;  //was .02
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
  while(millis() - startTime < timeout){
    currentValue = stacky.get_position();
    err = stackTarget - currentValue;
    err_last = err;
    derr = (err - err_last);
    p = (stackKP * err);
    //err_sum += err;
    d = (stackKD * derr);

    motorPower = p+i+d;

    if(motorPower > 90){motorPower = 90;}
    if(motorPower < -100){motorPower = -100;}
  //  motorPower = (motorPower > 1 ? 1 : motorPower < -1 ? -1 : motorPower);
    stacky.move(motorPower);
    delay(20);
  }
}
void Tray::pid(int target, int timeout, float kP, float kI, float kD){
	int error, sumError, diffError, errorLast, output;
	int startTime = millis();
	while((millis() - startTime) < timeout){
		error = target - stacky.get_position();
		sumError += error;
		diffError = error - errorLast;
		stacky.move((error * kP) + (sumError * kI) + (diffError * kD));
		errorLast = error;
	}
}
void STACK_Task_fn(void*parameter){
		float stackKP = 0.8; //was .7
		float stackKD = 1.2;  //was .02
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
    while(true){
      currentValue = stacky.get_position();
      err = stackTarget - currentValue;
      err_last = err;
      derr = (err - err_last);
      p = (stackKP * err);
      //err_sum += err;
      d = stackKD * derr;

      motorPower = p+i+d;

      if(motorPower > MAXUP){motorPower = MAXUP;}
      if(motorPower < MAXDOWN){motorPower = MAXDOWN;}
    //  motorPower = (motorPower > 1 ? 1 : motorPower < -1 ? -1 : motorPower);
      stacky.move(motorPower);
      delay(20);
    }
}
void Tray::zero_ft(int timeout){
  int starttime = pros::millis();
  /*
  while(millis() - starttime < timeout){
    if(downis.get_new_press()){
      boi = 1;
      Zero = false;
    }
    else if(Zero == true){
      boi = 0;
    }
    else if(boi == 1){
      stacky.move_velocity(0);
    }
    else if(boi == 0){
    stacky.move_velocity(-80);
    };
  }
*/
  do {
     stacky.move_velocity(-40);
  } while(!downis.get_value() && ((millis() - starttime) < timeout));

}
