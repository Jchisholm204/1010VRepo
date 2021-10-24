#include "tray.h"
#include "main.h"
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
int err = 0;
 int err_last = 0;
 int currentValue;
 int targetValue;
 bool buttonStop = false;
 int motorPower;
 int cap;
 int derr;

void trayPreset_fn(void*param){
 while(true){
   if(competition::is_autonomous()){}
   else{
       int LIFTEXP = expo(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y), 1.5 /*DSiveExp*/, 8 /*JoyDead*/, 15 /*MotorMin*/); //tray expo

       if(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) > 0){ //if the joystick is above 0 (moving up)
          TrayMotor.move_velocity(LIFTEXP); //move the tray motor with the expo output
        }
        else if(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) < 0){ //if the joystick is in the down position
          TrayMotor.move_velocity(LIFTEXP); //move the tray motor with the expo output
        }
        else{
          TrayMotor.move_velocity(0);
        };
        if(partner.get_digital(E_CONTROLLER_DIGITAL_R2)){
          TrayMotor.tare_position();
        };
   }
 }
}
