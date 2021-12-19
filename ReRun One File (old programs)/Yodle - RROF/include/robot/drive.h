#ifndef DRIVE_H
#define DRIVE_H

#define Back -1
#define Front 1
#define Right 0
#define Left 1

#define ORIGIN_RIGHT 0
#define ORIGIN_LEFT 1

class Chassis{
public:
  //operator drive
  void operator_Chassis(void);
  //Flips Front of Robot
  void flip(int NewFront, bool swapLidars = true);
  //time driven drivebase movement
  void timeDrive(int time, int leftPow, int rightPow, bool use_NewFront = true);
  //encoder based drivebase movement with left and right pid values
  void driveTurn(int leftTarget, int maxLeft, int rightTarget, int maxRight, int timeout, bool use_NewFront = true);
  //encoder based drivebase movement
  void move(int targetValue, int timeout, bool use_NewFront = true);
  //encoder based drivebase movement with driveDiff
  void LineDrive(int targetValue, int timeout);
  //Lidar based drivebase movement
  void drive(int targetValue, int timeout, bool use_NewFront = true);
  //gyro based drivebase turning with center origins
  void turn(int targetValue, int timeout);
  //gyro based turning with abs values (0-360) with center origins
  void heading(int targHeading, int offset, int timeout);
  //gyro based turning around a fixed point (Drive in a Circle)
  void turnDrive(int turnDeg, int innerPower, int outterPower, int timeout, bool use_NewFront = true);
  //pid
  void pid(int targetValue, int maxSpeed, int timeout, float kP, float kD);
  //stops all drivebase movement
  void stop(void);
  //time driven drivebase movement
  void time(int time, int velocity);

};

#endif
