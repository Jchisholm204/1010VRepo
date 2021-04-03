#include "main.h"
#include "autons.h"
#include "drive.h"

void ultraCheck(int leftTarg, int rightTarg, int timeout){
    int startMillis = pros::millis();

    float KP = 0.7;
	float KD = 1.2;
	int errL = 0; //error value init
	int derrL = 0;//error difference
	int err_lastL = 0; //last error
	int err_sumL = 0; //sum of errors
	float pL; //p value normally 0.8
	float dL; //d value normally 0.7

	int errR = 0; //error value init
	int derrR = 0;//error difference
	int err_lastR = 0; //last error
	int err_sumR = 0; //sum of errors
	float pR; //p value normally 0.8
	float dR; //d value normally 0.7

    while((pros::millis()-startMillis) < timeout){

		errL = lLDR.get() - leftTarg;
		err_lastL = errL; 
		derrL = (errL - err_lastL); 
		pL = (KP * errL); 
		err_sumL += errL;
		dL = KD * derrL;

		errR = rLDR.get() - rightTarg;
		err_lastR = errR; 
		derrR = (errR - err_lastR); 
		pR = (KP * errR); 
		err_sumL += errR;
		dR = KD * derrR;

		driveRF.move(pR+dR);
      	driveLB.move(pL+dL);
      	driveRB.move(pR+dR);
      	driveLF.move(pL+dR);

    }    
}


void autoRun(void){

    FILE * runFile = fopen("/usd/TestSensors.txt", "r");

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

        fscanf(runFile, "%f %f %f %f %f %f %f %f %d %f %f", &m1, &m2, &m3, &m4, &m5, &m6, &m7, &m8, &b9, &u10, &u11);
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

        if(b9 == 1){
            
           ultraCheck(u11, u10, 2500);
        }
        else{
            
        };

        pros::delay(15);
    }
}
