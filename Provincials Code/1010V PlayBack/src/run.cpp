#include "main.h"
#include "chassis.h"
#include "Intakes.h"
#include "tray.h"
#include "lift.h"
#include "run.h"

void autoRun(void){
  /*
The fopen statement here is used to open the autonomous file previously recorded to the SD card.
I typicaly record my files acording to the format "UpRED" for unprotected red, or "pBLUE" for protected blue
In PROS, files are accessed through /usd/filename.txt
EX:
mvfile = fopen("/usd/UpBLUE.txt", "r");
Would run the unprotected blue recording
  */

  FILE* fp = fopen("/usd/record.txt", "r"); //opens the file with the auton in it

  static float m1, m2, m3, m4, m5, m6, m7, m8; //these are placeholders for motor volatges
  //Auton while loop
  while (true) {
    if(feof(fp)){  //if end of file reached
    /////////stop all of the motors
      //drive motors
        driveRB.move_voltage(0);
        driveRF.move_voltage(0);
        driveLB.move_voltage(0);
        driveLF.move_voltage(0);
        //tray motor
        TrayMotor.move_voltage(0);
        //intakes
        LeftIntake.move_voltage(0);
        RightIntake.move_voltage(0);
      //arm motor
        ArmMotor.move_voltage(0);
    ///////close the file
        fclose(fp);
        delay(100);
    }
//reading from the array
    fscanf(fp, "%f %f %f %f %f %f %f %f", &m1, &m2, &m3, &m4, &m5, &m6, &m7, &m8);

//moving motors using array values
//drive motors
  //printf("%f\n", m1);
  driveRB.move_voltage(m1);
  driveRF.move_voltage(m2);
  driveLB.move_voltage(m3);
  driveLF.move_voltage(m4);
  //tray motor
  TrayMotor.move_voltage(m5);
  //intakes
  LeftIntake.move_voltage(m6);
  RightIntake.move_voltage(m7);
//arm motor
  ArmMotor.move_voltage(m8);
  delay(15);
}
}
