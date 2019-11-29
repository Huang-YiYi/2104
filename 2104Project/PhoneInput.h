/*
 * PhoneInput.h
 *
 *  Created on: 11 Nov 2019
 *      Author: jameswong
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#ifndef PHONEINPUT_H_
#define PHONEINPUT_H_

#ifdef __cplusplus
extern "C" {
#endif

extern bool mpuState_1;                   //Indication of First MPU on/off state
extern int degree;                      //degree to take in user input
extern sem_t semMPU_1;                  //Create semaphore for First MPU
extern pthread_t mpu_handler;           //First MPU handler
extern pthread_t mpu_handler2;          //Second MPU handler
extern void *mpuThread(void *arg0);     //First MPU main function prototype
extern void *mpuThread2(void *arg0);    //Second MPU main function prototype


#ifdef __cplusplus
}
#endif
#endif /* PHONEINPUT_H_ */
