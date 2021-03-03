/*
Thanks to Caden H. and 1010A for this display code.
All of the code here is baised off of his and much of what is here would not be possible without him.
Please see:
https://github.com/cadenhewlett/CHPersonal/tree/master/ScreenStuff
*/


#include "main.h"
#include "display.h"
#include <string.h>
int SelectedAuto;
int autoLength;

lv_obj_t * tabs = lv_tabview_create(lv_scr_act(), NULL);
lv_obj_t * disabled_tab = lv_tabview_add_tab(tabs, "RECORD AUTO");
lv_obj_t * sys_battery_meter;
lv_obj_t * bat_meter_label;
lv_obj_t * intakeLED;
lv_obj_t* autoDuration;
lv_obj_t* selectedAuto;
lv_obj_t* autoL;
lv_obj_t* sAuto;

lv_res_t autoSelect_action(lv_obj_t * selector){
  SelectedAuto = lv_roller_get_selected(selector);

  return LV_RES_OK;
}

void Display::createBatteryMeter(void){
  sys_battery_meter = lv_lmeter_create(disabled_tab, NULL);
  bat_meter_label = lv_label_create(sys_battery_meter, NULL);
  lv_obj_t * symbol_label =  lv_label_create(sys_battery_meter, NULL);
  lv_lmeter_set_range(sys_battery_meter, 0, 100);
//  lv_obj_set_size(sys_battery_meter, 80, 80);
  lv_obj_align(sys_battery_meter, NULL, LV_ALIGN_CENTER, -150, 0);
  lv_obj_align(bat_meter_label, sys_battery_meter, LV_ALIGN_CENTER, 0, -10);
  lv_obj_align(symbol_label, bat_meter_label, LV_ALIGN_CENTER, -10, 20);
  lv_lmeter_set_value(sys_battery_meter, 75);
  //lv_label_set_text(bat_meter_label, SYMBOL_BATTERY_2);
  lv_label_set_text(symbol_label, "Battery");
//lv_obj_align(bat_meter_label, sys_battery_meter, LV
}
void Display::createAutoSelector(void){
  lv_obj_t * autoSelector = lv_roller_create(disabled_tab, NULL); //create auto selector
  lv_roller_set_options(autoSelector, "\nRed\nBlue\nSkills\nTest"); //set options for the array
  /*
  * Some Notes about the auto selector:
  * The auto selector works by setting a numeral value to the variable "SelectedAuto"
  * The first value is zero, and the values increase by 1 every time
  * This value then controls a switch case in the autoRun function.
  * To add new autos, they must be added in three places;
  * First here, after the last auto, but they must go before NoAuto
  * Then, there also needs to be a new case added to the autoselector in the autoRun function
  * Finaly, a text file with the name you gave it within the switch case needs to be set up on the SD card
  */
  lv_obj_set_width(autoSelector, 80);
  lv_roller_set_visible_row_count(autoSelector, 4);
  lv_roller_set_action(autoSelector, autoSelect_action);
  lv_obj_align(autoSelector, NULL , LV_ALIGN_CENTER, -25, 0);
}

void Display::createLabels(void){
  autoDuration = lv_label_create(disabled_tab, NULL);
  selectedAuto = lv_label_create(disabled_tab, NULL);
  lv_obj_align(autoDuration, NULL, LV_ALIGN_CENTER, 50, 10);
  lv_obj_align(selectedAuto, NULL, LV_ALIGN_CENTER, 50, -60);

  autoL = lv_label_create(disabled_tab, NULL);
  sAuto = lv_label_create(disabled_tab, NULL);
  lv_obj_align(autoL, autoDuration,LV_ALIGN_CENTER, 0, 30);
  lv_obj_align(sAuto, selectedAuto, LV_ALIGN_CENTER, 0, 30);

  lv_label_set_text(autoDuration, "Auto Length:");
  lv_label_set_text(selectedAuto, "Selected Auto:");
  lv_label_set_text(autoL, "UNKNOWN");
  lv_label_set_text(sAuto, "UNKNOWN");

}
void Display::refresh(void)
{
  int level = pros::battery::get_capacity();
  lv_lmeter_set_value(sys_battery_meter, level);

  lv_label_set_text(autoL, std::to_string(autoLength).c_str()); //just placing the variable in does not work
  lv_label_set_text(sAuto, std::to_string(SelectedAuto).c_str()); //you must insert it as a c string

  //lv_label_set_text(sAuto, "Unknown");
  lv_label_set_text(bat_meter_label, (std::to_string(level)+"%").c_str()); //Thanks to Caden H for coming up with this fix
//lv_lmeter_set_value(bat_meter_label, level);
  delay(20);
}
void Display::setActiveTab(int tab){
  lv_tabview_set_tab_act(tabs, tab, LV_ANIM_NONE);
}

void Display::createScreen(void)
{
    lv_theme_t *th = lv_theme_night_init(40, NULL); //60 For TTYellow
    lv_theme_set_current(th);
    lv_tabview_set_sliding(tabs, false);
    lv_tabview_get_style(tabs, LV_TABVIEW_STYLE_BTN_PR);
    lv_tabview_set_anim_time(tabs, 0);

    createBatteryMeter();
    createAutoSelector();
    createLabels();
    //createTabs();
}
