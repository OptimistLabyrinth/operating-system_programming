#ifndef ___ALARM_EXAMPLE__H___
#define ___ALARM_EXAMPLE__H___

#include <string>
#include <vector>

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>

#include "print_functions.h"

#define TIMEOUT         5
#define MAXTRIES        5
#define LINESIZE        100
#define CTRL_G          '\007'

volatile bool timed_out;
char myline[LINESIZE];
void sig_catch(int);

#endif /* ___ALARM_EXAMPLE__H___ */