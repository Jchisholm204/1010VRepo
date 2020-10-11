#include "main.h"
#include "drive.h"

int exponential(int joystickVal, float driveExp, int joydead, int motorMin){
  int joySign;
  int joyMax = 128 - joydead;
  int joyLive = abs(joystickVal) - joydead;
  if(joystickVal > 0){joySign = 1;}
  else if(joystickVal < 0){joySign = -1;}
  else{joySign = 0;}
  int power = joySign * (motorMin + ((127 - motorMin) * (pow(joyLive, driveExp) / pow(joyMax, driveExp))));
  return power;
}

void Chassis::operator_Chassis(void){
  int Yval = exponential(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), 1.5 /*DriveExp*/, 8 /*JoyDead*/, 15 /*MotorMin*/);
  int Xval = exponential(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X), 1.5, 8, 15);

  driveLB.move_velocity(Yval + Xval);
  driveLF.move_velocity(Yval + Xval);
  driveRB.move_velocity(Yval - Xval);
  driveRF.move_velocity(Yval - Xval);
}
void Chassis::timeDrive(int time, int vel){
  driveLB.move_velocity(vel);
  driveLF.move_velocity(vel);
  driveRB.move_velocity(vel);
  driveRF.move_velocity(vel);
//drive for 85% of the time at entered speed^
  delay(time*0.85);

  driveLB.move_velocity(vel*0.25);
  driveLF.move_velocity(vel*0.25);
  driveRB.move_velocity(vel*0.25);
  driveRF.move_velocity(vel*0.25);
//drive for last 15% of time at 25% entered speed^
  delay(time*0.15);
//stop
  driveLB.move_velocity(0);
  driveLF.move_velocity(0);
  driveRB.move_velocity(0);
  driveRF.move_velocity(0);
}
