/*#include "pid.h"
#include "main.h"

void PIDCONTROLLER::pid(int motor, int target, int timeout, float kP, float kI, float kD){
	int error, sumError, diffError, errorLast, output;
	int startTime = millis();
	while((millis() - startTime) < timeout){
		error = target - motor.get_position();
		sumError += error;
		diffError = error - errorLast;
		motor.move((error * kP) + (sumError * kI) + (diffError * kD));
		errorLast = error;
	}
}
*/
