/*
 * MPUsem.h
 *
 *  Created on: 15 Nov 2019
 *      Author: jameswong
 */
#include <ti/drivers/I2C.h>
#include <pthread.h>
#include <semaphore.h>
#ifndef MPUSEM_H_
#define MPUSEM_H_


extern sem_t semMPU;      //Create semaphore thread for MPU
extern bool mpuState_2;     //Boolean to determine the on/off state of the second MPU
extern char mpu_1[2];     //Global variable for reading taken in from Second MPU, to be able to be read from First MPU function


#endif /* MPUSEM_H_ */
