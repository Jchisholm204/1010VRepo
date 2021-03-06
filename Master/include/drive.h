#ifndef _DRIVE_H_
#define _DRIVE_H_
class Chassis{
public:
  void operator_Chassis(void);
  void timeDrive(int time/*the time it drives for*/, int vel/*the entered Speed*/, int cooldown/*the period that the robot should drive for a slower % of the speed*/);
  void MoveDistance(int direction, int targetValue, int speed, int timeout);
  void TurnDistance(int direction, int targetValue, int speed, int timeout);
  //void TurnGyro(int direction, int targetValue, int timeout);
  void stopDriving(void);
  void startDriving(int speed);
  void driveULT(int targetValue, ADIUltrasonic sensor, int timeout, int slowdownfactor, int slowdownValue);
  void towerDive(int stoppingValue, int slowdownfactor, int slowdownValue, int timeout);

};

#endif