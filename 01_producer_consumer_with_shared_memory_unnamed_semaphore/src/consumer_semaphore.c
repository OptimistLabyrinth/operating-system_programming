/*******************************************************************************
 * FILE:                consumer_semaphore.c
 * Title:               Source file which implements the behaviors of consumer
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
#include "../include/consumer_semaphore.h"

/*******************************************************************************
 * Name of Function:    consume_data
 * Purpose:             dequeue one data from the buffer at the shared memory
 *                      and consume it
 * Parameters:          (void*)
 * Return Value:        --
 * Calls to:            sem_wait, sem_post, printf
 * Called from:         main    (file: producer_consumer_shared_memory_main.c)
 * 
 * Method:              inside for Loop
 *                          1. decrease the semaphore variable 'buffer_has_data'
 *                              using sem_wait() function
 *                          2. dequeue the first data in the buffer
 *                          3. move 'out' one step forward
 *                          4. check whether consumer cycled through the
 *                              whole buffer
 *                          5. increase the semaphore variable 'buffer_has_space'
 *                              using sem_post() function
 *                              so that producer can work
 ******************************************************************************/
void consume_data(void* ptr)
{
    shared_buffer_struct* stptr = (shared_buffer_struct*) ptr;

    int i;
    for (i=0; i < LOOP_COUNT; ++i) {
        sem_wait(&(stptr->buffer_has_data));
        printf("\tchild: %3d\n", stptr->buffer[stptr->out]);         
        ++(stptr->out);
        stptr->out %= 100;
        sem_post(&(stptr->buffer_has_space));
    }
}
