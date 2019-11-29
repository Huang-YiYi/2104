/*
 * timer.h
 *
 *  Created on: 8 Nov 2019
 *      Author: jameswong
 */
#include <pthread.h>
#include <ti/drivers/Timer.h>
#ifndef TIMER_H_
#define TIMER_H_




#ifdef __cplusplus
extern "C" {
#endif
extern pthread_t timerthread_handler;
extern void *timerThread(void *arg0);
extern void blinkTimer_Callback(Timer_Handle myHandle);

extern Timer_Handle blinkTimer;
extern Timer_Params timer_params;
extern sem_t semEnableTimer;


#endif /* TIMER_H_ */
