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
 *    ======== i2cmasterexample1.c ========
 */
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "ti_drivers_config.h"
#include <ti/drivers/UART.h>
#include <ti/drivers/I2C.h>
#include <ti/drivers/GPIO.h>

#include "msp.h"
#include "MPU2.h"
#include "uart.h"
#include "motor.h"
#include "PhoneInput.h"
#include "MPUsem.h"

#include <pthread.h>
#include <semaphore.h>
//#include "SITStraight.h"

#define MPU_ADDR 0x68
#define TEMP 0x41
#define GYRO 0x43
#define ACCEL 0x3B
#define POWER_MGMT_1 0x6B
#define WHOAMI 0x75

int readings;
int oldgyro2 = 0;
int oldaccel2 = 0;
int odd2 = 0;
int currentgyro2 = 0;
int different2;
//int volatile readings = 0;
bool ledState2 = 0;
bool ledTimerState2 = 0;


uint8_t txBuffer[10];
static uint8_t rxBuffer[20];


sem_t semBlink;
pthread_t mpu_handler2;
I2C_Handle      i2c2;
I2C_Params      i2cParams2;
I2C_Transaction i2cTransaction2;
#define THREADSTACKSIZE    1024
void setRegister2(uint8_t regAddr, uint8_t value)
{
    i2cWrite2(i2c2, MPU_ADDR, regAddr, value);
}
void i2cWrite2(I2C_Handle i2c2, uint8_t slaveAddr, uint8_t regAddr, uint8_t value)
{
    bool retVal = 0;
    txBuffer[0] = regAddr; //register addr
    txBuffer[1] = value; //data
    i2cTransaction2.slaveAddress = slaveAddr;
    i2cTransaction2.writeBuf = txBuffer;
    i2cTransaction2.writeCount = 2;
    i2cTransaction2.readBuf = rxBuffer;
    i2cTransaction2.readCount = 0;
    do {
        retVal = I2C_transfer(i2c2, &i2cTransaction2);
    } while(!retVal);
}
uint8_t* i2cRead2(I2C_Handle i2c2, uint8_t slaveAddr, uint8_t regAddr, uint8_t len)
{
    bool retVal = 0;
    txBuffer[0] = regAddr; //register addr
    i2cTransaction2.slaveAddress = slaveAddr;
    i2cTransaction2.writeBuf = txBuffer;
    i2cTransaction2.writeCount = 1;
    i2cTransaction2.readBuf = rxBuffer;
    i2cTransaction2.readCount = len;
    do {
        retVal = I2C_transfer(i2c2, &i2cTransaction2);
    } while(!retVal);

    return rxBuffer;
}

