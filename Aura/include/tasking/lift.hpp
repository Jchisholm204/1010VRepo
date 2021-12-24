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

        /**
         * Initialization of the Lift
         * 
         * \param maximumVelocity
         *      The maximum velocity the Lift can move in the PID
         * \param nkP
         *      The Lift's kP Value
         * \param nkD
         *      The Lift's kD Value
         * \param iState
         *      The initial PID state given to the controller at startup
         * \param wait
         *      Dont Move the Lift at startup
         *      
        */
        Lift(int maximumVeloity, float nkP, float nkD, int iState, bool wait);

        /**
         * Initialization of the Lift
         * 
         * \param maximumVelocity
         *      The maximum velocity the Lift can move in the PID
         * \param nkP
         *      The Lift's kP Value
         * \param nkD
         *      The Lift's kD Value
         *      
        */
        Lift(int maximumVeloity, float nkP, float nkD);

        //manual control
        void manual(int velocity, bool enabled);

        //manual control of lift (meant for use with controllers)
        void manual(int velocity);

        //change pid constraints
        void PID(int maxVel, float nkP, float nkD);

        int maxVel; //maxuimum velocity of lift motors

        float kP; //kP of Lift

        float kD; //kD of Lift

        //allows PD controller to be temporary disabled in order for manual adjustment of the Lift
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

        //move the lift to a preset
        void preset(int nstate);

        //move the lift to a custom preset
        void targ(int targetValue);
};

//lift class
extern Lift lift;

//liftTask
void Lift_Task_fn(void*param);

#endif