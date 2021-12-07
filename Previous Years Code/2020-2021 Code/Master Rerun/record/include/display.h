#ifndef _LCD_H_
#define _LCD_H_
#include <stdio.h>
#include <errno.h>
#include "display/lvgl.h"

#define NO_AUTO_SELECTED 0
extern int SelectedAuto;
extern lv_obj_t * lLED;
extern lv_obj_t * rLED;


class Display{
public:
  void createImg(void);
  void createTabs(void);
  void setActiveTab(int tab);
  void createScreen(void);
  void createOpLEDs(void);
  void createTitle(void);
  void DistanceReadout(void);
  void createAutoSelector(void);
  void createBatteryMeter(void);
  void refresh(void);
};

#endif
