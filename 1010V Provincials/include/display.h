#pragma once
#include <stdio.h>
#include <errno.h>


//Autos
#define NO_AUTO 0
#define RED_FRONT 1
#define BLUE_FRONT 2
#define RED_BACK 3
#define BLUE_BACK 4
#define SKILLS 5

class Display{
public:
  //use these functions to create objects on the screen
  void createDisplay(void);
  void createLEDs(void);
  void createTitle(void);
  void createBatteryMeter(void);
////use these function to manipulate those objects
  void refresh(void);

};
