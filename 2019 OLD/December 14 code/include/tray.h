#ifndef TRAY_H_
#define TRAY_H_

class Tray{
public:
  void opTray(void); //operator tray function
  void pid(int target, int timeout, float kP, float kI, float kD); //tray stack function
};
#endif
