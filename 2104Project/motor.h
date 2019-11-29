/*
 * motor.h
 *
 *  Created on: 8 Nov 2019
 *      Author: jameswong
 */


#include <ti/drivers/I2C.h>
#include <ti/drivers/PWM.h>
#include <pthread.h>
#include <semaphore.h>

#ifndef MOTOR_H_
#define MOTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

extern pthread_t motor_handler;         // Create motor_handler pthread_t Prototype
extern void *motorThread(void *arg0);   // Create Vibration MotorThread main function
extern sem_t semVibrate;                // Create semephore thread
extern bool vibrationState;             // Boolean to indicate Vibration on/off
extern PWM_Handle pwm;                  // Create PWM_Handle for vibration Motor
extern PWM_Handle pwm_green;            // Create PWM_Handle for Green LED


#endif /* MOTOR_H_ */
