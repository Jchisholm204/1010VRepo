#include "main.h"
#include "autons.h"
#include "drive.h"
#include "lift.h"
#include "dock.h"
#include "helpers.h"

void skillsAuto(void){

}


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
        
    }


}