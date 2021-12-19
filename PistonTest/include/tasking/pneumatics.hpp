/* Ingenuity - pneumatics.hpp
*/
#ifndef _PNEUMATICS_HPP_
#define _PNEUMATICS_HPP_
#include "main.h"

const bool Piston_Task_Enable = true;

extern bool Lift_Piston_State;
extern bool Dock_Piston_State;
extern bool Side_Piston_State;

//for running all of the pistons so that they are rerun compatable
void piston_task_fn(void*param);

#endif