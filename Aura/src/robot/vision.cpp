/* Aura - vision.cpp
/* - vision.hpp
* Vision Test File

# Written By: Jacob Chisholm
# Written For: Ten Ton Vex Robotics Team 1010V

*/

#include "main.h"
#include "robot/display.h"
#include "autos.hpp"
#include "robot/vision.hpp"

using namespace pros;

void vsProgram(){
    vision_object_s_t rtn = visionSensor.get_by_size(0);
    // Gets the largest object
    std::cout << "sig: " << rtn.signature;
}