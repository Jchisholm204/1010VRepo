#ifndef _LIFT_H_
#define _LIFT_H_
//liftState
extern int lift_state;

const bool Lift_Task_Enable = true;

//reeee
extern bool lift_manual_exemption;

//Lift Piston State
//Lift Piston State = lpState
//Updated in lift files
extern bool lpState;

//store previous lift state for manual control
extern int lift_state_prev;
//liftTask
void Lift_Task_fn(void*param);

#endif