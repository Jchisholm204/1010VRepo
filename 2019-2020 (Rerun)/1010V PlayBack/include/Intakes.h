#ifndef _INTAKES_H_
#define _INTAKES_H_
////////////Intake State
#define MoveIntake 0
#define MoveOuttake 1
#define MoveTower 2
#define MoveStop 3
#define MoveSlowOut 4
#define MoveSlowIn 5
class intakeClass;
class intakeClass{
public:
    void opintake(void);
    void suck(int velocity);
    void swap(int intakeState);
};
#endif
