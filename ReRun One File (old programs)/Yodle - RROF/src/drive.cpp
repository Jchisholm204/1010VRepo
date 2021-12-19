#include "main.h"
#include "robot/drive.h"

//what direction is forwards?
int forwardsDrive = Front;
int getDist(int side){
	int out;
	if(forwardsDrive == Front){
		if(side == Right){
			out = lidarBR.get();
		}
		if(side == Left){
			out = lidarBL.get();
		}
	}
	if(forwardsDrive == Back){
		if(side == Right){
			out = lidarFL.get();
		}
		if(side == Left){
			out = lidarFR.get();
		}
	}
	return out;
}

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
  int Yval = exponential(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), 1.5 /*DriveExp*/, 4 /*JoyDead*/, 25 /*MotorMin*/);
  int Xval = exponential(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X), 1.3, 4, 20);
  //remove "= 0" and comment if you wish to use mechanum drive
  int Zval = 0;//(exponential(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), 2.2, 20, 15)*0);

  driveLB.move(Yval + Xval - Zval);
  driveLF.move(Yval + Xval + Zval);
  driveRB.move(Yval - Xval + Zval);
  driveRF.move(Yval - Xval - Zval);
}


void Chassis::flip(int NewFront, bool swapLidars){
	forwardsDrive = NewFront;
}

void Chassis::timeDrive(int time, int leftPow, int rightPow, bool use_NewFront){
	driveRF.move_velocity(forwardsDrive * rightPow);
    driveLB.move_velocity(forwardsDrive * leftPow);
    driveRB.move_velocity(forwardsDrive * rightPow);
    driveLF.move_velocity(forwardsDrive * leftPow);
	pros::delay(time);
	driveRF.move(0);
    driveLB.move(0);
    driveRB.move(0);
    driveLF.move(0);
}
void Chassis::driveTurn(int leftTarget, int maxLeft, int rightTarget, int maxRight, int timeout, bool use_NewFront){
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

		if(use_NewFront){
			dPowL = (pL+dL)*forwardsDrive;
			dPowR = (pR+dR)*forwardsDrive;
		}
		else{
			dPowL = (pL+dL);
			dPowR = (pR+dR);			
		}

		//dPowL = (dPowL > 100 ? 100 : dPowL < -100 ? -100 : dPowL);
		//dPowR = (dPowR > 100 ? 100 : dPowR < -100 ? -100 : dPowR);
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

void Chassis::move(int targetValue, int timeout, bool use_NewFront){
	driveLF.tare_position();
	driveRF.tare_position();
	int startMillis = pros::millis();

    float KP = 0.8;
	float KD = 1.8;
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
		errL = targetValue - driveLF.get_position();
		derrL = (errL - err_lastL); 
		err_lastL = errL; 
		pL = (KP * errL); 
		err_sumL += errL;
		dL = KD * derrL;

		//Right PID
		errR = targetValue - driveRF.get_position(); 
		derrR = (errR - err_lastR); 
		err_lastR = errR;
		pR = (KP * errR); 
		err_sumL += errR;
		dR = KD * derrR;

		dPowL = (pL+dL);
		dPowR = (pR+dR);			

		//dPowL = (dPowL > 100 ? 100 : dPowL < -100 ? -100 : dPowL);
		//dPowR = (dPowR > 100 ? 100 : dPowR < -100 ? -100 : dPowR);
		if(dPowL > 150){dPowL=150;};
		if(dPowL < -150){dPowL=-150;};
		if(dPowR > 150){dPowR=150;};
		if(dPowR < -150){dPowR=-150;};

		driveRF.move(dPowR);
      	driveLB.move(dPowL);
      	driveRB.move(dPowR);
      	driveLF.move(dPowL);
	}
}

