/* Ingenuity - pneumatics.hpp
* Custom Library to interface with PROS Pistons
*/
#ifndef _PNEUMATICS_HPP
#define _PNEUMATICS_HPP

#include "main.h"

class Piston {
    public:
        bool pistonState;

        Piston(pros::ADIDigitalOut stabby, bool startState); //create a piston object on a given port
        
        bool set_state(bool newState);
        bool get_state(void);
        bool toggle(void);
};

#endif