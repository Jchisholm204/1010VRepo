#include "main.h"
#include "autons.h"
#include "drive.h"

void intakes(int vel){//hi
	intakeL.move_velocity(-vel);
	intakeR.move_velocity(-vel);
}

void skills(){
	intakes(200);
	pros::delay(500);
	roller.move_velocity(90);
	pros::delay(1000);
	roller.move_velocity(0);
	drivef.drive(700, 2000);
	intakes(-100);
	drivef.turn(155, 2000);
	drivef.time(800, 150);
	flyWheel.move_velocity(550);
	drivef.twrAlign(2000, 450, 250);
	roller.move_velocity(200);
	pros::delay(450);
	roller.move_velocity(0);
	pros::delay(1000);
	drivef.turn(-18, 800);
	drivef.move(-2850, 5000);
	intakes(200);
	drivef.turn(-65, 1500); //46
	drivef.heading(110, 0, 1500);
	drivef.time(1000, 100);
	drivef.heading(100, 0, 1000);
	drivef.time(800, -100);
	drivef.heading(105, 0, 1500);
	intakes(-180);
	pros::delay(800);
	intakes(0);
	drivef.timeDrive(1500, 70, 75);
	flyWheel.move_velocity(460);
	//drivef.turn(10, 800);
	roller.move_velocity(200);
	pros::delay(1000);
	roller.move_velocity(0);
	drivef.move(-500, 1000);
	drivef.heading(0, 0, 2000);
	drivef.turn(-55, 1000);
	intakes(200);
	drivef.stop();
	pros::delay(500);
	drivef.move(1400, 3000);
	drivef.timeDrive(1000, 20, 80);
	drivef.timeDrive(800, 100, 80);
	drivef.twrAlign(2000, 350, 350);
	roller.move_velocity(200);
}
void sadAuto(){
	flyWheel.move_velocity(600);
	pros::delay(500);
	roller.move_velocity(200);	
}
void leftAuto(){
	flyWheel.move_velocity(470);
	pros::delay(200);
	roller.move_velocity(200);
	pros::delay(1300);
	roller.move_velocity(0);
	drivef.move(-800, 1500);
	drivef.turn(125, 1000);
	pros::delay(150);
	drivef.move(600, 1500);
	intakes(200);
	roller.move_velocity(100);
	pros::delay(1800);
	intakes(-200);
	roller.move_velocity(0);
	pros::delay(1100);
	intakes(0);
	//drivef.time(800, 50);
	drivef.twrAlign(2000, 300, 370);
	intakes(0);
	roller.move_velocity(200);
}
void rightAuto(){
	flyWheel.move_velocity(470);
	pros::delay(200);
	roller.move_velocity(200);
	pros::delay(1300);
	roller.move_velocity(0);
	drivef.move(-800, 1500);
	drivef.turn(-125, 1000);
	pros::delay(150);
	drivef.move(600, 1500);
	intakes(200);
	roller.move_velocity(100);
	pros::delay(1800);
	intakes(-200);
	roller.move_velocity(0);
	pros::delay(1100);
	intakes(0);
	//drivef.time(800, 50);
	drivef.twrAlign(2000, 370, 300);
	//intakes(0);
	roller.move_velocity(200);
}
void testAuto(){
	int leftTarg = 400;
	int rightTarg = 400;
	int startMillis = pros::millis();

    float KP = 0.4;
	float KD = 1.6;

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

	int dPowL, dPowR;

    while(true){
		printf("Left: %d Right: %d PowR: %d PowL: %d\n",lLDR.get(), rLDR.get(), dPowR, dPowL);
		//printf("D: %f P: %d\n", dR, pR);
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

		dPowL = (pL+dL);
		dPowR = (pR+dR);

		//dPowL = (dPowL > 90 ? 90 : dPowL < -90 ? -90 : dPowL);
		//dPowR = (dPowR > 90 ? 90 : dPowR < -90 ? -90 : dPowR);
		if(dPowL > 80){dPowL=80;};
		if(dPowL < -80){dPowL=-80;};
		if(dPowR > 80){dPowR=80;};
		if(dPowR < -80){dPowR=-80;};


		driveRF.move(dPowR);
      	driveLB.move(dPowL);
      	driveRB.move(dPowR);
      	driveLF.move(dPowL);

    }
}
void crap(){
	int leftTarg = 400;
	int rightTarg = 400;
	int startMillis = pros::millis();

    float KP = 0.8;
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

	int dPowL, dPowR;

    while(true){
		//printf("L: %d R: %d OR: %d OL: %d\n",lLDR.get()/10, rLDR.get()/10, dPowR, dPowL);
		printf("D: %f P: %d", dR, pR);

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

		dPowL = (pL+dL);
		dPowR = (pR+dR);

		//dPowL = (dPowL > 90 ? 90 : dPowL < -90 ? -90 : dPowL);
		//dPowR = (dPowR > 90 ? 90 : dPowR < -90 ? -90 : dPowR);
		if(dPowL > 80){dPowL=80;};
		if(dPowL < -80){dPowL=-80;};
		if(dPowR > 80){dPowR=80;};
		if(dPowR < -80){dPowR=-80;};


		driveRF.move(dPowR);
      	driveLB.move(dPowL);
      	driveRB.move(dPowR);
      	driveLF.move(dPowL);

    }
}