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

  FILE* fp = fopen("/usd/NEWrecord.txt", "r"); //opens the file with the auton in it

  static float m1, m2, m3, m4, m5, m6, m7, m8; //these are placeholders for motor volatges
  //Auton while loop
  while (true) {
    if(feof(fp)){  //if end of file reached
    /////////stop all of the motors
      //drive motors
        driveRB.move(0);
        driveRF.move(0);
        driveLB.move(0);
        driveLF.move(0);
        //tray motor
        TrayMotor.move(0);
        //intakes
        LeftIntake.move(0);
        RightIntake.move(0);
      //arm motor
        ArmMotor.move(0);
    ///////close the file
        fclose(fp);
        delay(100);
    }
//reading from the array
    fscanf(fp, "%f %f %f %f %f %f %f %f", &m1, &m2, &m3, &m4, &m5, &m6, &m7, &m8);

//moving motors using array values
//drive motors
  //printf("%f\n", m1);
  driveRB.move_velocity(m1);
  driveRF.move_velocity(m2);
  driveLB.move_velocity(m3);
  driveLF.move_velocity(m4);

  //tray motor
  TrayMotor.move_velocity(m8);
  //intakes
  LeftIntake.move_velocity(m6);
  RightIntake.move_velocity(m7);
//arm motor
  ArmMotor.move_velocity(m5);
  delay(15);
}
}
