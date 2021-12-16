/* Ingenuity - pneumatics.cpp
/* - main.h
/* - pneumatics.h
* Custom Library for interfacing with PROS Pistons
*/

//#include "main.h"
#include "robot/pneumatics.hpp"

Piston::Piston(pros::ADIDigitalOut stabby, bool startState){
    pistonState = startState;
}

bool Piston::set_state(bool newState){
    pistonState = newState;
    //stabby.set_value(newState);
}

bool Piston::get_state(void){
    return pistonState;
}

bool Piston::toggle(void){
    pistonState = !pistonState;
    //stabby.set_value(pistonState);
}