/*******************************************************************************
 * FILE:                producer_semaphore.h
 * Title:               Header file for .c file which implements the 
 *                      behaviors of producers
 * Date:                October 13, 2018
 * Revised:             October 16, 2018
 * Author:              yks93
 * Email:               keesung0705@gmail.com
 * Assignment:          Operating Systems - Assignment #01
 * Due Date:            ~
 * 
 * Struct List:         --
 * Function List:       produce_data
 * 
********************************************************************************/

#ifndef __PRODUCER_SEMAPHORE_95b1eb64_21ab_4c11_a89a_ac72706a815e_H__
#define __PRODUCER_SEMAPHORE_95b1eb64_21ab_4c11_a89a_ac72706a815e_H__

#include "buffer.h"
#include "producer_consumer_shared_memory_main.h"

void produce_data(void*);

#endif /* __PRODUCER_SEMAPHORE_95b1eb64_21ab_4c11_a89a_ac72706a815e_H__ */
