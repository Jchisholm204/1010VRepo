/* Ingenuity - pneumatics.cpp
/* - main.h
/* - tasking/pneumatics.h
* This is not the best way to do Pneumatics, but it is the only way I've found to do it with ReRun integration
*/

//#include "main.h"
#include "tasking/pneumatics.hpp"
#include "main.h"

// Global Variables for controlling the states of Pneumatics

bool Lift_Piston_State; // Lift Pneumatic State
bool Dock_Piston_State; // Dock Pneumatic State
bool Side_Piston_State; // Side MOGO Pneumatic State

/* Piston Task Function:
    Updates the value applied to the ADI port to reflect that of the live value stored within the Piston_State variables
*/

void piston_task_fn(void*param){

    while(true){

        LiftPiston.set_value(Lift_Piston_State);
        DockPiston.set_value(Dock_Piston_State);
        SidePiston.set_value(Side_Piston_State);

        pros::delay(100); //use a long delay to prevent overloading the brain

    }
}