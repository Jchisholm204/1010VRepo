#ifndef _LCD_H_
#define _LCD_H_
#include <stdio.h>
#include <errno.h>
#include "display/lvgl.h"

#define NO_AUTO_SELECTED 0
extern int SelectedAuto;

extern Task display_Task;
extern void Display_Task_fn(void*param);

class Display{
public:
  void createImg(void);
  void createTabs(void);
  void setActiveTab(int tab);
  void createScreen(void);
  void createOpLEDs(void);
  void createTitle(void);
  void createAutoSelector(void);
  void createBatteryMeter(void);
  void refresh(void);
};

extern Display display;

#endif
