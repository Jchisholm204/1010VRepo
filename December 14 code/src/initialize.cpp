#include "main.h"
#include "tray.h"
#include "diagnostics.h"
#include "intakes.h"

Controller master(E_CONTROLLER_MASTER);
Controller partner(E_CONTROLLER_PARTNER);

Motor driveLF(12, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor driveLB(14, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

Motor driveRF(11, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveRB(15, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

Motor lifty(18, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);  //18
Motor stacky(13, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);

Motor leftSuck(17, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_ROTATIONS);
Motor rightSuck(16, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_ROTATIONS);

bool outTake;
Tray cubeTray;
Chassis driveF;
RobotLift arm;
Intake intake;

//hey
void initialize() {
	//auto liftpid = okapi::AsyncControllerFactory::posIntegrated(4);
	stacky.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	lifty.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	rightSuck.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	leftSuck.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveLF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveLB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	pros::lcd::initialize();

	//pros::motor_pid_s_t pid = pros::Motor::convert_pid(KF, KP, KI, KD);
	//intakeTilt.set_pos_pid(pid);

	ADIDigitalIn boistop('a');
	ADIDigitalIn downis('b');
	ADIUltrasonic rightUltra ('h', 'g');
	ADIUltrasonic leftUltra ('f', 'e');
	ADIGyro gyro ('d');
	pros::Task diagnostics_tsk(
		 diagnostics_fn,
		 (void*)"PROS", //PROS Constant Value
		 TASK_PRIORITY_DEFAULT, //Default Priority
		 TASK_STACK_DEPTH_DEFAULT, //Default Depth (data it stores)
		 "Diagnostics_tsk" //Task Name
);
/*
	pros::Task Stack_Task(
		 STACK_Task_fn, //defined in lift.h and lift.cpp
		 (void*)"PROS", //PROS Constant Value
		 TASK_PRIORITY_DEFAULT, //Default Priority
		 TASK_STACK_DEPTH_DEFAULT, //Default Depth (data it stores)
		 "stackTask" //Task Name
);

pros::Task Stack_Zero_task(
	 zero_ft, //defined in lift.h and lift.cpp
	 (void*)"PROS", //PROS Constant Value
	 TASK_PRIORITY_DEFAULT, //Default Priority
	 TASK_STACK_DEPTH_DEFAULT, //Default Depth (data it stores)
	 "stackTask" //Task Name
);
*/
}
/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
}

void competition_initialize() {
}
