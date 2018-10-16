/*******************************************************************************
 * FILE:                producer_semaphore.c
 * Title:               Source file which implements the behaviors of producer
 * Date:                October 13, 2018
 * Revised:             October 16, 2018
 * Author:              yks93
 * Email:               keesung0705@gmail.com
 * Assignment:          Operating Systems - Assignment #01
 * Due Date:            ~
 *
 * Function List:       produce_data
 * 
********************************************************************************/

/* Include header files */
#include "../include/producer_semaphore.h"

/*******************************************************************************
 * Name of Function:    produce_data
 * Purpose:             produce and enqueue new data into the buffer at the
 *                      shared memory
 * Parameters:          (void*)
 * Return Value:        --
 * Calls to:            sem_wait, sem_post, printf
 * Called from:         main    (file: producer_consumer_shared_memory_main.c)
 * 
 * Method:              inside for Loop
 *                          1. decrease the semaphore variable 'buffer_has_space'
 *                              using sem_wait() function
 *                          2. enqueue new data into the buffer
 *                          3. move 'in' one step forward
 *                          4. check whether producer cycled through the
 *                              whole buffer
 *                          5. increase the semaphore variable 'buffer_has_data'
 *                              using sem_post() function
 *                              so that consumer can work
 ******************************************************************************/
void produce_data(void* ptr)
{
    shared_buffer_struct* stptr = (shared_buffer_struct*) ptr;

    int i;
    for (i=0; i < LOOP_COUNT; ++i) {
        sem_wait(&(stptr->buffer_has_space));
        stptr->buffer[stptr->in] = i;
        printf("inside parent: %3d\n", stptr->buffer[stptr->in]);
        ++(stptr->in);
        stptr->in %= 100;
        sem_post(&(stptr->buffer_has_data));
    }
}
