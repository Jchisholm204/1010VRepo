#include "main.h"
#include "helpers.h"
#include "drive.h"
#include "dock.h"
#include "lift.h"

int IntakeStateStorage;

void intake(int velocity, bool desync){
    conveyerMotor.move_velocity(velocity);
    intakeMotor.move_velocity(velocity*(1-desync));
}

void Dock(int state){
    dock_state = state;
}

void Lift(int Liftstate){
    lift_state = Liftstate;
}

int home_tare(pros::Motor motor, pros::ADIDigitalIn limit_switch, int homeSpeed){
    bool homing_complete = false;
    motor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    while(homing_complete == false){
        if(limit_switch.get_value() == 1){
            motor.move_velocity(0);
            motor.tare_position();
            homing_complete = true;
        }
        else{
            motor.move_velocity(homeSpeed);
        }
    }
    return motor.get_position();
}