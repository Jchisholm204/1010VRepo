#ifndef _EXT_H_
#define _EXT_H_

//////////DOCKER///////////////////
extern int dock_state;
#define POS_DOWN 1
#define POS_UP 0

void Docker_Task_fn(void*param);
extern Task Docker_Task;


////////DIAGNOSTICS///////////
class Diagnostics{
    public:
    //report system errors
    void report(auto error, auto subsystem, auto print);
    void fatal(auto error, auto subsystem);
};


#endif