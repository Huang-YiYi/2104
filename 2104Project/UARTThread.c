/*
 * Copyright (c) 2015-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== uartecho.c ========
 */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/PWM.h>

//#include <ti/drivers/I2C.h>
/* Driver configuration */
#include "ti_drivers_config.h"
#include <semaphore.h>
#include "msp.h"
#include <pthread.h>
#include "PhoneInput.h"
int  i;
volatile int bytesReceived = 1;
/*
 *  ======== mainThread ========
 */
pthread_t uartthread_handler;
sem_t semRepUpdate;
UART_Handle uart;
const char ledOnState[]    = "Power On\n";
const char ledOffState[]   = "Power Off\n";

int charToint = 0;
char receiveByte[5];
#define THREADSTACKSIZE    1024
void *RepUpdateFxn(void *arg0)
{
    int rc;
    /* Initialize Semaphore */
    rc = sem_init(&semRepUpdate, 0, 0);
    if (rc == -1)
    {
        while (1)
            ;
    }
    while (1)
    {
//        printf("thread2 running\n");
        rc = sem_wait(&semRepUpdate);    // Wait on user input, depending of what they input 'b' or 't'
        if (rc == 0)
        {
            if (mpuState_1)  //if 'b' RED LED will turn on.
            {
//                printf("thread2.1 running\n");
                GPIO_write(CONFIG_GPIO_RED_LEFT, CONFIG_GPIO_LED_ON);
                delayM(10);
            }
            else            //else RED LED will turn off.
            {
//                printf("thread2.2 running\n");
                GPIO_write(CONFIG_GPIO_RED_LEFT, CONFIG_GPIO_LED_OFF);
                delayM(10);

            }
        }
    }
}
void *SetUpdateFxn(void *arg0)
{
    int rc;
    while (1)
    {
            char new_degree[2];            UART_read(uart, &receiveByte, sizeof(receiveByte));//input = RXD byte
            delayM(100);
            switch (receiveByte[0])
            {
            case 'b':
                UART_write(uart, "\n", 1);
                UART_write(uart, &ledOnState, 9);
                mpuState_1 = 1; //Note here if it does not provide a favorable view of the button and will have to use mutex
                /* Post to semaphore that rate change occurred. */
                receiveByte[0] = receiveByte[1];     /* Maniplulate the receiveByte array*/
                receiveByte[1] = receiveByte[2];
                receiveByte[2] = '\0';
                charToint = atoi(receiveByte);       // Convert int to char

                degree = charToint;                  //Take in user degree input
                rc = sem_post(&semMPU_1);
                if (rc == -1)
                {
        //                printf("thread1.1 running\n");
                    while (1)
                        ;
                }
                rc = sem_post(&semRepUpdate);
                if (rc == -1)
                {
        //                printf("thread1.2 running\n");
                    while (1)
                        ;
                }
                break;
            case 't':
                //Lenh bat den
                UART_write(uart, "\n", 1);
                UART_write(uart, &ledOffState, 10);
                mpuState_1 = 0; //chu y o day neu ko cung muc do uu tien ngat cua nut bam va den thi can phai dung mutex
                /* Post to semaphore that rate change occurred. */
                rc = sem_post(&semMPU_1);
                if (rc == -1)
                {
                    while (1)
                        ;
                }
                rc = sem_post(&semRepUpdate);
                if (rc == -1)
                {
                    while (1)
                        ;
                }
                break;
            default:
                UART_write(uart, &receiveByte, sizeof(receiveByte));
                break;

        }
    }
}
void *uartThread(void *arg0)
{
    char input[10];
//    const char  echoPrompt[] = "Echoing characters:\r\n";
    pthread_t RepUpdateFxn_Handle, SetUpdateFxn_Handle;
    pthread_attr_t attrs;
    struct sched_param priParam;
    int detachState;
    int rc;
    UART_Params uartParams;

    /* Call driver init functions */
    GPIO_init();
    UART_init();

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 9600;

    uart = UART_open(CONFIG_UART_0, &uartParams);

    if (uart == NULL) {
        /* UART_open() failed */
        while (1);
    }
    pthread_attr_init(&attrs);
    detachState = PTHREAD_CREATE_DETACHED;
    priParam.sched_priority = 2; //Cung voi muc do uu tien cua thread chinhs
    pthread_attr_setschedparam(&attrs, &priParam);
    rc = pthread_attr_setdetachstate(&attrs, detachState);
    if (rc != 0)
    {
        /* pthread_attr_setdetachstate() failed */
        while (1)
            ;
    }

    rc |= pthread_attr_setstacksize(&attrs, THREADSTACKSIZE);
    if (rc != 0)
    {
        /* pthread_attr_setstacksize() failed */
        while (1)
            ;
    }
    rc = pthread_create(&RepUpdateFxn_Handle, &attrs, RepUpdateFxn, NULL);
    if (rc != 0)
    {
        /* pthread_create() failed */
        while (1)
            ;
    }
    /* Create SetUpdateFxn thread */
    rc = pthread_create(&SetUpdateFxn_Handle, &attrs, SetUpdateFxn, NULL);
    if (rc != 0)
    {
        /* pthread_create() failed */
        while (1)
            ;
    }
    return (NULL);
}
void delayM(int n) {
    int i, j;
    for (j = 0; j < n; j++)
        for (i = 750; i > 0; i--);      /* Delay */
}
