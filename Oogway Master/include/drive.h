#ifndef _DRIVE_H_
#define _DRIVE_H_

class Chassis{
public:
  void operator_Chassis(void);
  void timeDrive(int time, int leftPow, int rightPow);
  void drive(int targetValue, int timeout);
  void move(int targetValue, int timeout);
  void turn(int targetValue, int timeout);
  void twrAlign(int timeout, int leftTarg, int rightTarg);
  void fenceAlign(int timeout);
  void time(int time, int velocity);
  void heading(int targHeading, int offset, int timeout);
  void stop(void);

};

#endif
