#ifndef _INTAKE_H_
#define _INTAKE_H_

//usecase
extern int intakeStatus;
//Presets
#define INTAKE_FOLDED 0
#define INTAKE_CLOSED 1
#define INTAKE_OPEN 2

// intake function
void intake_fn(void*param);

#endif
