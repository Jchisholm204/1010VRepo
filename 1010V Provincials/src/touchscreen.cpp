#include "main.h"
#include "touchscreen.h"
#include <string.h>
extern lv_obj_t*tabs;
extern lv_obj_t*working_tab;
extern lv_obj_t*disabled_tab;
lv_obj_t * tabs = lv_tabview_create(lv_scr_act(), NULL); //Declare tabview on default tab
lv_obj_t * working_tab = lv_tabview_add_tab(tabs, "Enabled"); //Declare a tab
lv_obj_t * disabled_tab = lv_tabview_add_tab(tabs, "Info"); //Declare a tab

lv_obj_t*battery_meter;
lv_obj_t*battery_meter_label;
lv_obj_t * autoSelector;
lv_obj_t*tryLmtLED;
lv_obj_t*tryDwnLED;
lv_obj_t*tryUpLED;
lv_obj_t * symbol_label;


/*** CREATE FUNCTIONS FOR OUR OBJECTS ***/
lv_res_t autoSelect_action(lv_obj_t * selector){
  autoCase = lv_roller_get_selected(selector); /*Changes the current auto to be the list option index*/

  return LV_RES_OK; //return OK for complete execution
}

void Screen::createOpLEDs(void){
  //declare leds
  tryLmtLED = lv_led_create(working_tab, NULL);
  tryDwnLED = lv_led_create(working_tab, NULL);
  tryUpLED = lv_led_create(working_tab, NULL);
  //set lv object positions
  lv_obj_align(tryLmtLED, NULL, LV_ALIGN_IN_TOP_RIGHT, -20, 40);
  lv_obj_align(tryUpLED, tryLmtLED, LV_ALIGN_CENTER, 0, 45);
  lv_obj_align(tryLmtLED, tryLmtLED, LV_ALIGN_CENTER, 0, 90);
  //set object lv size
  lv_obj_set_size(tryLmtLED, 50, 35);
  lv_obj_set_size(tryDwnLED, 50, 35);
  lv_obj_set_size(tryUpLED, 50, 35);

  //set lv object labels
  lv_obj_t * tryLmtLabel = lv_label_create(working_tab, NULL);
  lv_obj_t * tryDWNLabel = lv_label_create(working_tab, NULL);
  lv_obj_t * tryUpLabel = lv_label_create(working_tab, NULL);
  //set label positions
  lv_obj_align(tryLmtLabel, tryLmtLED, LV_ALIGN_CENTER, 0, 0);
  lv_obj_align(tryDWNLabel, tryDwnLED, LV_ALIGN_CENTER, 0, 0);
  lv_obj_align(tryUpLabel, tryUpLED, LV_ALIGN_CENTER, 0, 0);
  //make label text
  lv_label_set_text(tryLmtLabel, "TryLmt");
  lv_label_set_text(tryDWNLabel, "Lower");
  lv_label_set_text(tryUpLabel, "Upper");
}

void Screen::createTitle(void){
  lv_obj_t * Title = lv_label_create(working_tab, NULL);
  lv_obj_set_size(Title, 100, 70);
  lv_label_set_text(Title, "1010V");
  lv_obj_align(Title, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
}

void Screen::createAutoSelector(void){
  autoSelector = lv_roller_create(working_tab, NULL); //create auto selector
  lv_roller_set_options(autoSelector, "None\nUPBlue\nUPRed\nSkills\nOther\nMore"); //sets options to our character array
  lv_obj_set_width(autoSelector, 80); //sets the widtho of our list
  lv_roller_set_visible_row_count(autoSelector, 4);
  lv_roller_set_action(autoSelector, autoSelect_action); //Sets the action to our previously defined function
  lv_obj_align(autoSelector, battery_meter, LV_ALIGN_CENTER, 150, -5); //Align object

}
void Screen::createBatteryMeter(void){
  battery_meter = lv_lmeter_create(working_tab, NULL);
  battery_meter_label = lv_label_create(battery_meter, NULL);
  symbol_label =  lv_label_create(battery_meter, NULL);
  lv_lmeter_set_range(battery_meter, 0, 100);
//  lv_obj_set_size(sys_battery_meter, 80, 80);
  lv_obj_align(battery_meter, NULL, LV_ALIGN_CENTER, 45, 10);
  lv_obj_align(battery_meter_label, battery_meter, LV_ALIGN_CENTER, 8, -10);
  lv_obj_align(symbol_label, battery_meter_label, LV_ALIGN_CENTER, -10, 20);
  lv_lmeter_set_value(battery_meter, 75);
  //lv_label_set_text(bat_meter_label, SYMBOL_BATTERY_2);
  lv_label_set_text(symbol_label, "Battery");
//lv_obj_align(bat_meter_label, sys_battery_meter, LV
}
void Screen::refresh(void) //refreshes values sent to the screen
{

    if(TrayDownLimit.get_value() == HIGH){lv_led_on(tryLmtLED);} //If the front light sensor reading is less than 2700, turn on the LED
    else{lv_led_off(tryLmtLED);} //Otherwise it is off

    if(top.get_value() > 2000){lv_led_on(tryUpLED);}
    else{lv_led_off(tryUpLED);}

    if(top.get_value() < 2000){lv_led_on(tryDwnLED);} //If the back light sensor reading is less than 2700, turn on the LED
    else{lv_led_off(tryDwnLED);} //Otherwise it is off

    int level = pros::battery::get_capacity();
    lv_lmeter_set_value(battery_meter, level);
    lv_label_set_text(battery_meter_label, (std::to_string(level)+"%").c_str()); //convert level(int) to string to a const char

//  delay(20);
}
void Screen::setActiveTab(int tab){
  lv_tabview_set_tab_act(tabs, tab, LV_ANIM_NONE); //changes active tab
}

void Screen::createScreen(void)
{

    lv_theme_t *th = lv_theme_alien_init(60, NULL); //Sets the theme, 60 For TTYellow
    lv_tabview_set_sliding(tabs, false); //do not slide the tabs to save brain powah
    lv_tabview_set_anim_time(tabs, 0); //Disable animations to save the brain

    //Call our functions
    createTitle();
    createBatteryMeter();
    createOpLEDs();
    createAutoSelector();
  //  createBackground();

}
