/* Ten Ton Library - adiPiston.hpp
*   ttl Piston
*/
#ifndef _PISTON_HPP_
#define _PISTON_HPP_


#include "api.h"
namespace ttl{
    /* ADI Piston Class:
    a simpler way to interface with VEX pneumatics.
*/
class ADIPiston : private pros::ADIPort {
    public:
    /** 
     * Initializes an ADIPiston device on a given port
    * \param adi_port
    *    The ADI port the device is on (from 1-8, 'a'-'h', 'A'-'H')
    * \param init_state
    *   What the piston should be doing when the robot first turns on;
    *   LOW (0) is the default value, change to HIGH (1) if the piston starts in the wrong state
    */
        explicit ADIPiston(std::uint8_t adi_port, bool init_state = LOW);

    /* The Variable that holds the current state of the Pneumatic Device
    * \param state
    *    The Current State
    */
        bool state;

    /**
    *  Sets the Pneumatic Device to a given state
    * \param new_state
    *    The State to set the Pneumatic device to (LOW / 0 - HIGH / 1)
    * \return The New State (LOW / 0 / false - HIGH / 1 / true)
    */
        std::int32_t set_state(std::int32_t new_state);

    /**
    *  Get the Current state of a Pneumatic device acording to the state varable
    * \return retuns the current state (LOW / 0 / false - HIGH / 1 / true)
    */
        std::int32_t get_state() const;

    /**
    *  Toggles the Pneumatic Device:  
    *   This function changes the Pneumatic state to the opposite of what it was prior to calling 
    *   this function.   This is primarily useful in operator control for something like a claw.
    * \return The Current/New State (LOW / 0 / false - HIGH / 1 / true)
    */
        std::int32_t toggle();
    
    protected:
        std::uint8_t adi__port;
};
}
#endif