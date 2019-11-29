/*
 * uart.h
 *
 *  Created on: 8 Nov 2019
 *      Author: jameswong
 */

#include <pthread.h>
#include <ti/drivers/UART.h>
#include <semaphore.h>
#ifndef UART_H_
#define UART_H_


#ifdef __cplusplus
extern "C" {
#endif

extern pthread_t uartthread_handler;    // Create UART thread handler
extern void *uartThread(void *arg0);    // Create UART main function prototype
extern sem_t semRepUpdate;              // Turn on/off LED to indicate device on/off
extern UART_Handle uart;                // Create UART handle


#endif /* UART_H_ */
