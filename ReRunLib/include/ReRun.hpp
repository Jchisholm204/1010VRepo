#ifndef _AUTOS_HPP_
#define _AUTOS_HPP_
#include "api.h"

namespace ttl{

    class ReRun{

        public:
        
            void imu();

            // Playback of ReRun Autos
            int playback(const char *filename);

            // Full OpControl for Recording of ReRun Autos
            int record(const char *filename, int allotedTime);

        protected:
            pros::Motor m1(1);
           /* pros::Motor m2;
            pros::Motor m3;
            pros::Motor m4;
            pros::Motor m5;
            pros::Motor m6;
            pros::Motor m7;
            pros::Motor m8;
            pros::ADIDigitalOut p1;
            pros::ADIDigitalOut p2;
            pros::ADIDigitalOut p3;
            int pid_State_A;
            int pid_State_B;
            int pid_State_C;*/
    };

    //ReRun Motor Velocity Calculator - returns float
    //(motor, percent_actual) // percent_actual = 0.5 default
    //0.4 percent_actual = 40% actual + 60% target (velocities)
    // 0 percent_actual = use target velocity only
    int VelocityCalc(pros::Motor motor, float percent_actual = 0.5);

}

#endif