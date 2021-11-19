#ifndef _AUTONS_H_
#define _AUTONS_H_

extern void skillsAuto(void);

//exit codes
#define EXIT_CODE_SUCCESS 2
#define EXIT_CODE_ERROR 1
#define EXIT_CODE_0 0
#define EXIT_CODE_DONE 0

// Playback of ReRun Autos
int reRunAuto(int reRunFile);

// Full OpControl for Recording of ReRun Autos
int recordAuto(int reRunFile, bool recording_disabled, int allottedTime);

#endif