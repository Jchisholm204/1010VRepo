#include "main.h"
#include "drive.h"

int exponential(int joystickVal, float driveExp, int joydead, int motorMin){
  int joySign;
  int joyMax = 128 - joydead;
  int joyLive = abs(joystickVal) - joydead;
  if(joystickVal > 0){joySign = 1;}
  else if(joystickVal < 0){joySign = -1;}
  else{joySign = 0;}
  int power = joySign * (motorMin + ((127 - motorMin) * (pow(joyLive, driveExp) / pow(joyMax, driveExp))));
  return power;
}

void Chassis::operator_Chassis(void){
  int Yval = exponential(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), 1.5 /*DriveExp*/, 8 /*JoyDead*/, 15 /*MotorMin*/);
  int Xval = exponential(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X), 1.5, 8, 15);

  driveLB.move(Yval + Xval);
  driveLF.move(Yval + Xval);
  driveRB.move(Yval - Xval);
  driveRF.move(Yval - Xval);
}


void Chassis::timeDrive(int time, int leftPow, int righPow){

}

void Chassis::drive(int targetValue, int timeout){
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

	int dPowR;
	int dPowL;



    while((pros::millis()-startMillis) < timeout){

		errL = targetValue - lbLDR.get();
		err_lastL = errL; 
		derrL = (errL - err_lastL); 
		pL = (KP * errL); 
		err_sumL += errL;
		dL = KD * derrL;

		errR = targetValue - rbLDR.get();
		err_lastR = errR; 
		derrR = (errR - err_lastR); 
		pR = (KP * errR); 
		err_sumL += errR;
		dR = KD * derrR;

		dPowL = (pL+dL);
		dPowR = (pR+dR);

		dPowL = (dPowL > 127 ? 127 : dPowL < -127 ? -127 : dPowL);
		dPowR = (dPowR > 127 ? 127 : dPowR < -127 ? -127 : dPowR);


		driveRF.move(dPowR);
      	driveLB.move(dPowL);
      	driveRB.move(dPowR);
      	driveLF.move(dPowL);
	}
}

void Chassis::turn(int targetValue, int timeout){
	gyro.tare_rotation();
	int startMillis = pros::millis();

    float KP = 0.7;
	float KD = 1.2;
	int err = 0; //error value init
	int derr = 0;//error difference
	int err_last = 0; //last error
	int err_sum = 0; //sum of errors
	float p; //p value normally 0.8
	float d; //d value normally 0.7
	int dPow;

    while((pros::millis()-startMillis) < timeout){

		err = targetValue - gyro.get_rotation();
		err_last = err; 
		derr = (err - err_last); 
		p = (KP * err); 
		err_sum += err;
		d = KD * derr;

		dPow = (p+d);

		dPow = (dPow > 127 ? 127 : dPow < -127 ? -127 : dPow);


		driveRF.move(-dPow);
      	driveLB.move(dPow);
      	driveRB.move(-dPow);
      	driveLF.move(dPow);
	}
}

void Chassis::twrAlign(int timeout, int leftTarg, int rightTarg){
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

	int dPowL, dPowR;

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

		dPowL = (pL+dL);
		dPowR = (pR+dR);

		dPowL = (dPowL > 127 ? 127 : dPowL < -127 ? -127 : dPowL);
		dPowR = (dPowR > 127 ? 127 : dPowR < -127 ? -127 : dPowR);


		driveRF.move(dPowR);
      	driveLB.move(dPowL);
      	driveRB.move(dPowR);
      	driveLF.move(dPowL);

    }
}

void Chassis::fenceAlign(int timeout){
	int startMillis = pros::millis();

    float KP = 0.7;
	float KD = 1.2;
	int err = 0; //error value init
	int derr = 0;//error difference
	int err_last = 0; //last error
	int err_sum = 0; //sum of errors
	float p; //p value normally 0.8
	float d; //d value normally 0.7
	int dPow;

    while((pros::millis()-startMillis) < timeout){

		err = rbLDR.get() - lbLDR.get();
		err_last = err; 
		derr = (err - err_last); 
		p = (KP * err); 
		err_sum += err;
		d = KD * derr;

		dPow = (p+d);

		dPow = (dPow > 127 ? 127 : dPow < -127 ? -127 : dPow);


		driveRF.move(dPow);
      	driveLB.move(-dPow);
      	driveRB.move(dPow);
      	driveLF.move(-dPow);
	}
}

void Chassis::stop(void){
	driveRF.move_velocity(0);
    driveLB.move_velocity(0);
    driveRB.move_velocity(0);
    driveLF.move_velocity(0);
}

void Chassis::time(int time, int velocity){
	driveRF.move_velocity(velocity);
    driveLB.move_velocity(velocity);
    driveRB.move_velocity(velocity);
    driveLF.move_velocity(velocity);
	pros::delay(time);
	driveRF.move(0);
    driveLB.move(0);
    driveRB.move(0);
    driveLF.move(0);
}

void Intakes(int velocity){
	intakeL.move_velocity(velocity);
	intakeR.move_velocity(velocity);
}