uint8_t getRegister2(uint8_t regAddr)
{

    return i2cRead2(i2c2, MPU_ADDR, regAddr, 1)[0];
}
void MPUinit2()
{
    //Init and set params for I2C
    I2C_init();
    I2C_Params_init(&i2cParams2);
    i2cParams2.bitRate = I2C_100kHz;
    i2c2 = I2C_open(1, &i2cParams2);

    //Power Cycle the MPU w/ VCC on P6.0
    P6DIR = 0;
    P6OUT = 0;
    delayM(1000);
    P6DIR = 1;
    P6OUT = 1;
    delayM(1000);

    //Wake up MPU
    setRegister2(POWER_MGMT_1, 0x40); //reset to default values
    delayM(100);
    setRegister2(POWER_MGMT_1, 0x00); //clear sleep bit
    delayM(100);
    setRegister2(POWER_MGMT_1, 0x01); //use internal gyro clock
    uint8_t whoami2 = getRegister2(WHOAMI);
    printf("MPU2 whoami = %x\n", whoami2);

}
sem_t semMPU;
bool mpuState_2 = 0;
char mpu_1[2];
void *BlinkFxn2(void *arg0)
{
    char test[] = "MPU2 X Axis: ";
    char mybuff2[] = "";
    int rc;
        /* Initialize Semaphore */
        rc = sem_init(&semMPU, 0, 0);
        if (rc == -1)
        {
            while (1)
                ;
        }
        while (1)
        {
//            float temp = getTemp2();
//            printf("temp(C) = %.2f\n", temp);
            /* Timer tells when to toggle LED On/Off*/
            rc = sem_wait(&semMPU);
            if (rc == 0)
            {

                if (mpuState_2)
                {
                    int countAngle2;
                    int readAngle2;
                    int16_t* newgyro = 0;
                    int16_t* newaccel= 0;
                    int counter = 0;

                    while(1)
                    {
                        int16_t* var2 = getGyro2();
//                            int16_t* var2 = getAccel();
                        newgyro = (var2[0]/131)+2;
//                            newaccel = (var2[0]/131);
                        readAngle2 = newgyro;
//                            UART_write(uart, &newaccel, sizeof(newaccel));

                        if (readAngle2 > -1 && readAngle2 < 3)
                        {

                            currentgyro2 += 0;
//                                currentgyro = 0;
                            oldgyro2 = 0;
                        }
                        else if (readAngle2 > oldgyro2+1 && readAngle2 > 4)
                        {
                            currentgyro2 += 1;
//                                oldgyro = readAngle;

                        }
                        else if (readAngle2 < oldgyro2-2 && readAngle2<-4)
                        {
                            currentgyro2 += -1;
//                                oldgyro = readAngle;
                        }

                        if (currentgyro2 < 10 && currentgyro2 > -1)
                        {
                            odd2 = 1;
                        }
                        else
                        {
                            odd2 = 0;
                        }

                        delayM(10);
                        sprintf (mybuff2, "%d", currentgyro2);
//                            sprintf (mybuff2, "%d", oldaccel);
                        oldgyro2 = readAngle2;
                        if (currentgyro2 > 95 || currentgyro2 < -100){
                        }
                        else
                        {
                            if (mpuState_2 == 1 ){

                                   if (odd2){
//                                       UART_write(uart, &test, sizeof(test)-1);
//                                       delayM(100);
//                                       UART_write(uart, &mybuff2, sizeof(mybuff2));
//                                       delayM(100);
//                                       UART_write(uart, "\n", 1);
//                                       printf("MPU2 X axis: %s\n", mybuff2);
                                       strcpy(mpu_1, mybuff2);

                                   }
                                   else{
//                                       UART_write(uart, &test, sizeof(test)-1);
//                                       delayM(100);
//                                       UART_write(uart, &mybuff2, sizeof(mybuff2)+1);
//                                       delayM(100);
//                                       UART_write(uart, "\n", 1);
                                       strcpy(mpu_1, mybuff2);
//                                       printf("MPU2 X axis: %s\n", mybuff2);
                                   }
                               }
                               else{}
                    }
                }
            }
        }
    }
}
void *mpuThread2(void *arg0)
{

    pthread_t BlinkFxn_Handle2;
    pthread_attr_t attrs;
    struct sched_param priParam;
    int retc;
    int detachState;
    /* Configure the LED pin */
//    GPIO_setConfig(CONFIG_GPIO_1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    /* Turn on user LED */
//    GPIO_write(CONFIG_GPIO_1, CONFIG_GPIO_LED_ON);

    /* Create a UART with data processing off. */

//    int16_t* accel = getAccel();
//    printf("accel XYZ = %d %d %d\n", accel[0]/2048, accel[1]/2048, accel[2]/2048);
    GPIO_init();
    MPUinit2();

    pthread_attr_init(&attrs);
    detachState = PTHREAD_CREATE_DETACHED;
    priParam.sched_priority = 3;
    pthread_attr_setschedparam(&attrs, &priParam);

    retc = pthread_attr_setdetachstate(&attrs, detachState);
    if (retc != 0)
    {
        /* pthread_attr_setdetachstate() failed */
        while (1)
            ;
    }

    retc |= pthread_attr_setstacksize(&attrs, THREADSTACKSIZE);
    if (retc != 0)
    {
        /* pthread_attr_setstacksize() failed */
        while (1)
            ;
    }
    /* Create BlinkFxn thread */
        retc = pthread_create(&BlinkFxn_Handle2, &attrs, BlinkFxn2, NULL);
        if (retc != 0)
        {
            /* pthread_create() failed */
            while (1)
                ;
        }
    return (NULL);
}
float getTemp2()
{
    return (1.0 * get1Axis2(TEMP)/340 + 36.53);
}
int16_t get1Axis2(uint8_t regAddr)
{
    uint8_t* buf = i2cRead2(i2c2, MPU_ADDR, regAddr, 2);
    return convert8to16(buf[0], buf[1]);
}
int16_t convert8to162(uint8_t val1, uint8_t val2)
{
    return (int16_t) (((uint16_t) val1 << 8) | ((uint16_t) val2));
}
int16_t* getGyro2()
{
    return get3Axis2(GYRO);
}

int16_t* get3Axis2(uint8_t regAddr)
{
    uint8_t* buf = i2cRead2(i2c2, MPU_ADDR, regAddr, 6);
    static int16_t xyz[3];
    xyz[0] = convert8to16(buf[0], buf[1]);
    xyz[1] = convert8to16(buf[2], buf[3]);
    xyz[2] = convert8to16(buf[4], buf[5]);
    return xyz;
}
