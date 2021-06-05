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

void cycle(int balls){
        int count = 0;
        bool reset = 1;
    while(balls != 0){
        if(ballDetector.get_value() < 50 && reset == 1){
            count +=1;
            balls -=1;
            reset = 0;
        }
        if(ballDetector.get_value() > 150){
            reset = 1;
        }
        if (balls == 1){
            intakes(0);
        }
        //printf("DIS: %d\t COUNT: %d\n", ballDetector.get_value(), count);
        pros::delay(10);
    }
}

void colorCycle(int color){
    auto rgb_value = colorSensor.get_rgb();
    if (color == 0){
        auto colorGet = rgb_value.red;
        int colorWanted = 0;
    }
    else if (color == 1){
        auto colorGet = rgb_value.blue;
        int colorWanted = 0;
    }
}