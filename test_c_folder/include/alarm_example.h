#ifndef ___ALARM_EXAMPLE__57e83496_2669_4f1a_b9dc_0bd1721ee147__H___
#define ___ALARM_EXAMPLE__57e83496_2669_4f1a_b9dc_0bd1721ee147__H___

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define TIMEOUT         5
#define MAXTRIES        5
#define LINESIZE        100
#define TRUE            1
#define FALSE           0

// global variable
volatile int timed_out;
char myline[LINESIZE];

// function prototypes
const char* quickreply(const char*);
void sig_catch(int);

#endif /* ___ALARM_EXAMPLE__57e83496_2669_4f1a_b9dc_0bd1721ee147__H___ */