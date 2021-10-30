/*
Thanks to Caden H. and 1010A for this display code.
All of the code here is baised off of his and much of what is here would not be possible without him.
Please see:
https://github.com/cadenhewlett/CHPersonal/tree/master/ScreenStuff
*/


#include "main.h"
#include "display.h"
#include <string.h>
#include "display/lvgl.h"
#include "setup.h"
int SelectedAuto;

lv_obj_t * tabs = lv_tabview_create(lv_scr_act(), NULL);
lv_obj_t * disabled_tab = lv_tabview_add_tab(tabs, "Disabled");
lv_obj_t * op_tab = lv_tabview_add_tab(tabs, "OperatorTab");
lv_obj_t * sys_battery_meter;
lv_obj_t * bat_meter_label;

//LV_IMG_DECLARE(dispimg);
//lv_img_set_src(dispimg, "/usd/dispimg.bin");

lv_res_t autoSelect_action(lv_obj_t * selector){
  SelectedAuto = lv_roller_get_selected(selector);

  return LV_RES_OK;
}
/*
void Display::createImg(void){
  lv_obj_t * oogway = lv_img_create(op_tab, NULL);
  lv_img_set_src(oogway, &dispimg);
  lv_obj_align(oogway, NULL, LV_ALIGN_CENTER, 100, 0);
  lv_img_set_auto_size(oogway, true);
}*/
void Display::createTitle(void)
{
  lv_obj_t * teamOrg = lv_label_create(op_tab, NULL);
  lv_obj_t * teamName =  lv_label_create(op_tab, NULL);
  lv_obj_t * creator = lv_label_create(op_tab, NULL);
  lv_label_set_text(teamOrg, TEAM_ORG);
  lv_label_set_text(teamName, TEAM_NAME);
  lv_label_set_text(creator, "Property of 1010V"); //DO NOT CHANGE
  //You are welcome to use this code, but people must know who it belongs to
  lv_obj_align(teamOrg, NULL, LV_ALIGN_CENTER, 100, -20);
  lv_obj_align(teamName, teamOrg, LV_ALIGN_CENTER, 0, 20);
  lv_obj_align(creator, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, -80);
}

void Display::createBatteryMeter(void){
  sys_battery_meter = lv_lmeter_create(lv_scr_act(), NULL);
  bat_meter_label = lv_label_create(sys_battery_meter, NULL);
  lv_obj_t * symbol_label =  lv_label_create(sys_battery_meter, NULL);
  lv_lmeter_set_range(sys_battery_meter, 0, 100);
//  lv_obj_set_size(sys_battery_meter, 80, 80);
  lv_obj_align(sys_battery_meter, NULL, LV_ALIGN_CENTER, -130, 30);
  lv_obj_align(bat_meter_label, sys_battery_meter, LV_ALIGN_CENTER, 0, -10);
  lv_obj_align(symbol_label, bat_meter_label, LV_ALIGN_CENTER, -10, 20);
  lv_lmeter_set_value(sys_battery_meter, 75);
  //lv_label_set_text(bat_meter_label, SYMBOL_BATTERY_2);
  lv_label_set_text(symbol_label, "Battery");
//lv_obj_align(bat_meter_label, sys_battery_meter, LV
}

void Display::createAutoSelector(void){
  lv_obj_t * autoSelector = lv_roller_create(disabled_tab, NULL); //create auto selector
  lv_roller_set_options(autoSelector, autoOptions); //set options for the array
  lv_obj_set_width(autoSelector, 80);
  lv_roller_set_visible_row_count(autoSelector, 4);
  lv_roller_set_action(autoSelector, autoSelect_action);
  lv_obj_align(autoSelector, NULL , LV_ALIGN_CENTER, 100, 0);
}

void Display::refresh(void)
{
  int level = pros::battery::get_capacity();
  lv_lmeter_set_value(sys_battery_meter, level);

  lv_label_set_text(bat_meter_label, (std::to_string(level)+"%").c_str()); //Thanks to Caden H for coming up with this fix
//lv_lmeter_set_value(bat_meter_label, level);
}

void Display::createScreen(void){
  createTitle();
  createAutoSelector();
  createBatteryMeter();
}

void Display_Task_fn(void*param){/*
  display.createScreen();
  while(true){
    display.refresh();
    pros::delay(DISPLAY_REFRESH_RATE);
  }*/
}