/*******************************************************************************
 * FILE:                buffer.h
 * Title:               Header file for multi-process Producer-Consumer 
 *                      Implementation in C
 * Date:                October 13, 2018
 * Author:              yks93
 * Email:               keesung0705@gmail.com
 * Assignment:          Operating Systems - Assignment #01
 * Due Date:            ~
 * 
 * Struct List:         shared_buffer_struct
 * 
 * Function List:       --
********************************************************************************/

#ifndef __BUFFER_7b69c43f_a728_4d61_aa64_5bf437d65420_H__
#define __BUFFER_7b69c43f_a728_4d61_aa64_5bf437d65420_H__

/* Including header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

/*******************************************************************************
 * Name of Stuct:       shared_buffer_struct
 * Purpose:             struct to be used by user to locate inside 
 *                      POSIX Shared Memory area
 * Used By:             produce_consumer_shared_memory.c
 * Member Variables:    1. in                   (type: int)
 *                          index where the producer process use to enqueue
 *                          new data into buffer[]
 *                      2. out                  (type: int)
 *                          index where the consumer process use to dequeue
 *                          first data from buffer[]
 *                      3. buffer[]             (type: int[])
 *                          circular queue in which the data are stored
 * 
 *                      << Semaphore >>
 *                      P(S) or wait(S):
 *                          S = S - 1
 *                          If S < 0 Then:
 *                              block the calling process
 *                              add it to the wait queue of this semaphore
 * 
 *                      V(S) or signal(S):
 *                          S = S + 1
 *                          If S <= 0 Then:
 *                              removev the first process from the wait queue
 *                              add it to the scheduling queue
 * 
 *                      4. buffer_has_space     (type: sem_t)
 *                          semaphore condition variable
 *                          used to control the behavior of the producer process
 *                          initial value 100
 *                          it indicates how many more items the producer
 *                          can put into buffer
 *                      5. buffer_has_data      (type: sem_t)
 *                          semaphore condition variable
 *                          used to control the behavior of the consumer process
 *                          initial value 0
 *                          it indicates how many more items the consumer
 *                          can retrieve from buffer and use it
 ******************************************************************************/
typedef struct shared_buffer_struct
{
    int in, out;
    int buffer[100];
    sem_t buffer_has_space, buffer_has_data;


} shared_buffer_struct;

/* function prototypes */

#endif /* __BUFFER_7b69c43f_a728_4d61_aa64_5bf437d65420_H__ */