void Chassis::LineDrive(int targetValue, int timeout){
	driveLF.tare_position();
	driveRF.tare_position();
	int startMillis = pros::millis();
	int drive_diff = 0;

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

	int dPowR;
	int dPowL;



    while((pros::millis()-startMillis) < timeout){
		//Difference Calculations
		drive_diff = ((abs(targetValue) - abs(driveLF.get_position())+10)) / ((abs(targetValue) - abs(driveRF.get_position())+10));

		//Left PID
		errL = targetValue - driveLF.get_position();
		err_lastL = errL; 
		derrL = (errL - err_lastL); 
		pL = (KP * errL); 
		err_sumL += errL;
		dL = KD * derrL;

		//Right PID
		errR = targetValue - driveRF.get_position();
		err_lastR = errR; 
		derrR = (errR - err_lastR); 
		pR = (KP * errR); 
		err_sumL += errR;
		dR = KD * derrR;

		dPowL = (pL+dL);
		dPowR = (pR+dR);

		//dPowL = (dPowL > 100 ? 100 : dPowL < -100 ? -100 : dPowL);
		//dPowR = (dPowR > 100 ? 100 : dPowR < -100 ? -100 : dPowR);
		if(dPowL > 100){dPowL=100;};
		if(dPowL < -100){dPowL=-100;};
		if(dPowR > 100){dPowR=100;};
		if(dPowR < -100){dPowR=-100;};

		driveRF.move(dPowR / drive_diff);
      	driveLB.move(dPowL * drive_diff);
      	driveRB.move(dPowR / drive_diff);
      	driveLF.move(dPowL * drive_diff);
	}
}

void Chassis::drive(int targetValue, int timeout, bool use_NewFront){
	int startMillis = pros::millis();

    float KP = 0.6;
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

	int driveReversedMultiplication = 1; //not reversed
	int curLeft;
	int curRight;

	while((pros::millis()-startMillis) < timeout){

		if(use_NewFront){
			driveReversedMultiplication = forwardsDrive;
			curLeft = getDist(Left);
			curRight = getDist(Right);
		}
		else{
			curLeft = lidarBL.get();
			curRight = lidarBR.get();	
		}

		errL = targetValue - curLeft;
		err_lastL = errL; 
		derrL = (errL - err_lastL); 
		pL = (KP * errL); 
		err_sumL += errL;
		dL = KD * derrL;

		errR = targetValue - curRight;
		err_lastR = errR; 
		derrR = (errR - err_lastR); 
		pR = (KP * errR); 
		err_sumL += errR;
		dR = KD * derrR;

		dPowL = (pL+dL);
		dPowR = (pR+dR);

		//dPowL = (dPowL > 100 ? 100 : dPowL < -100 ? -100 : dPowL);
		//dPowR = (dPowR > 100 ? 100 : dPowR < -100 ? -100 : dPowR);
		if(dPowL > 100){dPowL=100;};
		if(dPowL < -100){dPowL=-100;};
		if(dPowR > 100){dPowR=100;};
		if(dPowR < -100){dPowR=-100;};


		driveRF.move(dPowR*driveReversedMultiplication);
      	driveLB.move(dPowL*driveReversedMultiplication);
      	driveRB.move(dPowR*driveReversedMultiplication);
      	driveLF.move(dPowL*driveReversedMultiplication);
	}
}

void Chassis::turn(int targetValue, int timeout){
	//gyro.tare_rotation(); //returns (+) or (-) rotation values in deg
	giro.reset();
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

		err = targetValue - (giro.get_value()/10); 
		derr = (err - err_last); 
		err_last = err;
		p = (KP * err); 
		err_sum += err;
		d = KD * derr;

		dPow = (p+d);

		//dPow = (dPow > 100 ? 100 : dPow < -100 ? -100 : dPow);
		if(dPow > 100){dPow=100;};
		if(dPow < -100){dPow=-100;};

		driveRF.move(-dPow);
      	driveLB.move(dPow);
      	driveRB.move(-dPow);
      	driveLF.move(dPow);
	}
}

