/*
 * test.h
 *
 *  Created on: 20 Oct 2019
 *      Author: jameswong
 */
#include <stdint.h>
#include <ti/drivers/I2C.h>
#include <pthread.h>
#include <semaphore.h>


#ifndef SITStraight_H_
#define SITStraight_H_



//void delayMs(int n);
//void wait(int n);
int16_t convert8To16(uint8_t val1, uint8_t val2);
int power(int base, int exponent);

#define MPU_ADDR 0x68
#define TEMP 0x41
#define GYRO 0x43
#define ACCEL 0x3B
#define POWER_MGMT_1 0x6B
#define WHOAMI 0x75
//int_fast32_t UART_write(UART_Handle handle, const void *buffer, size_t size);
//uint32_t UART_Read(uint32_t UART, uint8_t *Data, uint32_t Size);

void i2cWrite(I2C_Handle i2c, uint8_t slaveAddr, uint8_t regAddr, uint8_t value);
uint8_t* i2cRead(I2C_Handle i2c, uint8_t slaveAddr, uint8_t regAddr, uint8_t len);

void setRegister(uint8_t regAddr, uint8_t value);
uint8_t getRegister(uint8_t regAddr);

int16_t get1Axis(uint8_t regAddr);
int16_t* get3Axis(uint8_t regAddr);

//GET SENSORS
float getTemp();
int16_t* getGyro();
int16_t* getAccel();

void sendDataHC05(char *data);
char brx_buffer[1];

//STARTUP
void MPUinit();


uint8_t fs_sel = 3; //Gyro split
uint8_t afs_sel = 3;//accel split

uint8_t txBuffer[10];
static uint8_t rxBuffer[20];

void MPUinit()
{
    //Init and set params for I2C
//    I2C_init();
//    I2C_Params_init(&i2cParams);
//    i2cParams.bitRate = I2C_100kHz;
//    i2c = I2C_open(0, &i2cParams);

    //Power Cycle the MPU w/ VCC on P6.0
    P6DIR = 0;
    P6OUT = 0;
    delayMs(5000);
    P6DIR = 1;
    P6OUT = 1;
    delayMs(5000);


    //Wake up MPU
    setRegister(POWER_MGMT_1, 0x40); //reset to default values
    delayMs(100);
    setRegister(POWER_MGMT_1, 0x00); //clear sleep bit
    delayMs(100);
    setRegister(POWER_MGMT_1, 0x01); //use internal gyro clock
    uint8_t whoami = getRegister(WHOAMI);
    printf("whoami = %x\n", whoami);

}


void delayMs(int n) {
    int i, j;
    for (j = 0; j < n; j++)
        for (i = 750; i > 0; i--);      /* Delay */
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

int16_t convert8to16(uint8_t val1, uint8_t val2)
{
    return (int16_t) (((uint16_t) val1 << 8) | ((uint16_t) val2));
}

int power(int base, int exponent)
{
    int result = 1;
    int var;
    for (var = 0; var < exponent; ++var) {
        result *= base;
    }
    return result;
}
void setRegister(uint8_t regAddr, uint8_t value)
{
    i2cWrite(i2c, MPU_ADDR, regAddr, value);
}
uint8_t getRegister(uint8_t regAddr)
{

    return i2cRead(i2c, MPU_ADDR, regAddr, 1)[0];
}

int16_t get1Axis(uint8_t regAddr)
{
    uint8_t* buf = i2cRead(i2c, MPU_ADDR, regAddr, 2);
    return convert8to16(buf[0], buf[1]);
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
float getTemp()
{
    return (1.0 * get1Axis(TEMP)/340 + 36.53);
}

int16_t* getGyro()
{
    return get3Axis(GYRO);
}

int16_t* getAccel()
{
    return get3Axis(ACCEL);
}




#endif /* SITStraight_H_ */
