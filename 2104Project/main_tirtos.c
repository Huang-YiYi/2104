/*
 * Copyright (c) 2016-2019, Texas Instruments Incorporated
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
 *  ======== main_tirtos.c ========
 */
#include <stdint.h>
#include "msp.h"
/* POSIX Header files */
#include <pthread.h>
//#include <SITStraight.h>
//#include "UART.h"


/* RTOS header files */
#include <ti/sysbios/BIOS.h>

/* Driver configuration */
#include <ti/drivers/Board.h>
#include "uart.h"
#include "PhoneInput.h"
#include "motor.h"
#include "timer.h"



/* Stack size in bytes */
#define THREADSTACKSIZE    1024

/*
 *  ======== main ========
 */


int main(void)
     {
//    pthread_t           thread;
    pthread_attr_t      attrs;
    struct sched_param  priParam;
    int                 retc;
    int                 detachState;
    /* Call driver init functions */
    Board_init();

//    /* Initialize the attributes structure with default values */
    pthread_attr_init(&attrs);
//    /* Set priority, detach state, and stack size attributes */
    detachState = PTHREAD_CREATE_DETACHED;
    retc = pthread_attr_setdetachstate(&attrs, detachState);
    if (retc != 0)
    {
        /* pthread_attr_setdetachstate() failed */
        while (1)
            ;
    }
    pthread_attr_setschedparam(&attrs, &priParam);

    retc |= pthread_attr_setstacksize(&attrs, THREADSTACKSIZE);
    if (retc != 0)
    {
        /* pthread_attr_setstacksize() failed */
        while (1)
            ;
    }

    // Priority level: 4 being the highest -> 1 Being the lowest



    /* Create Uart Thread with priority = 2 */
    priParam.sched_priority = 2; //Bang muc uu tien cua GPIO thread, neeus khgac phai su dung mutex vi cung dieu khin trang thai led
    pthread_attr_setschedparam(&attrs, &priParam);
    retc = pthread_create(&uartthread_handler, &attrs, uartThread, NULL);
    if (retc != 0)
    {
        /* pthread_create() failed */
        while (1)
            ;
    }
//
//    /* Create Motor Thread with priority = 1 */
    priParam.sched_priority =1;
    pthread_attr_setschedparam(&attrs, &priParam);
    retc = pthread_create(&motor_handler, &attrs, motorThread, NULL);
    if (retc != 0)
    {
        /* pthread_create() failed */
        while (1)
            ;
    }
    /* Create Second MPU with with priority = 3 */
    priParam.sched_priority = 3;
    pthread_attr_setschedparam(&attrs, &priParam);
    retc = pthread_attr_setdetachstate(&attrs, detachState);
    retc = pthread_create(&mpu_handler2, &attrs, mpuThread2, NULL);
    if (retc != 0)
    {
        /* pthread_create() failed */
        while (1)
            ;
    }

    /* Create First MPU with with priority = 4 */
    priParam.sched_priority = 4;
        pthread_attr_setschedparam(&attrs, &priParam);
        retc = pthread_attr_setdetachstate(&attrs, detachState);
        retc = pthread_create(&mpu_handler, &attrs, mpuThread, NULL);
        if (retc != 0)
        {
            /* pthread_create() failed */
            while (1)
                ;
        }


    //Initialize of the all the threads
    BIOS_start();


    return (0);
}

