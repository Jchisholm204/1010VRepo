/* Ingenuity - ReRun.cpp
/* - main.h
/* - autons.h
* ReRun File - Contains all operations nessasary to ReRun
*/

#include "main.h"
#include "robot/display.h"
#include "robot/drive.hpp"
#include "tasking/pneumatics.hpp"
#include "tasking/lift.hpp"

//Velocity Calculator Function
int VelocityCalc(pros::Motor motor, float percent_actual){
    //get actual velocity of the motor
    int actualVel = motor.get_actual_velocity();
    //get target velocity of the motor
    int targetVel = motor.get_target_velocity();
    //calculate % of actual velocity + fill remaining with actual target
    float returnVel = (actualVel * percent_actual) + (targetVel * (1-percent_actual));
    return returnVel;
}

/*
ORDER OF RECORDING:
    -driveRB
    -driveRF
    -driveLB
    -driveLF
    -intake
    -conveyer
    -lift state
    -lift targetvalue
    -lift state override (also known as lift manual exemption)
    -dock piston state
    -lift piston state
    -side piston state

*/

int rec_loop_delay = 20; // ReRun loop delay in [ms]

//Takes full control of auto - NO OTHER INPUT ALLOWED WHILE RERUN RUNNING
int reRunAuto(int reRunFile){
    FILE * runFile;
    switch(reRunFile){
        case 0:
            //No auto
            pros::delay(500);
            return 1;
            break;

        case 1:
            //right auto
            runFile = fopen("/usd/right.txt", "r");
            break;

        case 2:
            //left auto
            runFile = fopen("/usd/left.txt", "r");
            break;

        case 4:
            //rerun skills auto
            runFile = fopen("/usd/skills.txt", "r");
            break;

        case 5:
            runFile = fopen("/usd/testAuto.txt", "r");
            break;

        default:
            return 1;
            break;
    }

    static int drb/*drive right back*/, drf, dlb, dlf, intm/*intake Motor*/, cnvm/*conveyer motor*/;
    static int ls/*lift state*/, ltg/*lift targetvalue*/;
    static bool lso/*lift state override*/;
    static bool dps/*dock pneumatic state*/, lps/*lift pneumatic state*/, sps/*side pneumatic state*/;

    while(feof(runFile) == false){

        fscanf(runFile, "%d %d %d %d %d %d %d %d %d %d %d %d", &drb, &drf, &dlb, &dlf, &intm, &cnvm, &ls, &ltg, &lso, &dps, &lps, &sps); //read the file and store the values as variables

        driveRB.move_velocity(drb);
        driveRF.move_velocity(drf);
        driveLB.move_velocity(dlb);
        driveLF.move_velocity(dlf);

        intakeMotor.move_velocity(intm);
        conveyerMotor.move_velocity(cnvm);

        if (lso == true){
            lift.targetValue = ltg;
        }
        else{
            lift.lift_state = ls;
        }

        Dock_Piston_State = dps;
        Lift_Piston_State = lps;
        Side_Piston_State = sps;

        pros::delay(rec_loop_delay);
    }
    return 0;
}

int recordAuto(int reRunFile, bool recording_disabled, int allottedTime){
    int startTime = pros::millis();
    int timer = 0;
    bool endEarly  = false;

    if(recording_disabled == true){
        return 1;
    }

    FILE * recFile;

    switch(reRunFile){
        case 1:
            //right auto
            recFile = fopen("/usd/right.txt", "w");
            break;

        case 2:
            //left auto
            recFile = fopen("/usd/left.txt", "w");
            break;

        case 4:
            //rerun skills auto
            recFile = fopen("/usd/skills.txt", "w");
            break;

        case 5:
            recFile = fopen("/usd/testAuto.txt", "w");
            break;

        default:
            return 1;
            break;
    }


    while(timer < allottedTime && endEarly == false){

        operatorControl();

    	fprintf(recFile, "%d\n", VelocityCalc(driveRB, 0.95));
        //printf("first line printed");
		fprintf(recFile, "%d\n", VelocityCalc(driveRF, 0.95));
		fprintf(recFile, "%d\n", VelocityCalc(driveLB, 0.95));
		fprintf(recFile, "%d\n", VelocityCalc(driveLF, 0.95));

		fprintf(recFile, "%d\n", VelocityCalc(intakeMotor, 0));
		fprintf(recFile, "%d\n", VelocityCalc(conveyerMotor, 0));

        //Record Lift pid
		fprintf(recFile, "%d\n", lift.lift_state); //records lift state
        fprintf(recFile, "%d\n", lift.targetValue); //records lift state
        fprintf(recFile, "%d\n", lift.lift_manual_exemption); //records lift state

        fprintf(recFile, "%d\n", Dock_Piston_State); //records lift state
        fprintf(recFile, "%d\n", Lift_Piston_State); //records lift state
        fprintf(recFile, "%d\n", Side_Piston_State); //records lift state

        timer += rec_loop_delay;
        pros::delay(rec_loop_delay);

        //EndEarly Function - allows auto to be cut short of the allotted time
        if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
            endEarly = true;
        }
        //Ends while loop and immediately closes file

    }

    fprintf(recFile, "0\n0\n0\n0\n0\n0\n0\n0");
    fclose(recFile);

    return 0;
}