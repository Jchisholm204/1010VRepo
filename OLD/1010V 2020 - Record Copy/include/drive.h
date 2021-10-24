#ifndef _DRIVE_H_
#define _DRIVE_H_
class Chassis{
public:
  void operator_Chassis(void);
  void timeDrive(int time, int velocity);
  void MoveDistance(int direction, int targetValue, int timeout);
  void TurnDistance(int direction, int targetValue, int timeout);
  void timeGlide(int time, int velocity);
  void MoveSlow(int direction, int targetValue, int timeout);
  void stopDriving(void);
};
#endif
