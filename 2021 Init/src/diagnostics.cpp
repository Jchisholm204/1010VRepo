/*  Dignosics.cpp
    1010V - 2021 Init
    Jchisholm
    Diagnostics.cpp:
A set of diagnostics utilities that can be called to debug
various onboard systems within the robot and code..
Meant to be used in combination with PY debug
*/

#include "main.h"
#include "ports.h"
#include "ext.h"
#include "autons.h"
#include "display.h"
#include "drive.h"
#include <string>
#include <iostream>

void Diagnostics::report(auto error, auto subsystem, auto print){
    printf("ERROR:", error, "\t SUBSYSTEM:", subsystem, "\t INFO", print);
};

void Diagnostics::fatal(auto error, auto subsystem){
    printf("FATAL ERROR: \n", error, "\n", subsystem);
    printf("STOPPING DOCKER TASK");
    //suspend docker task
    Docker_Task.suspend();
};