#ifndef _INTAKE_H_
#define _INTAKE_H_

//usecase
extern int intakeStatus;

//Presets for intakeStatus
#define INTAKE_HOLD 0
#define INTAKE_CLOSED 1
#define INTAKE_OPEN 2

// Presets for reseting the intakes
#define intR 0
#define intL 1
#define intB 2

// intake reset function call
double zero_fn(int inr);

// Intake Task
void intake_fn(void*param);

#endif
