#ifndef _LIFT_HPP_
#define _LIFT_HPP_

//LIFT PRESETS
#define LIFT_UP 2
#define LIFT_HOLD 1
#define LIFT_DOWN 0

//set to disable to disable initialization of lift task
//Lift will NOT run if set false
const bool Lift_Task_Enable = true;


//Lift Class - used to control the front lift on the robot
class Lift{
    public:

        //initialization of the lift
        Lift(int maximumVeloity, float kP, float kD);

        //manual control
        int manual(int velocity, bool enabled);

        //manual control of lift (meant for use with controllers)
        int manual(int velocity);

        //change pid constraints
        void PID(int maxVel, float kP, float kD);

        int maxVel; //maxuimum velocity of lift motors

        float liftKp; //kP of Lift

        float liftKd; //kD of Lift

        //allows PD controller to be temporary disabled in order for manual adjustment of the Lift
        bool lift_manual_exemption;

        //current lift state
        int lift_state;

        //stores the last state the lift was set to
        int lift_state_prev;

        int targetValue;

        //simple preset
        int up();
        //simple preset
        int down();

        //move the lift to a preset
        int preset(int state);

        //move the lift to a custom preset
        int targ(int targetValue);
};

//lift class
extern Lift lift;

//liftTask
void Lift_Task_fn(void*param);

#endif