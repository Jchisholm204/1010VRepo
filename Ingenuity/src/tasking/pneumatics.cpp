/* Ingenuity - pneumatics.cpp
/* - main.h
/* - tasking/pneumatics.h
* This is not the best way to do Pneumatics, but it is the only way I've found to do it with ReRun integration
*/

//#include "main.h"
#include "tasking/pneumatics.hpp"
#include "main.h"
#include "ttl/adiPiston.hpp"

// Global Variables for controlling the states of Pneumatics
// Default Piston States Set Here:

bool Lift_Piston_State = false; // Lift Pneumatic State
bool Dock_Piston_State = false; // Dock Pneumatic State
bool Side_Piston_State = false; // Side MOGO Pneumatic State

ttl::ADIPiston pp('h', true);

/* Piston Task Function:
    Updates the value applied to the ADI port to reflect that of the live value stored within the Piston_State variables
*/

void piston_task_fn(void*param){

    while(true){

        LiftPiston.set_value(Lift_Piston_State);
        DockPiston.set_value(Dock_Piston_State);
        SidePiston.set_value(Side_Piston_State);
        pp.toggle();

        pros::delay(1000); //use a long delay to prevent overloading the brain

    }
}