/* Ingenuity - pneumatics.hpp
*/
#ifndef _PNEUMATICS_HPP_
#define _PNEUMATICS_HPP_

//Set to false to disable initialization of the Piston Task
const bool Piston_Task_Enable = true;

extern bool Lift_Piston_State; // Lift Pneumatic State
extern bool Dock_Piston_State; // Dock Pneumatic State
extern bool Side_Piston_State; // Side MOGO Pneumatic State

//for running all of the pistons so that they are rerun compatable
void piston_task_fn(void*param);

#endif