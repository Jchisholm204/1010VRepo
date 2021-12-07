#ifndef _EXT_H_
#define _EXT_H_

//////////DOCKER///////////////////
extern int dock_state;
extern int arm_state;
//Lowest Dock Position
#define POS_DOWN 1
//Highest Dock Position
#define POS_UP 0

//Adjust Dock Position
extern void Dock(int state);

//adjust arm state
extern void Arm(int state);

//Run Intakes (speed)
extern void Intake(int speed);

void Docker_Task_fn(void*param);

void Arm_Task_fn(void*param);


#endif