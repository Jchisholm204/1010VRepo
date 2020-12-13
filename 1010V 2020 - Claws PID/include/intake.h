#ifndef _INTAKE_H_
#define _INTAKE_H_

//usecase
extern int intakeStatus;
//Presets
#define INTAKE_HOLD 0
#define INTAKE_CLOSED 1
#define INTAKE_OPEN 2

#define intR 0
#define intL 1
#define intB 2

// intake functions
double zero_fn(int inr);
void intake_fn(void*param);

#endif
