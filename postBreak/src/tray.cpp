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
 int err = 0;
 int err_last = 0;
 int currentValue;
 int targetValue;
 int motorPower;
 int cap;
 int derr;
 int trayTarget;
 int TrayAutoTarget;
 bool TrayZero = false;
 bool TrayOP;

 while(true){
   if(competition::is_autonomous()){TrayOP = false;}
   else{TrayOP = true;}

   currentValue = TrayMotor.get_position();  //get value from trayPent --- changed from tray motor encoder for improved accuracy
/*
   if(TrayZero == true){
     while(TrayDownLimit.get_value() == false){
       TrayMotor.move_velocity(-80);
     }
     TrayMotor.move_velocity(0);
     TrayMotor.tare_position();
     trayPos.calibrate();
   }*/
   if (TrayOP == true){

     int LIFTEXP = expo(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y), 1.5 /*DSiveExp*/, 8 /*JoyDead*/, 15 /*MotorMin*/); //tray expo

     if(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) > 0 &&! TrayUpLimit.get_value()){ //if the joystick is above 0 (moving up); watch to see that the up limit isnt toggled
        TrayMotor.move_velocity(LIFTEXP); //move the tray motor with the expo output
      }
      else if(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) < 0 &&! TrayDownLimit.get_value()){ //if the joystick is in the down position; stop the action if the down switch it toggled
        TrayMotor.move_velocity(LIFTEXP); //move the tray motor with the expo output
      }
      else{
        TrayMotor.move_velocity(0);
      }
   }
   else if(competition::is_autonomous()){
     targetValue = TrayAutoTarget;

     if((currentValue > 350)){ //if  we're past appx. halfway
       cap = 50; //slow down so we don't knock down the tower
     }
     else{
       cap = 127; //otherwise move normally
     };

     err = targetValue - currentValue; //error is delta of target and current positions
     err_last = err; //store last error
     derr = err - err_last; //difference of errors over iterations
     motorPower = (0.7 * err) + (1.35 * derr); //PD constants plus our variables
     motorPower = motorPower > cap ?  cap : motorPower < -127 ? -127 : motorPower; //caps output at +cap, -127

     if((TrayUpLimit.get_value() == HIGH)){  //if our active stop variable is true
       TrayMotor.move(0); //stop movement, to prevent the motor from overheating
     }
     else{
       TrayMotor.move(motorPower); //move the lift equal to motorPower
     }
 }
}
}

/*
CREDIT:
Caden H.
"github.com/cadenhewlett/CHPersonal/"

Credit for the PD controller here goes to Caden H. Owner of the "CHPersonal" Repository
The code here is a modifyed version of the PD controller found in "1010A_2019_Dec9"
*/
