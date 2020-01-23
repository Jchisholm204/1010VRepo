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
//lv_obj_t * battery;


void Display::createLEDs(void){
  ///////create the digital LEDs
  HighCube = lv_led_create(lv_scr_act(), NULL);
  LowCube = lv_led_create(lv_scr_act(), NULL);
  tryLmt  = lv_led_create(lv_scr_act(), NULL);
  armLmt = lv_led_create(lv_scr_act(), NULL);

////position the virtual LEDs on the screen
  lv_obj_align(HighCube, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
  lv_obj_align(LowCube, HighCube, LV_ALIGN_CENTER, 50, 0);
  lv_obj_align(tryLmt, HighCube, LV_ALIGN_CENTER, -80, 0);
  lv_obj_align(armLmt, tryLmt, LV_ALIGN_CENTER, -50, 0);

  //set the sizes of the objects
  lv_obj_set_size(HighCube, 50, 35);
  lv_obj_set_size(LowCube, 50, 35);
  lv_obj_set_size(tryLmt, 50, 35);
  lv_obj_set_size(armLmt, 50, 35);

///////create labels for the virtual LEDs
  lv_obj_t * HighCubeLabel = lv_label_create(lv_scr_act(), NULL);
  lv_obj_t * LowCubeLabel = lv_label_create(lv_scr_act(), NULL);
  lv_obj_t * tryLmtLabel = lv_label_create(lv_scr_act(), NULL);
  lv_obj_t * armLmtLabel = lv_label_create(lv_scr_act(), NULL);
  lv_obj_t * endstopLabel = lv_label_create(lv_scr_act(), NULL);

  //position the labels on the screen
  lv_obj_align(HighCubeLabel, HighCube, LV_ALIGN_CENTER, 0, 0);
  lv_obj_align(LowCubeLabel, LowCube, LV_ALIGN_CENTER, 0, 0);
  lv_obj_align(tryLmtLabel, tryLmt, LV_ALIGN_CENTER, 0, 0);
  lv_obj_align(armLmtLabel, armLmt, LV_ALIGN_CENTER, 0, 0);
  lv_obj_align(endstopLabel, HighCube, LV_ALIGN_CENTER, -30, -20);
  //set the text for the labels
  lv_label_set_text(HighCubeLabel, "HighCube");
  lv_label_set_text(LowCubeLabel, "LowCube");
  lv_label_set_text(tryLmtLabel, "Tray");
  lv_label_set_text(armLmtLabel, "Arm");
  lv_label_set_text(endstopLabel, "Endstops:");

}

void Display::createTitle(void){
  lv_obj_t * victors = lv_label_create(lv_scr_act(), NULL);
  lv_obj_set_size(victors, 100, 70);
  lv_obj_align(victors, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_label_set_text(victors, "TEN TON ROBOTICS");
}

/*Here is where we define all of our batetry objects*/
lv_obj_t * batteryMeter;
lv_obj_t * batteryMeterLabel;
lv_obj_t * symbolLabel;
void Display::createBatteryMeter(void){
  batteryMeter = lv_lmeter_create(lv_scr_act(), NULL);
  batteryMeterLabel = lv_label_create(batteryMeter, NULL);
  symbolLabel = lv_label_create(batteryMeter, NULL);
  lv_lmeter_set_range(batteryMeter, 0, 100);                   /*Set the range*/
  lv_lmeter_set_value(batteryMeter, 75);                       /*Set the current value*/
  lv_lmeter_set_scale(batteryMeter, 240, 31);                  /*Set the angle and number of lines*/
  lv_obj_set_size(batteryMeter, 150, 150);                     /*Set the size of the meter*/
  lv_obj_align(batteryMeter, NULL, LV_ALIGN_CENTER, 0, 0);    /*align the meter*/
  lv_obj_align(batteryMeterLabel, batteryMeter, LV_ALIGN_CENTER, 0, 0);
  lv_obj_align(symbolLabel, batteryMeterLabel, LV_ALIGN_CENTER, 0, 0);
  lv_label_set_text(symbolLabel, "Battery");
}

void Display::createDisplay(void){
  lv_theme_t *th = lv_theme_zen_init(40/*theme color*/, NULL); //change default theme to (zen) theme
  //call to all of the functions that create objects
  //createTitle(); //
  createLEDs();
  createBatteryMeter();

}

void Display::refresh(void) //refreshes values sent to the screen
{

    if(TrayDownLimit.get_value() == HIGH){ //if the tray is in the zero position (very bottom) turn on the tray led
      lv_led_on(tryLmt);
    }
    else{lv_led_off(tryLmt);}

    if(top.get_value() > 2000){ //if the top cube sensor is triggered, turn on the led
      lv_led_on(HighCube);
    }
    else{
      lv_led_off(HighCube); //turn the led off if it isnt triggered
    }

    if(bottom.get_value() < 2000){ //if the bottom cube sensor is triggered, activate the led
      lv_led_on(LowCube);
    }
    else{
      lv_led_off(LowCube); //turn the led off if it isnt triggered
    }

    if(armLimit.get_value() == HIGH){ //if the arm limit switch sensor is triggered, activate the led
      lv_led_on(armLmt);
    }
    else{
      lv_led_off(armLmt); //turn the led off if it isnt triggered
    }

    int level = pros::battery::get_capacity(); //get the capacity of the battery
    lv_lmeter_set_value(batteryMeter, level); //set the meter to display the level of the battery
    lv_label_set_text(batteryMeterLabel, (std::to_string(level)+"%").c_str()); //display the battery %

}
