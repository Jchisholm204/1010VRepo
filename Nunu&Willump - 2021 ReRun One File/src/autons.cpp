/*  AUTONS.cpp
* Used for everything to do with autos:
*   Regular Skills Auto
*   ReRun Autos Playback
*   ReRun Auto Recording
*/

#include "main.h"
#include "autons.h"
#include "drive.h"
#include "lift.h"
#include "dock.h"
#include "helpers.h"

void skillsAuto(void){
    drivef.timeDrive(1000, -200, 200);
}

int rec_loop_delay = 20; // ReRun loop delay in [ms]

//Takes full control of auto - NO OTHER INPUT ALLOWED WHILE RERUN RUNNING
int reRunAuto(int reRunFile){
    FILE * runFile;
    switch(reRunFile){
        case 0:
            //No auto
            pros::delay(500);
            return EXIT_CODE_0;
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
            return EXIT_CODE_ERROR;
            break;
    }//endswitch

    static float drb/*drive right back*/, drf, dlb, dlf, intm/*intake Motor*/, cnvm/*conveyer motor*/;
    static int lms/*lift motor state*/, dks/*dock motor state*/, lps/*lift pnumatic state*/;

    while(feof(runFile) == false){
        fscanf(runFile, "%f %f %f %f %f %f %d %d", &drb, &drf, &dlb, &dlf, &intm, &cnvm, &lms, &dks);
        driveRB.move_velocity(drb);
        driveRF.move_velocity(drf);
        driveLB.move_velocity(dlb);
        driveLF.move_velocity(dlf);

        intakeMotor.move_velocity(intm);
        conveyerMotor.move_velocity(cnvm);

        if ( lift_state != lms ){
            lift_state = lms;
        }
        if ( dock_state != dks ){
            dock_state = dks;
        }
        pros::delay(rec_loop_delay);
        //same as opcontrol
    }
    return EXIT_CODE_SUCCESS;
}

int recordAuto(int reRunFile, bool recording_disabled, int allottedTime){
    int startTime = pros::millis();
    int timer = 0;
    bool endEarly  = false;

    if(recording_disabled == true){
        return EXIT_CODE_ERROR;
    }
    //printf("starting recording\n");


    FILE * recFile;

    switch(reRunFile){
        case 1:
            //right auto
            recFile = fopen("/usd/right.txt", "w");
            //printf("rightAutoSelected");
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
            //printf("testAuto Selected\n");
            break;

        default:
            return EXIT_CODE_ERROR;
            break;
    }//endswitch


    while(timer < allottedTime && endEarly == false){
        //printf("while loop engaged\n");

        mainDrive();

    	fprintf(recFile, "%f\n", VelocityCalc(driveRB, 0.8));
        //printf("first line printed\n");
		fprintf(recFile, "%f\n", VelocityCalc(driveRF, 0.8));
		fprintf(recFile, "%f\n", VelocityCalc(driveLB, 0.8));
		fprintf(recFile, "%f\n", VelocityCalc(driveLF, 0.8));

		fprintf(recFile, "%d\n", VelocityCalc(intakeMotor, 0));
		fprintf(recFile, "%d\n", VelocityCalc(conveyerMotor, 0));

		fprintf(recFile, "%d\n", lift_state);
		fprintf(recFile, "%d\n", dock_state);

        timer += rec_loop_delay;
        pros::delay(rec_loop_delay);

        //EndEarly Function - allows auto to be cut short of the allotted time
        if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
            endEarly = true;
        }
        //Ends while loop and immediately closes file

    }
    //printf("closing file now\n");
    fprintf(recFile, "0\n0\n0\n0\n0\n0\n0\n0");
    fclose(recFile);
    //printf("about to exit function\n");
    return EXIT_CODE_SUCCESS;
}