#ifndef __POSIX_THREAD_TEST__H__
#define __POSIX_THREAD_TEST__H__

#include <string>
#include <vector>

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#include "print_functions.h"

#define LOOP_COUNT 10

void init_vars(void);

void destroy_vars(void);

void execution(void);

void* incr(void* args);

void* decr(void* args);

void pthread_test_main(void);

typedef struct Data {
    int index;
    sem_t* sptr;
} Data;

typedef struct mData {
    int index;
    pthread_mutex_t* mutex;
} mData;

#endif __POSIX_THREAD_TEST__H__
