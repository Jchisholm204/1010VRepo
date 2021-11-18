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

int VelocityCalc(pros::Motor motor, int percent_actual){
    //get actual velocity of the motor
    float actualVel = motor.get_actual_velocity();
    //get target velocity of the motor
    int targetVel = motor.get_target_velocity();
    //calculate % of actual velocity + fill remaining with actual target
    float returnVel = (actualVel * percent_actual) + (targetVel * (1-percent_actual));
    return returnVel;
}

void mainDrive(void){
	bool intakeDeSync = false;
	bool conveyerDeSync = false;

	drivef.operator_Chassis();

	if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){
		Dock(UP);
	}
	else if (master.get_digital(E_CONTROLLER_DIGITAL_L2)){
		Dock(DOWN);
	}

	if(master.get_digital(E_CONTROLLER_DIGITAL_UP)){
		intakeDeSync = true;
	}
	else{
		intakeDeSync = false;
	}

	if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
		conveyerDeSync = true;
	}
	else{
		conveyerDeSync = false;
	}

	if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){
		intakeMotor.move_velocity(200*(1-intakeDeSync));
		conveyerMotor.move_velocity(200*(1-conveyerDeSync));
	}
	else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){
		intakeMotor.move_velocity(-200*(1-intakeDeSync));
		conveyerMotor.move_velocity(-200*(1-conveyerDeSync));
	}
	else{
		intakeMotor.move_velocity(0);
		conveyerMotor.move_velocity(0);
	};

	if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
		Lift(DOWN);
	}
	else if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)){
		Lift(UP);
	}
}