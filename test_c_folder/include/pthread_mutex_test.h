#ifndef ___PTHREAD_MUTEX_TEST__31193982_6909_41f0_9655_e1f1fa776bc3__H___
#define ___PTHREAD_MUTEX_TEST__31193982_6909_41f0_9655_e1f1fa776bc3__H___

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include "print_functions.h"

#define NUM 8
#define LOOP 1000

const char* sentences[NUM] = {
    "7", 
    "Lorem ipsum dolor sit amet", 
    "consequences", 
    "111111", 
    "Edsger W. Dijkstra", 
    "S---A---B---C---D---E---F", 
    "F=Y(X)"
    "int main() { printf(\"hello world!\"); return 0; }"
};

struct arg_struct {
    int index;
    const char* string;
    pthread_mutex_t my_mutex;
    pthread_cond_t mutex_cond;
};

// function prototypes
void* funcXXX(void*);

#endif /* ___PTHREAD_MUTEX_TEST__31193982_6909_41f0_9655_e1f1fa776bc3__H___ */
