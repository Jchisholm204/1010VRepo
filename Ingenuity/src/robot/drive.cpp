/* Ingenuity - drive.cpp
/* - main.h
/* - robot/drive.hpp
* Drive functions and operator control code for the chassis
*/
#include "main.h"
#include "robot/drive.hpp"

using namespace pros;

int Chassis::exponential(int joystickVal, float driveExp, int joydead, int motorMin){
  int joySign;
  int joyMax = 128 - joydead;
  int joyLive = abs(joystickVal) - joydead;
  if(joystickVal > 0){joySign = 1;}
  else if(joystickVal < 0){joySign = -1;}
  else{joySign = 0;}
  int power = joySign * (motorMin + ((127 - motorMin) * (pow(joyLive, driveExp) / pow(joyMax, driveExp))));
  return power;
}

float toVelocity(int motorPower, int maxVel){
	float output = ((motorPower/127) * maxVel);
	return output;
}

void Chassis::setDrive(double iPowR, double iPowL){
	driveRF.move_velocity(iPowR);
	driveRM.move_velocity(iPowR);
	driveRB.move_velocity(iPowR);

	driveLF.move_velocity(iPowL);
	driveLM.move_velocity(iPowL);
	driveLB.move_velocity(iPowL);

}

void Chassis::setDriveVel(double iVelR, double iVelL){
	driveRF.move_velocity(iVelR);
	driveRM.move_velocity(iVelR);
	driveRB.move_velocity(iVelR);

	driveLF.move_velocity(iVelL);
	driveLM.move_velocity(iVelL);
	driveLB.move_velocity(iVelL);

}

void Chassis::operator_Chassis(int maxVel){
	int Yval = exponential(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), 1.5 /*DriveExp*/, 4 /*JoyDead*/, 25 /*MotorMin*/);
	int Xval = exponential(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X), 1.3, 4, 20);

	Xval = (Xval*maxVel/127)*0.75;  //was0.85
	Yval = Yval*maxVel/127;

	driveLB.move_velocity(Yval + Xval);
	driveLM.move_velocity(Yval + Xval);
	driveLF.move_velocity(Yval + Xval);

	driveRB.move_velocity(Yval - Xval);
	driveRM.move_velocity(Yval - Xval);
	driveRF.move_velocity(Yval - Xval);
}


void Chassis::time(int time, int leftPow, int rightPow){
	setDriveVel(rightPow, leftPow);
	pros::delay(time);
	stop();
}

void Chassis::time(int time, int velocity){
	setDriveVel(velocity, velocity);
	pros::delay(time);
	stop();
}


void Chassis::driveTurn(int leftTarget, int maxLeft, int rightTarget, int maxRight, int timeout){
	driveLF.tare_position();
	driveRF.tare_position();
	int startMillis = pros::millis();

    float KP = 1.2;
	float KD = 1.4;
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
		//Left PID
		errL = leftTarget - driveLF.get_position();
		derrL = (errL - err_lastL); 
		err_lastL = errL; 
		pL = (KP * errL); 
		err_sumL += errL;
		dL = KD * derrL;

		//Right PID
		errR = rightTarget - driveRF.get_position();
		derrR = (errR - err_lastR); 
		err_lastR = errR; 
		pR = (KP * errR); 
		err_sumL += errR;
		dR = KD * derrR;

		dPowL = (pL+dL);
		dPowR = (pR+dR);			


		if(dPowL > maxLeft){dPowL=maxLeft;};
		if(dPowL < -maxLeft){dPowL=-maxLeft;};
		if(dPowR > maxRight){dPowR=maxRight;};
		if(dPowR < -maxRight){dPowR=-maxRight;};

		setDrive(dPowR, dPowL);
	}
}

void Chassis::turn(int targetValue, int timeout){
	//gyro.tare_rotation(); //returns (+) or (-) rotation values in deg
	posGyro.reset();
	int startMillis = pros::millis();

    float KP = 2.1;
	float KD = 1.1;
	int err = 0; //error value init
	int derr = 0;//error difference
	int err_last = 0; //last error
	int err_sum = 0; //sum of errors
	float p; //p value normally 0.8
	float d; //d value normally 0.7
	int dPow;

    while((pros::millis()-startMillis) < timeout){

		err = targetValue - (posGyro.get_value()/10); 
		derr = (err - err_last); 
		err_last = err;
		p = (KP * err); 
		err_sum += err;
		d = KD * derr;

		dPow = (p+d);

		//dPow = (dPow > 100 ? 100 : dPow < -100 ? -100 : dPow);
		if(dPow > 100){dPow=100;};
		if(dPow < -100){dPow=-100;};

		setDrive(-dPow, dPow);
	}
}



void Chassis::pid(int targetValue, int maxSpeed, int timeout, float kP, float kD){
	int startMillis = pros::millis();

	//int left side pid
	int errL = 0; //error value init
	int derrL = 0;//error difference
	int err_lastL = 0; //last error
	int err_sumL = 0; //sum of errors
	float pL;
	float dL;

	//int right side pid
	int errR = 0; //error value init
	int derrR = 0;//error difference
	int err_lastR = 0; //last error
	int err_sumR = 0; //sum of errors
	float pR;
	float dR;
	
	//int outputs
	int dPowL;
	int dPowR;

	while((pros::millis()-startMillis) < timeout){

		errL = targetValue - driveLB.get_position();
		err_lastL = errL; 
		derrL = (errL - err_lastL); 
		pL = (kP * errL); 
		err_sumL += errL;
		dL = kD * derrL;

		errR = targetValue - driveRB.get_position();
		err_lastR = errR; 
		derrR = (errR - err_lastR); 
		pR = (kP * errR); 
		err_sumL += errR;
		dR = kD * derrR;
		
		dPowL = (pL+dL);
		dPowR = (pR+dR);

		if(dPowL > maxSpeed){dPowL=maxSpeed;};
		if(dPowL < -maxSpeed){dPowL=-maxSpeed;};
		if(dPowR > maxSpeed){dPowR=maxSpeed;};
		if(dPowR < -maxSpeed){dPowR=-maxSpeed;};

		setDrive(dPowR, dPowL);
	}
}

void Chassis::stop(void){
	driveRF.move_velocity(0);
    driveLB.move_velocity(0);
    driveRB.move_velocity(0);
    driveLF.move_velocity(0);
}