int headingCalc(pros::ADIGyro gboi){
	int rawPos = gboi.get_value()/10; //get deg of gyro turn from origin
	int modt = rawPos % 360; //get remainder when dividing by 360, returns (-360, 360)
	int filtered = (modt + 360) % 360; // make final value between [0, 360]
	return filtered; //return final value
}

void Chassis::heading(int targHeading, int offset, int timeout){
	//gyro.get_heading() //gets a (+) value between 0 and 360 deg
	int startMillis = pros::millis();
    float KP = 0.8;
	float KD = 1.2;
	int err = 0; //error value init
	int derr = 0;//error difference
	int err_last = 0; //last error
	int err_sum = 0; //sum of errors
	float p; //p value normally 0.8
	float d; //d value normally 0.7
	int dPow;

    while((pros::millis()-startMillis) < timeout){

		err = targHeading - (headingCalc(absGyro) + offset);
		err_last = err; 
		derr = (err - err_last); 
		p = (KP * err); 
		err_sum += err;
		d = KD * derr;

		dPow = (p+d);

		//dPow = (dPow > 100 ? 100 : dPow < -100 ? -100 : dPow);
		if(dPow > 127){dPow=127;};
		if(dPow < -127){dPow=-127;};


		driveRF.move(-dPow);
      	driveLB.move(dPow);
      	driveRB.move(-dPow);
      	driveLF.move(dPow);
	}
}

void Chassis::turnDrive(int turnDeg, int innerPower, int outterPower, int timeout, bool use_NewFront){
	gyro.tare_rotation(); //reset gyro zero value
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

	int rPow;
	int lPow;

    while((pros::millis()-startMillis) < timeout){

		err = turnDeg - gyro.get_rotation();
		derr = (err - err_last); 
		err_last = err;
		p = (KP * err); 
		err_sum += err;
		d = KD * derr;

		dPow = (p+d);

		if(turnDeg > 0 && use_NewFront && forwardsDrive == Front){
			rPow = dPow;
			lPow = dPow;

			if(rPow > innerPower){rPow=innerPower;};
			if(rPow < -innerPower){rPow=-innerPower;};
			if(lPow > outterPower){lPow=outterPower;};
			if(lPow < -outterPower){lPow=-outterPower;};
		}
		if(turnDeg < 0 && use_NewFront && forwardsDrive == Front){
			rPow = dPow;
			lPow = dPow;

			if(rPow > outterPower){rPow=outterPower;};
			if(rPow < -outterPower){rPow=-outterPower;};
			if(lPow > innerPower){lPow=innerPower;};
			if(lPow < -innerPower){lPow=-innerPower;};
		}
		if(turnDeg < 0 && use_NewFront && forwardsDrive == Back){
			rPow = -dPow;
			lPow = -dPow;

			if(rPow > innerPower){rPow=innerPower;};
			if(rPow < -innerPower){rPow=-innerPower;};
			if(lPow > outterPower){lPow=outterPower;};
			if(lPow < -outterPower){lPow=-outterPower;};
		}
		if(turnDeg > 0 && use_NewFront && forwardsDrive == Back){
			rPow = -dPow;
			lPow = -dPow;

			if(rPow > outterPower){rPow=outterPower;};
			if(rPow < -outterPower){rPow=-outterPower;};
			if(lPow > innerPower){lPow=innerPower;};
			if(lPow < -innerPower){lPow=-innerPower;};
		}
		//dPow = (dPow > 100 ? 100 : dPow < -100 ? -100 : dPow);

		driveRF.move(rPow);
      	driveLB.move(lPow);
      	driveRB.move(rPow);
      	driveLF.move(lPow);
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

		driveRF.move_velocity(dPowR);
      	driveLB.move_velocity(dPowL);
      	driveRB.move_velocity(dPowR);
      	driveLF.move_velocity(dPowL);
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