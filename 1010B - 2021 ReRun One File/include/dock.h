#ifndef _DOCK_H_
#define _DOCK_H_

extern int dock_state;

extern bool dock_manual_exemption;

extern int dock_state_prev;

const bool Dock_Task_Enable = true;

void Docker_Task_fn(void*param);

#endif