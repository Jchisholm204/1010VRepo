#include "main.h"
#include "drive.h"
#include "run.h"
#include "display.h"
void autoRun(void){
  /*
The fopen statement here is used to open the autonomous file previously recorded to the SD card.
I typicaly record my files acording to the format "UpRED" for unprotected red, or "pBLUE" for protected blue
In PROS, files are accessed through /usd/filename.txt
EX:
mvfile = fopen("/usd/UpBLUE.txt", "r");
Would run the unprotected blue recording
  */


//  FILE* fp =fopen("/usd/red.txt", "r");
  FILE*fp;
  switch (SelectedAuto) { //get the auto selected on the display and open the corisponding file
    case 0:
      fp = fopen("/usd/red.txt", "r");
      break;
    case 1:
      fp = fopen("/usd/blue.txt", "r");
      break;
    case 2:
      fp = fopen("/usd/skills.txt", "r");
      break;
    default: //if there is not auto selected, open up a blank text file and do nothing
      fp = fopen("/usd/noauto.txt", "r");
      break;
  }
  //FILE* fp = fopen("/usd/record.txt", "r"); //opens the file with the auton in it

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
        //intakes
        intakeL.move(0);
        intakeR.move(0);
        //other
        flyWheel.move(0);
        roller.move(0);
    ///////close the file
        fclose(fp);
        delay(100);
    }
//reading from the array
    fscanf(fp, "%f %f %f %f %f %f %f %f", &m1, &m2, &m3, &m4, &m5, &m6, &m7, &m8);
  //printf("%f %f %f %f %f %f %f %f\n", &m1, &m2, &m3, &m4, &m5, &m6, &m7, &m8);  //debug to serial terminal
//moving motors using array values
//drive motors
  driveRB.move_velocity(m1);
  driveRF.move_velocity(m2);
  driveLB.move_velocity(m3);
  driveLF.move_velocity(m4);
  //inner roller
  roller.move_velocity(m5);
  //intakes
  intakeR.move_velocity(m6);
  intakeL.move_velocity(m7);
  //flyWheel vel target
  flyWheel.move_velocity(m8);
  delay(15);
}
}
