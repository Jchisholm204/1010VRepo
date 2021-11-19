#ifndef _LIFT_H_
#define _LIFT_H_
//liftState
extern int lift_state;

const bool Lift_Task_Enable = true;
//liftTask
void Lift_Task_fn(void*param);

#endif