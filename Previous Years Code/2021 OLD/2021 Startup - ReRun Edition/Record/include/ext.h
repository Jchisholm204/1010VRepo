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

//Dock Information Options
#define IS_TOWER 0

void Docker_Task_fn(void*param);

void Arm_Task_fn(void*param);

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