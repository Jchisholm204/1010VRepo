/* Ingenuity - ReRun.cpp
/* - main.h
/* - autons.h
* ReRun File - Contains all operations nessasary to ReRun
*/

#include "main.h"
#include "robot/display.h"
#include "robot/drive.hpp"
#include "ttl/ttl.hpp"
#include "robot/lift.hpp"

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
            runFile = fopen("/usd/right.rr", "r");
            break;

        case 2:
            //left auto
            runFile = fopen("/usd/left.rr", "r");
            break;

        case 4:
            //rerun skills auto
            runFile = fopen("/usd/skills.rr", "r");
            break;

        case 5:
            runFile = fopen("/usd/testAuto.rr", "r");
            break;

        default:
            return 1;
            break;
    }

    static int dr/*drive right*/, dl/*Drive Left*/, cnvm/*conveyer motor*/;
    static int ls/*lift state*/, ltg/*lift targetvalue*/;
    static bool lso/*lift state override*/;
    static bool dps/*dock pneumatic state*/, lps/*lift pneumatic state*/, sps/*side pneumatic state*/;

    while(feof(runFile) == false){

        fscanf(runFile, "%d %d %d %d %d %d %d %d %d", &dr, &dl, &cnvm, &ls, &ltg, &lso, &dps, &lps, &sps); //read the file and store the values as variables

        driveRB.move_velocity(dr);
        driveRM.move_velocity(dr);
        driveRF.move_velocity(dr);
        driveLB.move_velocity(dl);
        driveLM.move_velocity(dl);
        driveLF.move_velocity(dl);

        conveyerMotor.move_velocity(cnvm);

        if (lso == true){
            lift.targetValue = ltg;
        }
        else{
            lift.lift_state = ls;
        }

        DockPiston.set_state(dps);
        LiftPiston.set_state(lps);
        SidePiston.set_state(sps);

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
            recFile = fopen("/usd/right.rr", "w");
            break;

        case 2:
            //left auto
            recFile = fopen("/usd/left.rr", "w");
            break;

        case 4:
            //rerun skills auto
            recFile = fopen("/usd/skills.rr", "w");
            break;

        case 5:
            recFile = fopen("/usd/testAuto.rr", "w");
            break;

        default:
            return 1;
            break;
    }


    while(timer < allottedTime && endEarly == false){

        operatorControl();

    	fprintf(recFile, "%d\n", VelocityCalc(driveRM, 0.95));
        //printf("first line printed");
		fprintf(recFile, "%d\n", VelocityCalc(driveLM, 0.95));

		fprintf(recFile, "%d\n", VelocityCalc(conveyerMotor, 0));

        //Record Lift pid
		fprintf(recFile, "%d\n", lift.lift_state); //records lift state
        fprintf(recFile, "%d\n", lift.targetValue); //records lift state
        fprintf(recFile, "%d\n", lift.lift_manual_exemption); //records lift state

        fprintf(recFile, "%d\n", DockPiston.get_state()); //records lift state
        fprintf(recFile, "%d\n", DockPiston.get_state()); //records lift state
        fprintf(recFile, "%d\n", SidePiston.get_state()); //records lift state

        timer += rec_loop_delay;
        pros::delay(rec_loop_delay);

        //EndEarly Function - allows auto to be cut short of the allotted time
        if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
            endEarly = true;
        }
        //Ends while loop and immediately closes file

    }

    fprintf(recFile, "0\n0\n0\n");
    fclose(recFile);

    return 0;
}