/*******************************************************************************
 * FILE:                consumer_semaphore.h
 * Title:               Header file for .c file which implements the 
 *                      behaviors of consumers
 * Date:                October 13, 2018
 * Revised:             October 16, 2018
 * Author:              yks93
 * Email:               keesung0705@gmail.com
 * Assignment:          Operating Systems - Assignment #01
 * Due Date:            ~
 * 
 * Struct List:         --
 * Function List:       consume_data
 * 
********************************************************************************/

#ifndef __CONSUMER_SEMAPHORE_725010e0_90bd_4d8e_a278_6fd863b13e38_H__
#define __CONSUMER_SEMAPHORE_725010e0_90bd_4d8e_a278_6fd863b13e38_H__

#include "buffer.h"
#include "producer_consumer_shared_memory_main.h"

void consume_data(void*);

#endif /* __CONSUMER_SEMAPHORE_725010e0_90bd_4d8e_a278_6fd863b13e38_H__ */
