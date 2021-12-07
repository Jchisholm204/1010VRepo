#ifndef _LIFT_H_
#define _LIFT_H_

extern int lift_state;

const bool Lift_Task_Enable = true;

void Lift_Task_fn(void*param);

#endif