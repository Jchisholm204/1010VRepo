/* Ingenuity - pneumatics.cpp
/* - main.h
/* - tasking/pneumatics.h
*/

//#include "main.h"
#include "tasking/pneumatics.hpp"
#include "main.h"

bool Lift_Piston_State;
bool Dock_Piston_State;
bool Side_Piston_State;

void piston_task_fn(void*param){
    while(true){
        LiftPiston.set_value(Lift_Piston_State);
        DockPiston.set_value(Dock_Piston_State);
        SidePiston.set_value(Side_Piston_State);
        pros::delay(100);
    }
}