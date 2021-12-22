#include "jlib/piston.hpp"

ADIPiston::ADIPiston(std::uint8_t adi_port, bool init_state) : ADIPort(adi_port, pros::E_ADI_DIGITAL_OUT){
    state = init_state;
    adi__port = adi_port;
    pros::c::ext_adi_port_set_value(_smart_port, adi__port, state);
}

std::int32_t ADIPiston::set_state(std::int32_t new_state)  {
    state = new_state;
    pros::c::ext_adi_port_set_value(_smart_port, adi__port, state);
    return state;
}

std::int32_t ADIPiston::get_state() const{
    return state;
}

std::int32_t ADIPiston::toggle() {
    state = !state;
    pros::c::ext_adi_port_set_value(_smart_port, adi__port, state);
    return state;
};