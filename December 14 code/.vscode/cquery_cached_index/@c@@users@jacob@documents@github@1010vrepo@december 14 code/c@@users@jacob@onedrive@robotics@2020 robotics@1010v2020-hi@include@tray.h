#ifndef TRAY_H_
#define TRAY_H_

class Tray{
public:
  void opTray(void);
  void stack(int trayTarget, int timeout);
  void prostack(int traytarget, int timeout);
  void pid(int target, int timeout, float kP, float kI, float kD);
  void zero_ft(int timeout);
};
void STACK_Task_fn(void*parameter);
#endif
