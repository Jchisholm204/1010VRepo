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


void Chassis::timeDrive(int time/*the time it drives for*/, int vel/*the entered Speed*/, int cooldown/*the period that the robot should drive for a slower % of the speed*/){
  driveLB.move_velocity(vel);
  driveLF.move_velocity(vel);
  driveRB.move_velocity(vel);
  driveRF.move_velocity(vel);
//
  delay(time*(1-cooldown));

  driveLB.move_velocity(vel*0.25);
  driveLF.move_velocity(vel*0.25);
  driveRB.move_velocity(vel*0.25);
  driveRF.move_velocity(vel*0.25);
//
  delay(time*cooldown);
//stop
  driveLB.move_velocity(0);
  driveLF.move_velocity(0);
  driveRB.move_velocity(0);
  driveRF.move_velocity(0);
}

void Chassis::stopDriving(void){
  driveLB.move_velocity(0);
  driveLF.move_velocity(0);
  driveRB.move_velocity(0);
  driveRF.move_velocity(0);
}
void Chassis::startDriving(int speed){
  driveLB.move_velocity(speed);
  driveLF.move_velocity(speed);
  driveRB.move_velocity(speed);
  driveRF.move_velocity(speed);
}

void Chassis::TurnDistance(int direction, int targetValue, int timeout){
		float driveKP = 0.7;
		float driveKD = 1;
		int motorPower; //motor power level
		int startTime = millis(); //Elapsed time since start of the sequence
		int currentValue = 0; //starting value of 0
		int turn_err = 0; //error value init
		int derr = 0;//error difference
		int err_last = 0; //last error
		int err_sum = 0; //sum of errors
		float KI = 0; //KI value - not currently used'
		float p; //p value normally 0.8
		float i = 0; //I value
		float d; //d value normally 0.7
		driveLB.tare_position();
		driveRB.tare_position();
		while((millis() - startTime) < timeout){
			//reset motor encoders
			if(direction == DIRECTION_RIGHT){  //left encoder if turing right
				currentValue = abs(driveLB.get_position());
			}
			else if(direction == DIRECTION_LEFT){  // right encoder if turing left
				currentValue = abs(driveRB.get_position());
			}
			turn_err = targetValue - currentValue; //error is how far the current position is from the position you put into the loop
			err_last = turn_err; //stores the error
			derr = (turn_err - err_last); //difference between how far you were from the target last sequence compared to this sequence
			p = (driveKP * turn_err); //p value is preset driveKP multiplied by how far we are from our target
			err_sum += turn_err; //err_sum increases by the sum of errors
			d = driveKD * derr; //d value is preset driveKD multiplied by the difference between how far you were from the last rotation

			motorPower = p+i+d; //motorpower is the sum of p, i, and d

			if(motorPower > 25){motorPower = 25;} //if the motor power is greater than 127 (the maximun it can go), set it to 127
			if(motorPower < -25){motorPower = -25;}//if the motor power is less than -127 (the minimum it can go), set it to -127

				driveRF.move(direction*motorPower);
				driveLB.move((-direction*motorPower));
				driveRB.move((direction*motorPower));
				driveLF.move(-direction*motorPower);
			delay(20);
		}
}

void Chassis::MoveDistance(int direction, int targetValue, int timeout){
	float driveKP = 1.2;
	float driveKD = 0.8;
	int motorPower; //motor power level
	int startTime = millis(); //Elapsed time since start of the sequence
	int currentValue = 0; //starting value of 0
	int turn_err = 0; //error value init
	int derr = 0;//error difference
	int err_last = 0; //last error
	int err_sum = 0; //sum of errors
	float KI = 0; //KI value - not currently used'
	float p; //p value normally 0.8
	float i = 0; //I value
	float d; //d value normally 0.7
	driveRB.tare_position();
	driveLB.tare_position();
	while((millis() - startTime) < timeout){
		currentValue = abs(driveRB.get_position() + driveLB.get_position()) /2;
		turn_err = targetValue - currentValue; //error is how far the current position is from the position you put into the loop
		err_last = turn_err; //stores the error
		derr = (turn_err - err_last); //difference between how far you were from the target last sequence compared to this sequence
		p = (driveKP * turn_err); //p value is preset driveKP multiplied by how far we are from our target
		err_sum += turn_err; //err_sum increases by the sum of errors
		d = driveKD * derr; //d value is preset driveKD multiplied by the difference between how far you were from the last rotation

		motorPower = p+i+d; //motorpower is the sum of p, i, and d

		if(motorPower > 100){motorPower = 100;} //if the motor power is greater than 127 (the maximun it can go), set it to 127
		if(motorPower < -100){motorPower = -100;}//if the motor power is less than -127 (the minimum it can go), set it to -127

		driveRF.move(direction*motorPower);
      	driveLB.move((direction*motorPower));
      	driveRB.move((direction*motorPower));
      	driveLF.move(direction*motorPower);
		delay(20);
	}
}

