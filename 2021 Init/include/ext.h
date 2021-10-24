#ifndef _EXT_H_
#define _EXT_H_

//////////DOCKER///////////////////
extern int dock_state;
#define POS_DOWN 1
#define POS_UP 0

extern void Dock(int state);

void Docker_Task_fn(void*param);
extern Task Docker_Task;

////////MAIN-SYSTEMS///////////
#define SYS_MAIN 0
#define SYS_DOCKER 1
#define SYS_DISPLAY 2
//--------SUB-SYSTEMS---------//
#define SUB_DRIVE 3


////////DIAGNOSTICS///////////
class Diagnostics{
    public:
    //report system errors
    void report(std::string error, int subsystem, std::string print);
    void fatal(std::string error, int subsystem);
};


#endif