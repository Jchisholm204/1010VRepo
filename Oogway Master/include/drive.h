#ifndef _DRIVE_H_
#define _DRIVE_H_

class Chassis{
public:
  //operator drive
  void operator_Chassis(void);
  //time driven drivebase movement
  void timeDrive(int time, int leftPow, int rightPow);
  //lidar based drivebase movement
  void drive(int targetValue, int timeout);
  //encoder based drivebase movement
  void move(int targetValue, int timeout);
  //gyro based drivebase turning
  void turn(int targetValue, int timeout);
  //lidar based drivebase turning+movement
  void twrAlign(int timeout, int leftTarg, int rightTarg);
  //lidar based drivebase turning
  void fenceAlign(int timeout);
  //time driven drivebase movement
  void time(int time, int velocity);
  //gyro based turning with abs values (0-360)
  void heading(int targHeading, int offset, int timeout);
  //stops all drivebase movement
  void stop(void);

};

#endif
