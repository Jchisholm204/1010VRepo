#ifndef _EXR_H_
#define _EXR_H_

/*  returns:
        0 if a ball is in the intake
        0.75 if a ball might be in the intake
        1 if the intake is empty
*/
int ballCheck(void);

//cycles the tower for a given number of balls, with adjustable roller and fw speed
void cycle(int balls);


#endif
