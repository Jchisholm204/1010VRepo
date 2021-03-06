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
int SelectedAuto;

lv_obj_t * tabs = lv_tabview_create(lv_scr_act(), NULL);
lv_obj_t * disabled_tab = lv_tabview_add_tab(tabs, "Disabled");
lv_obj_t * op_tab = lv_tabview_add_tab(tabs, "OperatorTab");
lv_obj_t * diagnostics_tab = lv_tabview_add_tab(tabs, "Diagnostics");
lv_obj_t * sys_battery_meter;
lv_obj_t * bat_meter_label;
lv_obj_t * lLED;
lv_obj_t * rLED;
lv_obj_t * bULTsts;
lv_obj_t * lULTsts;
lv_obj_t * rULTsts;

LV_IMG_DECLARE(dispimg);

lv_res_t autoSelect_action(lv_obj_t * selector){
  SelectedAuto = lv_roller_get_selected(selector);

  return LV_RES_OK;
}

void Display::createImg(void){
  lv_obj_t * oogway = lv_img_create(op_tab, NULL);
  lv_img_set_src(oogway, &dispimg);
  lv_obj_align(oogway, NULL, LV_ALIGN_CENTER, 100, 0);
  lv_img_set_auto_size(oogway, true);
}
void Display::createTitle(void)
{
  lv_obj_t * title =  lv_label_create(op_tab, NULL);
  lv_label_set_text(title, "Ten Ton - 1010V" );
  lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_MID, 100, 0);
}

void Display::createOpLEDs(void){
  lLED = lv_led_create(diagnostics_tab, NULL);
  lv_obj_t * intakeLLabel = lv_label_create(diagnostics_tab, NULL);
  lv_label_set_text(intakeLLabel, "L lmt");
  lv_obj_align(lLED, NULL, LV_ALIGN_IN_TOP_RIGHT, -60, 0);
  lv_obj_set_size(lLED, 80, 40);
  //lv_obj_align(lv_obj_t *obj, const lv_obj_t *base, lv_align_t align, lv_coord_t x_mod, lv_coord_t y_mod)
  lv_obj_align(intakeLLabel, lLED, LV_ALIGN_CENTER, 0, 0);

  rLED = lv_led_create(diagnostics_tab, NULL);
  lv_obj_t * intakeRLabel = lv_label_create(diagnostics_tab, NULL);
  lv_label_set_text(intakeRLabel, "R lmt");
  lv_obj_align(rLED, NULL, LV_ALIGN_IN_TOP_RIGHT, -60, 100);
  lv_obj_set_size(rLED, 80, 40);
  //lv_obj_align(lv_obj_t *obj, const lv_obj_t *base, lv_align_t align, lv_coord_t x_mod, lv_coord_t y_mod)
  lv_obj_align(intakeRLabel, rLED, LV_ALIGN_CENTER, 0, 0);
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

void Display::DistanceReadout(void){
    bULTsts = lv_label_create(diagnostics_tab, NULL);
    lULTsts = lv_label_create(diagnostics_tab, NULL);
    rULTsts = lv_label_create(diagnostics_tab, NULL);

    lv_obj_align(bULTsts, lLED, LV_ALIGN_CENTER, -210, -20);
    lv_obj_align(lULTsts, bULTsts, LV_ALIGN_CENTER, 0, 20);
    lv_obj_align(rULTsts, lULTsts, LV_ALIGN_CENTER, 0, 20);

    lv_label_set_text(bULTsts, "ULTRASONIC B: --");
    lv_label_set_text(lULTsts, "ULTRASONIC L: --");
    lv_label_set_text(rULTsts, "ULTRASONIC R: --");

}

void Display::createAutoSelector(void){
  lv_obj_t * autoSelector = lv_roller_create(disabled_tab, NULL); //create auto selector
  lv_roller_set_options(autoSelector, "Red\nBlue\nSkills\nNoAuto"); //set options for the array
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
  lv_obj_align(autoSelector, NULL , LV_ALIGN_CENTER, 100, 0);
}

void Display::refresh(void)
{
  int level = pros::battery::get_capacity();
  lv_lmeter_set_value(sys_battery_meter, level);

  lv_label_set_text(bat_meter_label, (std::to_string(level)+"%").c_str()); //Thanks to Caden H for coming up with this fix
//lv_lmeter_set_value(bat_meter_label, level);
  if(LiL.get_value() == 1){
    lv_led_on(lLED);
  }
  else{
    lv_led_off(lLED);
  };
  if(LiR.get_value() == 1){
    lv_led_on(rLED);
  }
  else{
    lv_led_off(rLED);
  };

  int bULTtempdat = bULT.get_value();
  int lULTtempdat = lULT.get_value();
  int rULTtempdat = rULT.get_value();

  lv_label_set_text(bULTsts, ("ULTRASONIC B: " + std::to_string(bULTtempdat)).c_str());
  lv_label_set_text(lULTsts, ("ULTRASONIC L: " + std::to_string(lULTtempdat)).c_str());
  lv_label_set_text(rULTsts, ("ULTRASONIC R: " + std::to_string(rULTtempdat)).c_str());

}
void Display::setActiveTab(int tab){
  lv_tabview_set_tab_act(tabs, tab, LV_ANIM_NONE);
}

void Display::createScreen(void)
{
    lv_theme_t *th = lv_theme_night_init(0, NULL); //60 For TTYellow
    lv_theme_set_current(th);
    lv_tabview_set_sliding(tabs, false);
    lv_tabview_get_style(tabs, LV_TABVIEW_STYLE_INDIC);
    lv_tabview_set_anim_time(tabs, 0);

    createImg();
    createBatteryMeter();
    createOpLEDs();
    createAutoSelector();
    createTitle();
    DistanceReadout();
    //createTabs();
}
