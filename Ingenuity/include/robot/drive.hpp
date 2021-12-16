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
  //operator drive
  void operator_Chassis(int maxVel);
  //time driven drivebase movement
  void timeDrive(int time, int leftPow, int rightPow, bool use_NewFront = true);
  //encoder based drivebase movement with left and right pid values
  void driveTurn(int leftTarget, int maxLeft, int rightTarget, int maxRight, int timeout, bool use_NewFront = true);
  //gyro based drivebase turning with center origins
  void turn(int targetValue, int timeout);
  //pid
  void pid(int targetValue, int maxSpeed, int timeout, float kP, float kD);
  //stops all drivebase movement
  void stop(void);
  //time driven drivebase movement
  void time(int time, int velocity);
};

#endif
