/* Ingenuity - pneumatics.hpp
*/
#ifndef _PNEUMATICS_HPP
#define _PNEUMATICS_HPP

extern bool Lift_Piston_State;
extern bool Dock_Piston_State;
extern bool Side_Piston_State;

//for running all of the pistons so that they are rerun compatable
void piston_task_fn(void*param);

#endif