#ifndef ___POSIX_TIMER_EXAMPLE__4f2d423d_f4d4_4fdb_9b51_7223f3a3afc9__H___ 
#define ___POSIX_TIMER_EXAMPLE__4f2d423d_f4d4_4fdb_9b51_7223f3a3afc9__H___

#include <stdio.h>

#include <pthread.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

// function prototypes 
void before_main(void) __attribute__((constructor));
void after_main(void) __attribute__((destructor));

void start_clock(void);
void clock_handler(int, siginfo_t* info, void*);

#endif /* ___POSIX_TIMER_EXAMPLE__4f2d423d_f4d4_4fdb_9b51_7223f3a3afc9__H___ */