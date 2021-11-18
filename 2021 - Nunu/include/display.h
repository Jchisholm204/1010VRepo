#ifndef _LCD_H_
#define _LCD_H_
#include <stdio.h>
#include <errno.h>
#include "display/lvgl.h"

#define NO_AUTO_SELECTED 0
extern int SelectedAuto;

#define TAB_OP 1
#define TAB_DISABLED 0
#define TAB_RERUN 2

//display class
class Display{
public:
  void setActiveTab(int tab);
  void createReRunOps(void);
  void createTitle(void);
  void createBatteryMeter(void);
  void createAutoSelector(void);
  void refresh(void);
    //create screen elements
  void createScreen(void);
};

extern void Display_Task_fn(void*param);

extern Display display;

#endif