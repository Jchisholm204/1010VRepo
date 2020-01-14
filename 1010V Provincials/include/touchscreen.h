#ifndef TOUCHSCREEN_H_
#define TOUCHSCREEN_H_
#include <stdio.h>
#include <errno.h>

//Autos
#define NO_AUTO_SELECTED 0
#define RED_FRONT 1
#define BLUE_FRONT 2
#define RED_BACK 3
#define BLUE_BACK 4
#define SKILLS_AUTO 5

class Screen{
public:
  void setActiveTab(int tab);
  void createTabs(void);
  void createBars(void);
  void createScreen(void);
  void createOpLEDs(void);
  void createBackground(void);
  void createTitle(void);
  void createAutoSelector(void);
  void createBatteryMeter(void);
  void refresh(void);

};
#endif
