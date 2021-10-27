#include "main.h"
#include "autons.h"
#include "drive.h"
#include "ext.h"

void testAuto(void){
    //Place Auto Code Here
}

void ExampleAuto(void){
    //Place Auto Code Here
    Dock(POS_DOWN); //moves the dock to its lowest state
    Dock(POS_UP); //moves the dock back up
    drivef.move(200/*Encoder Units*/, 800/*timeout*/); //moves the drivebase 200 encoder units forward, maximum timeout 800 ms (milliseconds)
    drivef.time(1200/*timeout*/, -100/*Direction/Power(rpm)*/); //moves the drivebase backwards with a speed of 100 rpm for 1200 ms
    drivef.timeDrive(1000/*timeout*/, 100/*Left Power*/, -100/*Right Power*/);  //moves the left side of the drivebase @ 100rpm, the right side @ -100 rpm for 1000 ms
    drivef.heading(0/*heading*/, 0/*offset*/, 1000/*timeout*/); //GYRO REQUIRED --- turns the drivebase back to its starting position, gives it 1000ms (1 second) to turn with an ofset of 0 deg
    drivef.turn(45/*degrees to turn*/, 1000/*timeout*/); //turns the drivebase 45deg clockwise (+) with a timeout of 1000ms

}