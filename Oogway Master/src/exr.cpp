#include "main.h"
#include "drive.h"
#include "display.h"
#include "autons.h"
#include "exr.h"
#include <string.h>

int ballCheck(void){
    int sensorVal = ballDetector.get_value();
    if(sensorVal < 100){
        return 0;
    }
    if ( 100 < sensorVal < 250){
        return 0.75;
    }
    else{
        return 1;
    }
}

int cycle(int balls, int rollerSpeed, int flyWheelSpeed){
    while(balls > 0){
        int count = 0;
        int last = 0;
        int largest = 0;
        if(ballDetector.get_value() > largest && ballDetector.get_value() < 200 && int(ballDetector.get_value()/20) > int(last/20)){
            largest = ballDetector.get_value();
        }
        else if(ballDetector.get_value() < largest && (largest - ballDetector.get_value()) > 50){
            count++;
            balls--;
            largest = 0;
        }
        else{
        }
        if(balls < 0){
            roller.move(0);
            flyWheel.move(50);
            flyWheel.move(0);
            return 0;
        }
        else{
            roller.move_velocity(rollerSpeed);
            flyWheel.move_velocity(flyWheelSpeed);
        }
        last = ballDetector.get_value();
    }
}