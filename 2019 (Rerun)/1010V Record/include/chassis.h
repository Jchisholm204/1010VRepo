#ifndef _CHASSIS_H_
#define _CHASSIS_H_

class Chassis{
public:
  void OP_Chassis(void);
  void timeDrive(int time, int velocity);
  void MoveDistance(int direction, int targetValue, int speed, int timeout);
  void TurnDistance(int direction, int targetValue, int speed, int timeout);
  void TurnGyro(int direction, int targetValue, int timeout);
  void timeGlide(int time, int velocity);
  void stopDriving(void);
  void angleDrive(int motor, int velocity, int time);
  void drive(int input, int target, int timeout, float kP, float kI, float kD);
  void MoveSlow(int direction, int targetValue, int speed, int timeout);
  void switchDrive(int Mode, int direction, int targetValue, int timeout, float KP, float KD);

};

#endif
