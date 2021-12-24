#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include <stdio.h>
#include <errno.h>
#include "display/lvgl.h"

#define NO_AUTO_SELECTED 0
extern int SelectedAuto;

#define TAB_OP 1
#define TAB_DISABLED 0

extern lv_obj_t * recording_enabled_btn;

//display class
class Display{
public:
  void setActiveTab(int tab);
  void createReRunOps(void);
  //display an error popup on the brain screen that lasts for 3 seconds
  void msg(const char *displayMsg);
  //display a popup message on the brain screen for a given time
  void msg(const char *displayMsg, int MsgTimeout);
  void createTitle(void);
  void createBatteryMeter(void);
  void createAutoSelector(void);
  void refresh(void);
    //create screen elements
  void createScreen(void);
  //return "true" if recording enabed by display button
  bool recordingSelected(void);
};

extern Display display;

#endif
