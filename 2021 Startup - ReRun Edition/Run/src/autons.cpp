#include "main.h"
#include "autons.h"
#include "drive.h"
#include "ext.h"

void runtime(void){

    FILE * runFile = fopen("/usd/right.txt", "r");

    static float drb, drf, dlb, dlf, intm, cnvm, ams, dks;

    while(true){
        if(feof(runFile)){
            driveRB.move_velocity(0);
            driveRF.move_velocity(0);
            driveLB.move_velocity(0);
            driveLF.move_velocity(0);

            intakeMotor.move_velocity(0);
            conveyerMotor.move_velocity(0);

        }

        fscanf(runFile, "%f %f %f %f %f %f %d %d", &drb, &drf, &dlb, &dlf, &intm, &cnvm, &ams, &dks);
        driveRB.move_velocity(drb);
        driveRF.move_velocity(drf);
        driveLB.move_velocity(dlb);
        driveLF.move_velocity(dlf);

        intakeMotor.move_velocity(intm);
        conveyerMotor.move_velocity(cnvm);

        if ( arm_state != ams ){
            arm_state = ams;
        }
        if ( dock_state != dks ){
            dock_state = dks;
        }
        pros::delay(20);
    }
}