void Chassis::driveULT(int targetValue, ADIUltrasonic sensor, int timeout, int slowdownfactor, int slowdownValue){
	float driveKP = 1.2;
	float driveKD = 0.8;
	int motorpower;
	int startTime = pros::millis();
	int currentValue = 0;
	int err = 0;
	int derr = 0;
	int err_last = 0;
	int err_sum = 0;
	float KI = 0;
	float p;
	float i;
	float d;
	
	while(pros::millis() - startTime < timeout){
		currentValue = sensor.get_value();
		err = targetValue - currentValue; //error is how far the current position is from the position you put into the loop
		err_last = err; //stores the error
		derr = (err - err_last); //difference between how far you were from the target last sequence compared to this sequence
		p = (driveKP * err); //p value is preset driveKP multiplied by how far we are from our target
		err_sum += err; //err_sum increases by the sum of errors
		d = driveKD * derr; //d value is preset driveKD multiplied by the difference between how far you were from the last rotation

		motorpower = p + i + d;
		if(motorpower > 127){motorpower = 127;} //if the motor power is greater than 127 (the maximun it can go), set it to 127
		if(motorpower < -127){motorpower = -127;}//if the motor power is less than -127 (the minimum it can go), set it to -127

		if(slowdownfactor < 1 && slowdownValue > 0){
			if ((targetValue - slowdownValue) < sensor.get_value() < (targetValue + slowdownValue)){
				motorpower = motorpower * slowdownfactor;
			}

		}
		driveRF.move(motorpower);
      	driveLB.move(motorpower);
      	driveRB.move(motorpower);
      	driveLF.move(motorpower);
	}
}

void Chassis::towerDive(int stoppingValue, int slowdownfactor, int slowdownValue, int timeout){
	//int aVal;
	//int sValL = lLIDAR.get();
	//int sValR = rLIDAR.get();
	int errorLeft;
	int errorRight;
	//int DriveError;
	int leftPower;
	int rightPower;
	int startTime = pros::millis();
	
	while(pros::millis() - startTime < timeout){
		//aVal = ((lLIDAR.get() + rLIDAR.get()) /2);

		errorLeft = lLIDAR.get() - stoppingValue; //gets the remaining distance on the left side
		errorRight = rLIDAR.get() - stoppingValue; //gets the remaining distance on the right side
		
			//DriveError - keeps the two sides of the robot in position as well as helps to position the robot for shooting
		//DriveError = errorLeft - errorRight; 
			//turns positive if the left side is ahead of the right and negative if the right side is ahead of the left

		leftPower = (errorLeft * 1000); // drive error is negative when the left side is ahead, so slow the left side down
		rightPower = (errorRight * 1000); // drive error is positive when the right side is ahead, so slow the right side down

		if(leftPower > 50){leftPower = 50;} //if the motor power is greater than 127 (the maximun it can go), set it to 127
		if(leftPower < -50){leftPower = -50;}//if the motor power is less than -127 (the minimum it can go), set it to -127

		if(rightPower > 50){rightPower = 50;} //if the motor power is greater than 127 (the maximun it can go), set it to 127
		if(rightPower < -50){rightPower = -50;}//if the motor power is less than -127 (the minimum it can go), set it to -127
/*
		if(slowdownfactor < 1 && slowdownValue > 0){ //use slowdown factor to help with positional accuracy - does not work in place of pid, but serves simmarly
			if ((stoppingValue - slowdownValue) < aVal < (stoppingValue + slowdownValue)){ // if the target is close to the goal, engage the slowdown factor
				rightPower = rightPower * slowdownfactor; //if slowdown factor is engaged, multiply the motorpowers by the slowdown factor
				leftPower = leftPower * slowdownfactor;
			}
		}
*/
		driveRF.move(rightPower);
      	driveLB.move(leftPower);
      	driveRB.move(rightPower);
      	driveLF.move(leftPower);
	}
}

void Chassis::twrAlign(int timeout){
	int milis = pros::millis();
	int motorVel;
	while((pros::millis()-milis) < timeout){

		motorVel = (lLIDAR.get() - rLIDAR.get());

		driveRF.move_velocity(motorVel * -10);
      	driveLB.move_velocity(motorVel * 10);
      	driveRB.move_velocity(motorVel * -10);
      	driveLF.move_velocity(motorVel * 10);
	}
}