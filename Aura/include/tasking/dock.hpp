/**
 * @file tasking/dock.hpp
 * 
 * Aura  -  dock.hpp
 * 
 * Dock Declarations Header File
 */
#ifndef _DOCK_HPP_
#define _DOCK_HPP_

//DOCK PRESETS
#define DOCK_UP 0
#define DOCK_DOWN 1

//set to disable to disable initialization of Dock task
//Dock will NOT run if set false
const bool Dock_Task_Enable = true;

//Docker Class - used to control the rear mogo lift (dock)
class Docker{
    
    public:

        /**
         * Initialization of the Dock
         * 
         * @param maximumVelocity
         *      The maximum velocity the Dock can move in the PID
         * @param nkP
         *      The Dock's kP Value
         * @param nkD
         *      The Docks kD Value
         * @param iState
         *      The initial PID state given to the controller at startup
         * @param wait
         *      Dont Move the Dock at startup
         *      
        */
        Docker(int maximumVeloity, float nkP, float nkD, int iState, bool wait);

        /**
         * Initialization of the Dock
         * 
         * @param maximumVelocity
         *      The maximum velocity the Dock can move in the PID
         * @param nkP
         *      The Dock's kP Value
         * @param nkD
         *      The Docks kD Value
         *      
        */
        Docker(int maximumVeloity, float nkP, float nkD);

        //manual control
        void manual(int velocity, bool enabled);

        //manual control of Dock (meant for use with controllers)
        void manual(int velocity);

        //change pid constraints
        void PID(int maxVel, float kP, float kD);

        int maxVel; //maxuimum velocity of Dock motors

        float kP; //kP of Dock

        float kD; //kD of Dock

        //allows PD controller to be temporary disabled in order for manual adjustment of the Dock
        bool manual_exemption;

        //current lift state
        int state;

        //stores the last state the lift was set to
        int state_prev;

        int targetValue;

        //simple preset
        void up();
        //simple preset
        void down();

        //move the dock to a preset
        void preset(int state);

        //move the dock to a custom preset
        void targ(int targetValue);

        /**
         * Docker Home Tare Function
         * Homes the dock back to its starting position using a limit switch, 
         * works like a 3D printer..
         * @param homeSpeed
         *      The speed to move the dock home
         * @return the docks homed position (should be 0)
         */
        int home_tare(int homeSpeed);
};

//Dock class
extern Docker dock;

//DockTask
void Dock_Task_fn(void*param);

#endif