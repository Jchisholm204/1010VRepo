/* Aura - drive.cpp
/* - main.h
/* - robot/drive.hpp
* Drive functions and operator control code for the chassis
*/
#include "main.h"
#include "robot/drive.hpp"

using namespace pros;

Chassis::Chassis(float maxVal, float nkP, float nkD){
	drive_PID[drive_max_power] = maxVal;
	drive_PID[drive_kP] = nkP;
	drive_PID[drive_kD] = nkD;
}

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

void Chassis::operator_Chassis(int maxVel){
  int Yval = exponential(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), 1.5 /*DriveExp*/, 4 /*JoyDead*/, 25 /*MotorMin*/);
  int Xval = exponential(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X), 1.3, 4, 20);
  //remove "= 0" and comment if you wish to use mechanum drive
  int Zval = 0;//(exponential(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), 2.2, 20, 15)*0);

  Xval = Xval*maxVel/127;
  Yval = Yval*maxVel/127;

  driveLB.move_velocity(Yval + Xval - Zval);
  driveLF.move_velocity(Yval + Xval + Zval);
  driveRB.move_velocity(Yval - Xval + Zval);
  driveRF.move_velocity(Yval - Xval - Zval);
}


void Chassis::time(int time, int leftPow, int rightPow){
	driveRF.move_velocity(rightPow);
    driveLB.move_velocity(leftPow);
    driveRB.move_velocity(rightPow);
    driveLF.move_velocity(leftPow);
	pros::delay(time);
	driveRF.move(0);
    driveLB.move(0);
    driveRB.move(0);
    driveLF.move(0);
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


void Chassis::driveTurn(int leftTarget, int maxLeft, int rightTarget, int maxRight, int timeout){
	driveLF.tare_position();
	driveRF.tare_position();
	int startMillis = pros::millis();

    //float KP = 1.2;
	//float KD = 1.4;
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
		pL = (drive_PID[drive_kP] * errL); 
		err_sumL += errL;
		dL = drive_PID[drive_kD] * derrL;

		//Right PID
		errR = rightTarget - driveRF.get_position();
		derrR = (errR - err_lastR); 
		err_lastR = errR; 
		pR = (drive_PID[drive_kP] * errR); 
		err_sumL += errR;
		dR = drive_PID[drive_kD] * derrR;

		dPowL = (pL+dL);
		dPowR = (pR+dR);			


		if(dPowL > maxLeft){dPowL=maxLeft;};
		if(dPowL < -maxLeft){dPowL=-maxLeft;};
		if(dPowR > maxRight){dPowR=maxRight;};
		if(dPowR < -maxRight){dPowR=-maxRight;};

		driveRF.move(dPowR);
      	driveLB.move(dPowL);
      	driveRB.move(dPowR);
      	driveLF.move(dPowL);
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
		if(dPow > drive_PID[drive_max_power]){dPow=drive_PID[drive_max_power];};
		if(dPow < -drive_PID[drive_max_power]){dPow=-drive_PID[drive_max_power];};

		driveRF.move(-dPow);
      	driveLB.move(dPow);
      	driveRB.move(-dPow);
      	driveLF.move(dPow);
	}
}

void Chassis::adj_pid(float MaxPower, float nkP, float nkD){
	drive_PID[drive_max_power] = MaxPower;
	drive_PID[drive_kP] = nkP;
	drive_PID[drive_kD] = nkD;	
}

void Chassis::drive(int targetValue, int maxSpeed, int timeout){
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
		pL = (drive_PID[drive_kP] * errL); 
		err_sumL += errL;
		dL = drive_PID[drive_kD] * derrL;

		errR = targetValue - driveRB.get_position();
		err_lastR = errR; 
		derrR = (errR - err_lastR); 
		pR = (drive_PID[drive_kP] * errR); 
		err_sumL += errR;
		dR = drive_PID[drive_kD] * derrR;
		
		dPowL = (pL+dL);
		dPowR = (pR+dR);

		if(dPowL > maxSpeed){dPowL=maxSpeed;};
		if(dPowL < -maxSpeed){dPowL=-maxSpeed;};
		if(dPowR > maxSpeed){dPowR=maxSpeed;};
		if(dPowR < -maxSpeed){dPowR=-maxSpeed;};

		driveRF.move_velocity(dPowR);
      	driveLB.move_velocity(dPowL);
      	driveRB.move_velocity(dPowR);
      	driveLF.move_velocity(dPowL);
	}
}

void Chassis::distance(int source, int targetValue, int timeout){
	int startMillis = pros::millis();

	//int left side pid
	int left_cur_pos;
	int errL = 0; //error value init
	int derrL = 0;//error difference
	int err_lastL = 0; //last error
	int err_sumL = 0; //sum of errors
	float pL;
	float dL;

	//int right side pid
	int right_cur_pos;
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

		if(source == ENCODERS){
			right_cur_pos = driveRB.get_position();
			left_cur_pos = driveLB.get_position();
		}
		else if (source == Front_Distance){
			right_cur_pos = distFR.get();
			left_cur_pos = distFL.get();
		}
		else if (source == Back_Distance){
			right_cur_pos = distBR.get();
			left_cur_pos = distBL.get();
		}

		errL = targetValue - left_cur_pos;
		err_lastL = errL; 
		derrL = (errL - err_lastL); 
		pL = (drive_PID[drive_kP] * errL); 
		err_sumL += errL;
		dL = drive_PID[drive_kD] * derrL;

		errR = targetValue - right_cur_pos;
		err_lastR = errR; 
		derrR = (errR - err_lastR); 
		pR = (drive_PID[drive_kP] * errR); 
		err_sumL += errR;
		dR = drive_PID[drive_kD] * derrR;
		
		dPowL = (pL+dL);
		dPowR = (pR+dR);

		if(dPowL > drive_PID[drive_max_power]){dPowL=drive_PID[drive_max_power];};
		if(dPowL < -drive_PID[drive_max_power]){dPowL=-drive_PID[drive_max_power];};
		if(dPowR > drive_PID[drive_max_power]){dPowR=drive_PID[drive_max_power];};
		if(dPowR < -drive_PID[drive_max_power]){dPowR=-drive_PID[drive_max_power];};

		driveRF.move(dPowR);
      	driveLB.move(dPowL);
      	driveRB.move(dPowR);
      	driveLF.move(dPowL);
	}
}

void Chassis::stop(void){
	driveRF.move_velocity(0);
    driveLB.move_velocity(0);
    driveRB.move_velocity(0);
    driveLF.move_velocity(0);
}

void Chassis::reset(void){
	driveRB.tare_position();
	driveRF.tare_position();
	driveLB.tare_position();
	driveLF.tare_position();
}