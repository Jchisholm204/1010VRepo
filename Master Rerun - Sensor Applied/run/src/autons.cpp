#include "main.h"
#include "autons.h"
#include "drive.h"
void autoRun(void){

    FILE * runFile = fopen("/usd/NEWrecord.txt", "r");

    static float m1, m2, m3, m4, m5, m6, m7, m8, u10, u11;
    static bool b9;

    while (true){
        if(feof(runFile)){
            driveRB.move(0);
            driveRF.move(0);
            driveLB.move(0);
            driveLF.move(0);    
            flyWheel.move(0);
            roller.move(0);
            intakeL.move(0);
            intakeR.move(0);   

            fclose(runFile);
            pros::delay(100);    
        }

        fscanf(runFile, "%f %f %f %f %f %f %f %f %f %f %f", &m1, &m2, &m3, &m4, &m5, &m6, &m7, &m8, &b9, &u10, &u11);
        driveRB.move_velocity(m1);
        driveRF.move_velocity(m2);
        driveLB.move_velocity(m3);
        driveLF.move_velocity(m4);

        flyWheel.move_velocity(m5);
        roller.move_velocity(m6);

        if(m7 > 0){
            intakeL.move_velocity(m7 * (1 - LiL.get_value()));
        }
        else{
            intakeL.move_velocity(m7);
        }
        if(m8 > 0){
            intakeR.move_velocity(m8 * (1 - LiR.get_value()));
        }
        else{
            intakeR.move_velocity(m8);
        }

        if(b9 = true){
            ultraCheck(u11, u10, 1500);
        }        

        pros::delay(15);
    }
}

void ultraCheck(int leftTarg, int rightTarg, int timeout){
    int startMillis = pros::millis();
    int leftDif;
    int rightDif;

    leftDif = lULT.get_value() - leftTarg;
    rightDif = rULT.get_value() - rightTarg;

    while((pros::millis()-startMillis) < timeout){
		driveRF.move_velocity(rightDif * 10);
      	driveLB.move_velocity(leftDif * 10);
      	driveRB.move_velocity(rightDif * 10);
      	driveLF.move_velocity(leftDif * 10);        
    }

    
}