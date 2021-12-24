#ifndef _DOCK_HPP_
#define _DOCK_HPP_

//LIFT PRESETS
#define DOCK_UP 0
#define DOCK_DOWN 1

//set to disable to disable initialization of lift task
//Lift will NOT run if set false
const bool Lift_Task_Enable = true;


//Lift Class - used to control the front lift on the robot
class Docker{
    public:

        //initialization of the dock
        Docker(int maximumVeloity, float kP, float kD);

        //manual control
        void manual(int velocity, bool enabled);

        //Engage manual control of dock (meant for use with controllers)
        void manual(int velocity);

        //Change pid constraints
        void PID(int maxVel, float kP, float kD);

        //Allows PD controller to be temporary disabled in order for manual adjustment of the Lift
        bool dock_manual_exemption;

        //Current dock state
        int dock_state;

        //Current Dock PID TargetValue
        int targetValue;

        //simple preset
        void up();
        //simple preset
        void down();

        //move the dock to a preset
        void preset(int state);

        //move the dock to a custom preset
        void targ(int targetValue);

    private:
        int maxVel; //maxuimum velocity of lift motors

        float liftKp; //kP of Lift

        float liftKd; //kD of Lift

        //stores the last state the lift was set to
        int lift_state_prev;
};

//lift class
extern Lift lift;

//liftTask
void Lift_Task_fn(void*param);

#endif