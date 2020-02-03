#include "main.h"
#include "chassis.h"
#include "Intakes.h"
#include "tray.h"
#include "lift.h"
#include "run.h"

void autoRun(void){

  FILE* mvfile = fopen("/usd/mvstorage.txt", "w");
  FILE* armf = fopen("/usd/armfile.txt", "w");
  FILE* intakef = fopen("/usd/intake.txt", "w");
  FILE* typefile = fopen("/usd/namefile.txt", "w");
  /*
The fopen statement here is used to open the autonomous file previously recorded to the SD card.
I typicaly record my files acording to the format "UpRED" for unprotected red, or "pBLUE" for protected blue
In PROS, files are accessed through /usd/filename.txt
EX:
mvfile = fopen("/usd/UpBLUE.txt", "r");
Would run the unprotected blue recording
  */
  static float m1, m2, m3, m4, m5, m6, m7, m8; //these are placeholders for motor volatges
  static float pres;
  static float nameboi;

  fscanf(typefile, "%f", &nameboi);
  master.print(0, 0, "%f", nameboi);

  //Auton while loop
  while (true) {
    if(feof(mvfile)){  //if end of file reached
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
        fclose(mvfile);
        fclose(armf);
        fclose(intakef);
        fclose(typefile);
        delay(100);
    }
//reading from the array
    fscanf(mvfile, "%f %f %f %f %f %f %f", &m1, &m2, &m3, &m4, &m5, &m6, &m7);
    fscanf(armf, "%f", &pres);

    liftState = pres;

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
  //ArmMotor.move_voltage(m8);
  delay(15);
}
}
