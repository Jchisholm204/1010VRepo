#ifndef _EXT_H_
#define _EXT_H_

//////////DOCKER///////////////////
extern int dock_state;
//Lowest Dock Position
#define POS_DOWN 1
//Highest Dock Position
#define POS_UP 0

//Adjust Dock Position
extern void Dock(int state);

//Run Intakes (speed)
extern void Intake(int speed);

void Docker_Task_fn(void*param);
extern Task Docker_Task;

void Arm_Task_fn(void*param);
extern Task Arm_Task;

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
    // report errors to the brain screen
    void reportSR(int subsystem, std::string displayError);
};


#endif