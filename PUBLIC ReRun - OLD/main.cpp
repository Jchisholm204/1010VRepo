#include "main.h"
#include "run.h"
#include "record.h"
#include <math.h>
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */




 Controller master(E_CONTROLLER_MASTER);

 Motor testMotor(20, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
 Motor testMotor2(19, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
void initialize() {
	testMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);  //Record();

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
 int counter = 0;
void autonomous() {
  Run();
}



void opcontrol() {
  FILE* file = fopen("/usd/example.txt", "w");

	while (counter < 15000/*stop collecting data when over 15000 milliseconds*/) {
//write motor voltage to the file
    fprintf(file, "%d\n", testMotor.get_voltage());
    fprintf(file, "%d\n", testMotor2.get_voltage());

    printf("%d\n", testMotor.get_voltage());
    printf("%d\n", testMotor2.get_voltage());

    if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){
      testMotor.move(40);
    }
    else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){
      testMotor.move(-40);
    }
    else{
      testMotor.move(0);
    }
    if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){
      testMotor2.move(127);
    }
    else if(master.get_digital(E_CONTROLLER_DIGITAL_L2)){
      testMotor2.move(-127);
    }
    else{
      testMotor2.move(0);
    }
//increase counter by incriments of 10 every 10 milliseconds
    counter +=10;
		pros::delay(10);
	}
  fclose(file);
}
