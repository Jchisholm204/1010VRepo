#ifndef _DOCKER_H_
#define _DOCKER_H_

extern int dock_state;
#define POS_DOWN 1
#define POS_UP 0

void Docker_Task_fn(void*param);

#endif