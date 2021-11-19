#ifndef _DRIVE_H_
#define _DRIVE_H_

#define Back 0
#define Front 1

#define ORIGIN_RIGHT 0
#define ORIGIN_LEFT 1

class Chassis{
public:
  //operator drive
  void operator_Chassis(void);
  //time driven drivebase movement
  void timeDrive(int time, int leftPow, int rightPow);
  //encoder based drivebase movement with left and right pid values
  void driveTurn(int leftTarget, int maxLeft, int rightTarget, int maxRight, int timeout);
  //encoder based drivebase movement
  void move(int targetValue, int timeout);
  //encoder based drivebase movement with driveDiff
  void LineDrive(int targetValue, int timeout);
  //Lidar based drivebase movement
  void drive(int targetValue, int timeout, pros::Distance leftSensor, pros::Distance rightSensor);
  //gyro based drivebase turning with center origins
  void turn(int targetValue, int timeout);
  //gyro based turning with abs values (0-360) with center origins
  void heading(int targHeading, int offset, int timeout);
  //gyro based turning around a fixed point
  void pointTurn(int targetValue, int timeout, int origins);
  //stops all drivebase movement
  void stop(void);
  //time driven drivebase movement
  void time(int time, int velocity);

};

#endif
