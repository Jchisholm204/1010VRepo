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
void skills(){
    Intakes(200);
	roller.move_velocity(90);
	pros::delay(750);
	roller.move_velocity(0);
	drivef.drive(800, 4000);
	Intakes(-100);
	drivef.turn(100, 2000);
	Intakes(0);
	drivef.time(1000, 100);
	roller.move_velocity(80);
	pros::delay(500);
	roller.move_velocity(0);
	drivef.time(1000, -100);
	drivef.turn(30, 1000);
	drivef.time(800, 100);
	Intakes(200);
	drivef.twrAlign(2000, 350, 350);
	flyWheel.move_velocity(500);
	pros::delay(500);
	roller.move_velocity(200);
	pros::delay(1500);
	drivef.time(1000, -100);

}