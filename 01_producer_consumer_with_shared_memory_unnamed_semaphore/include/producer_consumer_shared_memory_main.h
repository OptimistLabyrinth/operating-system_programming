/*******************************************************************************
 * FILE:                producer_consumer_shared_memory_main.h
 * Title:               Header file for .c file which contains main function
 *                      of this assignment
 * Date:                October 13, 2018
 * Revised:             October 16, 2018
 * Author:              yks93
 * Email:               keesung0705@gmail.com
 * Assignment:          Operating Systems - Assignment #01
 * Due Date:            ~
 * 
 * Struct List:         --
 * Function List:       initiate_variables
 * 
********************************************************************************/

#ifndef __PRODUCER_CONSUMER_SHARED_MEMORY_f5c3433e_7e85_4bf5_a3ec_ec6f5a5027f1_H__
#define __PRODUCER_CONSUMER_SHARED_MEMORY_f5c3433e_7e85_4bf5_a3ec_ec6f5a5027f1_H__

/* include header files */
#include "buffer.h"
#include "producer_semaphore.h"
#include "consumer_semaphore.h"
#include "print_functions.h"

#define LOOP_COUNT 1000

/* function prototypes */
void initiate_variables(void*);

#endif /* __PRODUCER_CONSUMER_SHARED_MEMORY_f5c3433e_7e85_4bf5_a3ec_ec6f5a5027f1_H__ */
