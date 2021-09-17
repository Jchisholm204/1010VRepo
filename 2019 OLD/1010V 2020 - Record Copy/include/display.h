#ifndef _LCD_H_
#define _LCD_H_
#include <stdio.h>
#include <errno.h>


#define NO_AUTO_SELECTED 0
extern int SelectedAuto;
extern int autoLength;



class Display{
public:
  void createTabs(void);
  void setActiveTab(int tab);
  void createScreen(void);
  void createLabels(void);
  void createAutoSelector(void);
  void createBatteryMeter(void);
  void refresh(void);
};

#endif
