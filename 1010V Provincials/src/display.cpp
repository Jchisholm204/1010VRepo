//include definition files
#include "main.h"
#include "display.h"
#include <string.h>

//////int display objects
lv_obj_t * HighCube;
lv_obj_t * LowCube;
//limit switches
lv_obj_t * tryLmt;
lv_obj_t * armLmt;
//battery persentage
lv_obj_t * battery;


void Display::createLEDs(){
  ///////create the digital LEDs
  HighCube = lv_led_create(NULL, NULL);
  LowCube = lv_led_create(NULL, NULL);
  tryLmt  = lv_led_create(NULL, NULL);
  armLmt = lv_led_create(NULL, NULL);

////position the virtual LEDs on the screen
  lv_obj_align(HighCube, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);
  lv_obj_align(LowCube, HighCube, LV_ALIGN_CENTER, 0, 50);
  lv_obj_align(tryLmt, HighCube, LV_ALIGN_CENTER, 0, -50);
  lv_obj_align(armLmt, tryLmt, LV_ALIGN_CENTER, 0, -50);

  //set the sizes of the objects
  lv_obj_set_size(HighCube, 50, 35);
  lv_obj_set_size(LowCube, 50, 35);
  lv_obj_set_size(tryLmt, 50, 35);
  lv_obj_set_size(armLmt, 50, 35);

  //make labels for the virtual LEDs
  lv_obj_t * HighCubeLabel = lv_label_create(NULL, NULL);
  lv_obj_t * LowCubeLabel = lv_label_create(NULL, NULL);
  lv_obj_t * 
}
