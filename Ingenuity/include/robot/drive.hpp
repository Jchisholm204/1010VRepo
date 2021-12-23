#ifndef _DRIVEBASE_HPP
#define _DRIVEBASE_HPP

#define Back -1
#define Front 1
#define Right 0
#define Left 1

#define ORIGIN_RIGHT 0
#define ORIGIN_LEFT 1

class Chassis{
public:
  //exponential drive function
  int exponential(int joystickVal, float driveExp, int joydead, int motorMin);
  //operator drive
  void operator_Chassis(int maxVel);
  //time driven drivebase movement with different drive powers
  void time(int time, int leftPow, int rightPow);
  //time driven drivebase movement
  void time(int time, int velocity);
  //encoder based drivebase movement with left and right pid values
  void driveTurn(int leftTarget, int maxLeft, int rightTarget, int maxRight, int timeout);
  //gyro based drivebase turning with center origins
  void turn(int targetValue, int timeout);
  //pid
  void pid(int targetValue, int maxSpeed, int timeout, float kP, float kD);
  //stops all drivebase movement
  void stop(void);
};

#endif
