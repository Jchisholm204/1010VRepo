/* Ingenuity - piston.hpp
*   jlib piston
*/
#ifndef _PISTON_HPP_
#define _PISTON_HPP_


#include "api.h"


class ADIPiston : private pros::ADIPort {
    public:
        explicit ADIPiston(std::uint8_t adi_port, bool init_state = LOW);

        bool state;

        std::int32_t set_state(std::int32_t new_state);
        std::int32_t get_state() const;
    
    protected:
        std::uint8_t adi__port;
};

#endif