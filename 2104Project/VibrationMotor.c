/*
 * VibrationMotor.c
 *
 *  Created on: 4 Nov 2019
 *      Author: jameswong
 */

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "ti_drivers_config.h"
#include <ti/drivers/I2C.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/uart.h>
#include <ti/drivers/PWM.h>

#include "msp.h"
#include "motor.h"
#include "uart.h"

#include <semaphore.h>

char VOnState[] = "Vibration On\n";
char VOffState[] = "Vibration Off\n";
uint32_t   dutyValue;
sem_t semVibrate;
float power;
char timerbuff[] = "";
#define THREADSTACKSIZE    1024
bool vibrationState = 0;
void *VibrateFxn(void *arg0)
{
    int rc;
    int timer = 0;
    /* Initialize Semaphore */
    rc = sem_init(&semVibrate, 0, 0);
    if (rc == -1)
    {
        while (1)
            ;
    }
    while (1)
    {
        /* Timer tells when to toggle LED On/Off*/
        rc = sem_wait(&semVibrate);

        if (rc == 0)
        {
            if (vibrationState == 1)
            {

                PWM_start(pwm); // start pwm for vibration motor.

                power += 0.5 ; // slowly increase
//                GPIO_write(CONFIG_PWM_Motor, CONFIG_GPIO_LED_ON);
                dutyValue = (uint32_t) (((uint64_t) PWM_DUTY_FRACTION_MAX * power) / 100);
                if ( power > 0 && power <= 33){
                    PWM_start(pwm_green);
//                    GPIO_write(CONFIG_GPIO_Green, CONFIG_GPIO_LED_ON);
                }else if(power > 33 && power <= 66){
                    PWM_stop(pwm_green);
//                    GPIO_write(CONFIG_GPIO_Green, CONFIG_GPIO_LED_OFF);
                    GPIO_write(CONFIG_GPIO_RED, CONFIG_GPIO_LED_OFF);
                    GPIO_write(CONFIG_GPIO_BLUE, CONFIG_GPIO_LED_ON);


                }else{
                    GPIO_write(CONFIG_GPIO_BLUE, CONFIG_GPIO_LED_OFF);
                    GPIO_write(CONFIG_GPIO_RED, CONFIG_GPIO_LED_ON);


                }
                if (power > 99){
                    power = 99;
                }
                timer += 1;
                PWM_setDuty(pwm, dutyValue);
                PWM_setDuty(pwm_green, dutyValue);
            }
            else
            {
                power = 0;
                GPIO_write(CONFIG_GPIO_RED, CONFIG_GPIO_LED_OFF);
                GPIO_write(CONFIG_GPIO_BLUE, CONFIG_GPIO_LED_OFF);
                sprintf (timerbuff, "%d", timer);
                if (timer > 0){
                    UART_write(uart, &timerbuff, sizeof(timerbuff));
                    UART_write(uart, " seconds used", 13);
                    UART_write(uart, "\n", 1);
                    timer = 0;
                }

                PWM_stop(pwm);
                PWM_stop(pwm_green);
                GPIO_write(CONFIG_PWM_Motor, CONFIG_GPIO_LED_OFF);
            }
        }
    }
}
pthread_t motor_handler;
PWM_Handle pwm;
PWM_Handle pwm_green;

void *motorThread(void *arg0)
{
    pthread_t VirbateFxn_Handle;
    pthread_attr_t attrs;
    struct sched_param priParam;
    int detachState;
    int rc;

    GPIO_init();
    PWM_init();

    PWM_Params pwmParams;
    PWM_Params_init(&pwmParams);
    pwmParams.idleLevel = PWM_IDLE_LOW;         // Output low when PWM is not running
    pwmParams.periodUnits = PWM_PERIOD_HZ;      // Period is in Hz
    pwmParams.periodValue = 1e6;                // 1MHz
    pwmParams.dutyUnits = PWM_DUTY_FRACTION;    // Duty is in fractional percentage
    pwmParams.dutyValue = 0;                    // 0% initial duty cycle
    pwm = PWM_open(CONFIG_PWM_Motor, &pwmParams);
    pwm_green = PWM_open(CONFIG_PWM_Green, &pwmParams);





    pthread_attr_init(&attrs);
    detachState = PTHREAD_CREATE_DETACHED;
    priParam.sched_priority = 1; //Cung voi muc do uu tien cua thread chinhs
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
    rc = pthread_create(&VirbateFxn_Handle, &attrs, VibrateFxn, NULL);
    if (rc != 0)
    {
        /* pthread_create() failed */
        while (1)
            ;
    }




    return 0;
}
