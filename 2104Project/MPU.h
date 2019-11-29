/*
 * MPU.h
 *
 *  Created on: 8 Nov 2019
 *      Author: jameswong
 */
#include <pthread.h>
#include <semaphore.h>
#include <ti/drivers/I2C.h>


#ifndef MPU_H_
#define MPU_H_

#ifdef __cplusplus
extern "C" {
#endif






extern I2C_Handle      i2c;                 // Create I2C_Handle for First MPU
extern I2C_Params      i2cParams;           // Create I2C_Params for First MPU
extern I2C_Transaction i2cTransaction;      // Create I2C_Transaction for First MPU


extern uint8_t fs_sel = 3;                  //Gyro split
extern uint8_t afs_sel = 3;                 //accel split


extern void i2cWrite(I2C_Handle i2c, uint8_t slaveAddr, uint8_t regAddr, uint8_t value);   //First MPU I2CWrite function prototype
extern uint8_t* i2cRead(I2C_Handle i2c, uint8_t slaveAddr, uint8_t regAddr, uint8_t len);  //First MPU I2CRead function prototype


extern int16_t get1Axis(uint8_t regAddr);       //Functions to get various axis for gyro and temp
extern int16_t* getGyro();
extern uint8_t getRegister(uint8_t regAddr);



#endif /* MPU_H_ */
