#include "main.h"
#include "chassis.h"

int exponential (int joystickVal, float driveExp, int joyDead, int motorMin) { //exponential incrementation of joystick values
		   	int joySign;
		    int joyMax = 128 - joyDead;
		    int joyLive = abs(joystickVal) - joyDead;
		    if (joystickVal > 0) {joySign = 1;}
		    else if (joystickVal < 0) {joySign = -1;}
		    else {joySign = 0;}
		    int power = joySign * (motorMin + ((127 - motorMin) * (pow(joyLive, driveExp) / pow(joyMax, driveExp))));
		    return power;
}

void Chassis::OP_Chassis(void){
  int Y1 = exponential(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), 1.5 /*DriveExp*/, 8 /*JoyDead*/, 15 /*MotorMin*/);
	int X1 = exponential(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X), 1.5 /*DriveExp*/, 8 /*JoyDead*/, 15 /*MotorMin*/);
	int Z1 = exponential(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), 1.5 /*DriveExp*/, 8 /*JoyDead*/, 15 /*MotorMin*/);
	//int E2 = exponential(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_X), 1.5 /*DriveExp*/, 8 /*JoyDead*/, 15 /*MotorMin*/);
	//Expo drive outputs
	driveLF.move( Y1 + X1 + Z1 );  //map LF to left y, right X
	driveLB.move( Y1 + X1  - Z1 );  //map LB to left y, right X
	driveRF.move( Y1 - X1 - Z1 );  //map RF to left y, right X
	driveRB.move( Y1 - X1 + Z1 );  //map RB to left y, right X
}
void Chassis::angleDrive(int motor, int velocity, int time){
	switch(motor){
		case 1:
			driveLB.move_velocity(velocity);
			driveRF.move_velocity(velocity);
			break;
		case 2:
			driveRB.move_velocity(velocity);
			driveLF.move_velocity(velocity);
			break;
		default:
			printf("angledrive motor select err");
			break;
	};
	delay(time);
	//all drive motors stop
	driveLB.move(0);
	driveLF.move(0);
	driveRB.move(0);
	driveRF.move(0);
}
void Chassis::stopDriving(void){
	//all drive motors stop
	driveLB.move(0);
	driveLF.move(0);
	driveRB.move(0);
	driveRF.move(0);
}

void Chassis::timeDrive(int time, int velocity){
	//drive motors move velocity [Green = 200rpm min/max]
	driveLB.move_velocity(velocity);
	driveLF.move_velocity(velocity);
	driveRB.move_velocity(velocity);
	driveRF.move_velocity(velocity);
	pros::delay(time); //delay
	//all drive motors stop
	driveLB.move(0);
	driveLF.move(0);
	driveRB.move(0);
	driveRF.move(0);
}
void Chassis::timeGlide(int time, int velocity){
	//drive motors move velocity [Green = 200rpm min/max]
	driveLB.move_velocity(-velocity);
	driveLF.move_velocity(velocity);
	driveRB.move_velocity(velocity);
	driveRF.move_velocity(-velocity);
	pros::delay(time); //delay
	//all drive motors stop
	driveLB.move(0);
	driveLF.move(0);
	driveRB.move(0);
	driveRF.move(0);
}

void Chassis::TurnDistance(int direction, int targetValue, int speed, int timeout){
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
		driveLB.tare_position();
		driveRB.tare_position();
		while((millis() - startTime) < timeout){
			//reset motor encoders
			if(direction == DIRECTION_RIGHT){  //left encoder if turing right
				currentValue = driveLB.get_position();
			}
			else if(direction == DIRECTION_LEFT){  // right encoder if turing left
				currentValue = driveRB.get_position();
			}
			turn_err = targetValue - currentValue; //error is how far the current position is from the position you put into the loop
			err_last = turn_err; //stores the error
			derr = (turn_err - err_last); //difference between how far you were from the target last sequence compared to this sequence
			p = (driveKP * turn_err); //p value is preset driveKP multiplied by how far we are from our target
			err_sum += turn_err; //err_sum increases by the sum of errors
			d = driveKD * derr; //d value is preset driveKD multiplied by the difference between how far you were from the last rotation

			motorPower = p+i+d; //motorpower is the sum of p, i, and d

			if(motorPower > 50){motorPower = 50;} //if the motor power is greater than 127 (the maximun it can go), set it to 127
			if(motorPower < -50){motorPower = -50;}//if the motor power is less than -127 (the minimum it can go), set it to -127

				driveRF.move(direction*motorPower);
				driveLB.move((-direction*motorPower));
				driveRB.move((direction*motorPower));
				driveLF.move(-direction*motorPower);
			delay(20);
		}
}

