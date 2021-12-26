/* Aura - skills.cpp
/* - main.h
/* - autos.hpp
* Skills Auto written here
*/
#include "main.h"
#include "robot/display.h"
#include "robot/drive.hpp"
#include "ttl/ttl.hpp"
#include "tasking/lift.hpp"
#include "tasking/dock.hpp"
#include "autos.hpp"
#include "robot/vision.hpp"

void skillsAuto(void){
    //drivef.vturn(VIS_SIG_RED_TOWER, 60000, 0, 1.1);
    drivef.vdrive(VIS_SIG_RED_TOWER, 150, 1, 90000);
}