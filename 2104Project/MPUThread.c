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
#include "MPU.h"
#include "uart.h"
#include "motor.h"
#include "MPUsem.h"
#include "PhoneInput.h"


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
int newgyro = 0;
int oldgyro = 0;
int oldaccel = 0;
int odd = 0;
int currentgyro = 000;
int different;
//int avgDegree[] =;
int numberOftime = 0;
//int volatile readings = 0;
bool mpuState_1 = 0;
int degree = 0;
bool ledTimerState = 0;


uint8_t txBuffer[10];
static uint8_t rxBuffer[20];

sem_t semMPU_1;
pthread_t mpu_handler;
I2C_Handle      i2c;
I2C_Params      i2cParams;
I2C_Transaction i2cTransaction;

#define THREADSTACKSIZE    1024


//
void setRegister(uint8_t regAddr, uint8_t value)
{
    i2cWrite(i2c, MPU_ADDR, regAddr, value);
}
void i2cWrite(I2C_Handle i2c, uint8_t slaveAddr, uint8_t regAddr, uint8_t value)
{
    bool retVal = 0;
    txBuffer[0] = regAddr; //register addr
    txBuffer[1] = value; //data
    i2cTransaction.slaveAddress = slaveAddr;
    i2cTransaction.writeBuf = txBuffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf = rxBuffer;
    i2cTransaction.readCount = 0;
    do {
        retVal = I2C_transfer(i2c, &i2cTransaction);
    } while(!retVal);
}
uint8_t* i2cRead(I2C_Handle i2c, uint8_t slaveAddr, uint8_t regAddr, uint8_t len)
{
    bool retVal = 0;
    txBuffer[0] = regAddr; //register addr
    i2cTransaction.slaveAddress = slaveAddr;
    i2cTransaction.writeBuf = txBuffer;
    i2cTransaction.writeCount = 1;
    i2cTransaction.readBuf = rxBuffer;
    i2cTransaction.readCount = len;
    do {
        retVal = I2C_transfer(i2c, &i2cTransaction);
    } while(!retVal);

    return rxBuffer;
}
uint8_t getRegister(uint8_t regAddr)
{
    return i2cRead(i2c, MPU_ADDR, regAddr, 1)[0];
}
void MPUinit()
{
    //Init and set params for I2C
    I2C_init();
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_100kHz;
    i2c = I2C_open(0, &i2cParams);
    //Power Cycle the MPU w/ VCC on P6.0
    P6DIR = 0;
    P6OUT = 0;
    delayM(5000);
    P6DIR = 1;
    P6OUT = 1;
    delayM(5000);
    uint8_t fs_sel = 3;                             //Gyro split
    uint8_t afs_sel = 3;                            //accel split
    //Wake up MPU
    setRegister(POWER_MGMT_1, 0x40);                //reset to default values
    delayM(100);
    setRegister(POWER_MGMT_1, 0x00);                //clear sleep bit
    delayM(100);
    setRegister(POWER_MGMT_1, 0x01);                //use internal gyro clock
    uint8_t whoami = getRegister(WHOAMI);
    printf("whoami = %x\n", whoami);                //Get MPU WhoAmI address
}
char readbuff;
void *mpuFxn(void *arg0)
{
    char tempBuffer[10];
    char xaxisMPU[] = "";
    char mpu[] = "MPU1 X Axis: ";
    char output[] = "";
    int rc;
    /* Initialize Semaphore */
    rc = sem_init(&semMPU_1, 0, 0);
    if (rc == -1)
    {
        while (1)
            ;
    }
    while (1)
    {
        /* Timer tells when to toggle LED On/Off*/
        delayM(10);
        rc = sem_wait(&semMPU_1);
        if (rc == 0)
        {
            printf("MPUthread\n");

            if (mpuState_1 && degree >0 ) // Start only if user turn on and input amount of degree
            {
                        delayM(200);
//                        float temp = getTemp();
//                        printf("temp(C) = %.2f\n", (temp/3400000000 + 36.53));
//                        sprintf (tempBuffer, "%.2f", (temp/3400000000 + 36.53));
                        delayM(200);
//                        UART_write(uart, &tempBuffer, 5);
//                        delayM(200);
//                        UART_write(uart, "\n", 1);
                        delayM(10);
                        int countAngle;
                        int readAngle;
                        int16_t* newgyro = 0;
                        int16_t* newaccel= 0;
                        int counter = 0;
                        currentgyro = 0;
                        while(1)
                        {
                            int16_t* var1 = getGyro();
                            newgyro = (var1[0]/131)+2;
                            readAngle = newgyro;
                            if (readAngle > -1 && readAngle < 3)         // To ensure more accuracy, mpu readings have to be over 3 and less then -1
                            {
                                currentgyro += 0;                        // Maintan at current X axis
                                oldgyro = 0;                             // Force previous reading to 0
                            }
                            else if (readAngle > oldgyro+1 && readAngle > 4)  // if reading is more then previous reading and reading must be over 4
                            {
                                currentgyro += 1;                             // Add 1 to current X axis

                            }
                            else if (readAngle < oldgyro-2 && readAngle<-4)   // if reading is less then previous reading and reading must be lesser then -4
                            {
                                currentgyro += -1;                            // Minus 1 to current X axis
                            }

                            if (currentgyro < 10 && currentgyro > -1)        //if current X axis is from 0 to 9
                            {
                                odd = 1;                                     //Means it is an odd number
                            }
                            else
                            {
                                odd = 0;                                    // else it is an even number (eg. -1, -2, 10, 12 )
                            }
                            delayM(20);
                            sprintf (xaxisMPU, "%d", currentgyro);          // Convert int to char
                            oldgyro = readAngle;                            // save current reading to previous reading
                            if (currentgyro > 95 || currentgyro < -100){    // if current x axis is more than 95 degree and less then -100 degree do nothing
                            }
                            else
                            {
                                if (mpuState_1 == 1 ) // Only write to UART if user turn on the device
                                {
                                   if (currentgyro >= degree)
                                   {
                                       if (odd){                // If value write to UART is odd
                                           mpuState_2 = 1;        // Start taking in readings from Second MPU
                                           mpu2();              // Post semaphore to Second MPU to start readings
                                           delayM(50);
                                           UART_write(uart, &mpu, sizeof(mpu)-1);
                                           UART_write(uart, &xaxisMPU, sizeof(xaxisMPU));    // Write to UART reading from First MPU
                                           delayM(20);
                                           UART_write(uart, "\n", 1);
                                           printf("X axis: %s\n", xaxisMPU);
                                           vibrationState = 1;                          //Turn on Vibration Motor
                                           vibration();                                 //Call Vibration motor function and unlock semaphore
                                       }
                                       else
                                       {                        // If value write to UART is even
                                           mpuState_2 = 1;        // Start taking in readings from Second MPU
                                           mpu2();              // Post semaphore to Second MPU to start readings
                                           delayM(50);
                                           UART_write(uart, &mpu, sizeof(mpu)-1);
                                           UART_write(uart, &xaxisMPU, sizeof(xaxisMPU)+1); // Write to UART reading from First MPU
                                           delayM(20);
                                           if (strlen(mpu_1) == 1){
                                               UART_write(uart, " MPU2 X Axis: ", 14);
                                               UART_write(uart, &mpu_1, sizeof(mpu_1)-1);   //Write to UART reading from Second MPU
                                           }
                                           else{
                                               UART_write(uart, " MPU2 X Axis: ", 14);
                                               UART_write(uart, &mpu_1, sizeof(mpu_1)); //Write to UART reading from Second MPU
                                           }
                                           delayM(20);
                                           UART_write(uart, "\n", 1);
                                           printf("X axis: %s\n", xaxisMPU);
                                           numberOftime += 1;
                                           vibrationState = 1;                          //Turn on Vibration Motor
                                           vibration();                                 //Call Vibration motor function and unlock semaphore
                                       }
                                   }
                                   else                     // MPU X axis have not surpassed the degree inputed by the user
                                   {
                                       delayM(10);
                                       vibrationState = 0;      //Disable Vibration Motor
                                       vibration();             //Post to Vibration Motor to diable Vibration motor
                                       delayM(10);
                                       mpuState_2 = 0;            //Disable Second MPU
                                       mpu2();                  //Post to Second MPU to stop readings.
                                       delayM(10);

                                   }

                               }

                               else   // When Device is switch Off, Vibration should not occur
                               {

                                   sprintf (xaxisMPU, "%d", numberOftime);
                                   UART_write(uart, "Total Number of time crosses unhealthy degree: ", 47);
                                   UART_write(uart, &xaxisMPU, 1);
                                   UART_write(uart, "\n", 1);
                                   vibrationState = 0;  //Disable Vibration Motor
                                   vibration();         //Post to Vibration Motor to diable Vibration motor
                                   break;
                               }
                            }
                            }
            }
            else
            {
            }
        }

    }
}
void vibration(){
    int rc;
    rc = sem_post(&semVibrate);
    if (rc == -1)
    {
        while (1)
            ;
    }
}
void mpu2(){
    int rc;
    rc = sem_post(&semMPU);
    if (rc == -1)
    {
        while (1)
            ;
    }
}
void *mpuThread(void *arg0)
{
    pthread_t mpuFxn_Handle;
    pthread_attr_t attrs;
    struct sched_param priParam;
    int retc;
    int detachState;
//    int16_t* accel = getAccel();
//    printf("accel XYZ = %d %d %d\n", accel[0]/2048, accel[1]/2048, accel[2]/2048);
    GPIO_init();
    MPUinit();
    pthread_attr_init(&attrs);
    detachState = PTHREAD_CREATE_DETACHED;
    priParam.sched_priority = 4;
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
    /* Create mpuFxn thread */
        retc = pthread_create(&mpuFxn_Handle, &attrs, mpuFxn, NULL);
        if (retc != 0)
        {
            /* pthread_create() failed */
            while (1)
                ;
        }
    return (NULL);
}
float getTemp()
{
    return (1.0 * get1Axis(TEMP)/340 + 36.53);
}
int16_t get1Axis(uint8_t regAddr)
{
    uint8_t* buf = i2cRead(i2c, MPU_ADDR, regAddr, 2);
    return convert8to16(buf[0], buf[1]);
}
int16_t convert8to16(uint8_t val1, uint8_t val2)
{
    return (int16_t) (((uint16_t) val1 << 8) | ((uint16_t) val2));
}
int16_t* getGyro()
{
    return get3Axis(GYRO);
}


int16_t* getAccel()
{
    return get3Axis(ACCEL);
}
int16_t* get3Axis(uint8_t regAddr)
{
    uint8_t* buf = i2cRead(i2c, MPU_ADDR, regAddr, 6);
    static int16_t xyz[3];
    xyz[0] = convert8to16(buf[0], buf[1]);
    xyz[1] = convert8to16(buf[2], buf[3]);
    xyz[2] = convert8to16(buf[4], buf[5]);
    return xyz;
}
