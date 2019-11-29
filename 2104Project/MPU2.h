/*
 * MPU.h
 *
 *  Created on: 8 Nov 2019
 *      Author: jameswong
 */
#include <pthread.h>
#include <semaphore.h>
#include <ti/drivers/I2C.h>


#ifndef MPU2_H_
#define MPU2_H_

#ifdef __cplusplus
extern "C" {
#endif

extern I2C_Handle      i2c2;                // Create I2C_Handle for Second MPU
extern I2C_Params      i2cParams2;          // Create I2C_Params for Second MPU
extern I2C_Transaction i2cTransaction2;      // Create I2C_Transaction for Second MPU



extern void i2cWrite2(I2C_Handle i2c, uint8_t slaveAddr, uint8_t regAddr, uint8_t value);   //Second MPU I2CWrite function prototype
extern uint8_t* i2cRead2(I2C_Handle i2c, uint8_t slaveAddr, uint8_t regAddr, uint8_t len);  //Second MPU I2CRead function prototype


extern int16_t get1Axis2(uint8_t regAddr);
extern float getTemp2();
extern int16_t* getGyro2();
extern uint8_t getRegister2(uint8_t regAddr);



#endif /* MPU2_H_ */