void Chassis::MoveDistance(int direction, int targetValue, int speed, int timeout){
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
		currentValue = (driveRB.get_position() + driveLB.get_position()) /2;
		turn_err = targetValue - currentValue; //error is how far the current position is from the position you put into the loop
		err_last = turn_err; //stores the error
		derr = (turn_err - err_last); //difference between how far you were from the target last sequence compared to this sequence
		p = (driveKP * turn_err); //p value is preset driveKP multiplied by how far we are from our target
		err_sum += turn_err; //err_sum increases by the sum of errors
		d = driveKD * derr; //d value is preset driveKD multiplied by the difference between how far you were from the last rotation

		motorPower = p+i+d; //motorpower is the sum of p, i, and d

		if(motorPower > 85){motorPower = 85;} //if the motor power is greater than 127 (the maximun it can go), set it to 127
		if(motorPower < -85){motorPower = -85;}//if the motor power is less than -127 (the minimum it can go), set it to -127

			driveRF.move(direction*motorPower);
      driveLB.move((direction*motorPower));
      driveRB.move((direction*motorPower));
      driveLF.move(direction*motorPower);
		delay(20);
	}
}
	void Chassis::MoveSlow(int direction, int targetValue, int speed, int timeout){
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
			currentValue = (driveRB.get_position() + driveLB.get_position()) /2;
			turn_err = targetValue - currentValue; //error is how far the current position is from the position you put into the loop
			err_last = turn_err; //stores the error
			derr = (turn_err - err_last); //difference between how far you were from the target last sequence compared to this sequence
			p = (driveKP * turn_err); //p value is preset driveKP multiplied by how far we are from our target
			err_sum += turn_err; //err_sum increases by the sum of errors
			d = driveKD * derr; //d value is preset driveKD multiplied by the difference between how far you were from the last rotation

			motorPower = p+i+d; //motorpower is the sum of p, i, and d

			if(motorPower > 70){motorPower = 70;} //if the motor power is greater than 127 (the maximun it can go), set it to 127
			if(motorPower < -70){motorPower = -70;}//if the motor power is less than -127 (the minimum it can go), set it to -127

				driveRF.move(direction*motorPower);
	      driveLB.move((direction*motorPower));
	      driveRB.move((direction*motorPower));
	      driveLF.move(direction*motorPower);
			delay(20);
		}
	}
ADIGyro gyro ('d');
void Chassis::TurnGyro(int direction, int targetValue, int timeout){
	float driveKP = 1.2;
	float driveKD = 0.8;
	gyro.reset();
	//initialize variables

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

	while((millis() - startTime) < timeout){
		currentValue = gyro.get_value();
		turn_err = targetValue - currentValue; //error is how far the current position is from the position you put into the loop
		err_last = turn_err; //stores the error
		derr = (turn_err - err_last); //difference between how far you were from the target last sequence compared to this sequence
		p = (driveKP * turn_err); //p value is preset driveKP multiplied by how far we are from our target
		err_sum += turn_err; //err_sum increases by the sum of errors
		d = driveKD * derr; //d value is preset driveKD multiplied by the difference between how far you were from the last rotation

		motorPower = p+i+d; //motorpower is the sum of p, i, and d

		if(motorPower > 90){motorPower = 90;} //if the motor power is greater than 127 (the maximun it can go), set it to 127
		if(motorPower < -90){motorPower = -90;}//if the motor power is less than -127 (the minimum it can go), set it to -127

			driveRF.move(-direction*motorPower);
      driveLB.move((direction*motorPower));
      driveRB.move((-direction*motorPower));
      driveLF.move(direction*motorPower);
		delay(20);
	}
}
void switchDrive(int Mode, int direction, int targetValue, int timeout, float KP, float KD){
  //combination of driveValue, turnValue and strafeValue with a conditional called 'Mode' to switch between them
      int motorPower;
      int startTime = millis();
      int currentValue = 0;
      int err = 0;
      int derr = 0;
      int err_last = 0;
      int err_sum = 0;
      float KI = 0;
      float p;
      float i = 0;
      float d;
      driveLB.tare_position();
      while((millis() - startTime) < timeout){
        if(direction == DIRECTION_RIGHT){currentValue = driveLB.get_position();}
        else if(direction == DIRECTION_LEFT){currentValue = driveLB.get_position();}
        err = targetValue - currentValue;
        err_last = err;
        derr = (err - err_last);
        p = (KP * err);
        err_sum += err;
        d = KD * derr;

        motorPower = p+i+d;

        if(motorPower > 127){motorPower = 127;}
        if(motorPower < -127){motorPower = -127;}
        switch(Mode){ //switches the positives and negatives based on the selected mode
          case 0:
          driveLF.move(direction*motorPower);
          driveRF.move((direction*motorPower));
          driveLB.move((direction*motorPower));
          driveRB.move(direction*motorPower);
          case 1:
          driveLF.move(-direction*motorPower);
          driveLB.move(-direction*motorPower);
          driveRB.move((direction*motorPower));
          driveRF.move((direction*motorPower));
          case 2:
          driveLF.move(-direction*motorPower);
          driveRF.move((direction*motorPower));
          driveLB.move((direction*motorPower));
          driveRB.move(-direction*motorPower);
        }
        delay(20);
    }
}
