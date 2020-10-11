#include "main.h"
#include "display.h"
#include <string.h>
int SelectedAuto;
extern lv_obj_t*tabs;
extern lv_obj_t*disabled_tab;
extern lv_obj_t*op_tab;
extern lv_obj_t*intakeLED;
//extern lv_obj_t*

lv_obj_t * tabs = lv_tabview_create(lv_scr_act(), NULL);
lv_obj_t * disabled_tab = lv_tabview_add_tab(tabs, "Disabled");
lv_obj_t * op_tab = lv_tabview_add_tab(tabs, "OperatorTab");
lv_obj_t * sys_battery_meter;
lv_obj_t * bat_meter_label;
lv_obj_t * intakeLED;

lv_res_t autoSelect_action(lv_obj_t * selector){
  SelectedAuto = lv_roller_get_selected(selector);

  return LV_RES_OK;
}


void Display::createTitle(void)
{
  lv_obj_t * title =  lv_label_create(op_tab, NULL);
  lv_label_set_text(title, "Ten Ton - 1010V"  );
  lv_obj_align(title, NULL, LV_ALIGN_CENTER, 0, 0);
}

void Display::createOpLEDs(void){
  intakeLED = lv_led_create(op_tab, NULL);
  lv_obj_t * intakeLabel = lv_label_create(op_tab, NULL);
  lv_obj_align(intakeLED, NULL, LV_ALIGN_CENTER, 0, 60);
  lv_obj_align(intakeLabel, intakeLED, LV_ALIGN_CENTER, 0, 0);
}

void Display::createBatteryMeter(void){
  sys_battery_meter = lv_lmeter_create(disabled_tab, NULL);
  bat_meter_label = lv_label_create(sys_battery_meter, NULL);
  lv_obj_t * symbol_label =  lv_label_create(sys_battery_meter, NULL);
  lv_lmeter_set_range(sys_battery_meter, 0, 100);
//  lv_obj_set_size(sys_battery_meter, 80, 80);
  lv_obj_align(sys_battery_meter, NULL, LV_ALIGN_CENTER, 25, -15);
  lv_obj_align(bat_meter_label, sys_battery_meter, LV_ALIGN_CENTER, 8, -10);
  lv_obj_align(symbol_label, bat_meter_label, LV_ALIGN_CENTER, -10, 20);
  lv_lmeter_set_value(sys_battery_meter, 75);
  //lv_label_set_text(bat_meter_label, SYMBOL_BATTERY_2);
  lv_label_set_text(symbol_label, "Battery");
//lv_obj_align(bat_meter_label, sys_battery_meter, LV
}
void Display::createAutoSelector(void){
  lv_obj_t * autoSelector = lv_roller_create(disabled_tab, NULL); //create auto selector
  lv_roller_set_options(autoSelector, "Red\nBlue\nRed Front\nSkills"); //sets options to our character array
  lv_obj_set_width(autoSelector, 80); //sets the widtho of our list
  lv_roller_set_visible_row_count(autoSelector, 4);
  lv_roller_set_action(autoSelector, autoSelect_action); //Sets the action to our previously defined function
  lv_obj_align(autoSelector, sys_battery_meter, LV_ALIGN_CENTER, 0, 0); //Align object
}
void Display::refresh(void)
{
  int level = pros::battery::get_capacity();
  lv_lmeter_set_value(sys_battery_meter, level);

  lv_label_set_text(bat_meter_label, (std::to_string(level)+"%").c_str()); //convert level(int) to string to a const char
//lv_lmeter_set_value(bat_meter_label, level);
  delay(20);
}
void Display::setActiveTab(int tab){
  lv_tabview_set_tab_act(tabs, tab, LV_ANIM_NONE);
}
void Display::createScreen(void)
{
    lv_theme_t *th = lv_theme_material_init(50, NULL); //60 For TTYellow
    lv_tabview_set_sliding(tabs, false);
  //  lv_tabview_get_style(tabs, LV_TABVIEW_STYLE_BTN_PR);
    lv_tabview_set_anim_time(tabs, 0);

    createBatteryMeter();
    createOpLEDs();
    createAutoSelector();
    createTitle();
    //createTabs();
}
