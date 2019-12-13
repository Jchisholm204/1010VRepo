#ifndef LIFT_H_
#define LIFT_H_

class RobotLift{
public:
  void opLift(void);
  void proLift(int liftTarget, int velocity);
  void zero(void);
};
#endif
