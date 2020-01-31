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
void trayPreset_fn(void*param){
 while(true){
     int LIFTEXP = expo(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y), 1.5 /*DSiveExp*/, 8 /*JoyDead*/, 15 /*MotorMin*/); //tray expo

     if(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) > 0){ //if the joystick is above 0 (moving up); watch to see that the up limit isnt toggled
        TrayMotor.move_velocity(LIFTEXP); //move the tray motor with the expo output
      }
      else if(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) < 0 &&! TrayDownLimit.get_value()){ //if the joystick is in the down position; stop the action if the down switch it toggled
        TrayMotor.move_velocity(LIFTEXP); //move the tray motor with the expo output
      }
      else{
        TrayMotor.move_velocity(0);
      }
   }
 }
