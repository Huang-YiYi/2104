/*
 *  ======== ti_drivers_config.h ========
 *  Configured TI-Drivers module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSP_EXP432P401R
 *  by the SysConfig tool.
 */
#ifndef ti_drivers_config_h
#define ti_drivers_config_h

#define CONFIG_SYSCONFIG_PREVIEW

#define CONFIG_MSP_EXP432P401R

#ifndef DeviceFamily_MSP432P401x
#define DeviceFamily_MSP432P401x
#endif

#include <ti/devices/DeviceFamily.h>

#include <stdint.h>

/* support C++ sources */
#ifdef __cplusplus
extern "C" {
#endif


/*
 *  ======== GPIO ========
 */

/* P2.0, LaunchPad LED 2 Red */
#define CONFIG_GPIO_RED             0
/* P2.2, LaunchPad LED 2 Blue */
#define CONFIG_GPIO_BLUE            1
/* P1.0, LaunchPad LED 1 Red */
#define CONFIG_GPIO_RED_LEFT        2
/* P1.1, LaunchPad Button S1 (Left) */
#define CONFIG_GPIO_0               3

/* LEDs are active high */
#define CONFIG_GPIO_LED_ON  (1)
#define CONFIG_GPIO_LED_OFF (0)

#define CONFIG_LED_ON  (CONFIG_GPIO_LED_ON)
#define CONFIG_LED_OFF (CONFIG_GPIO_LED_OFF)


/*
 *  ======== I2C ========
 */

/*
 *  SCL: P6.5
 *  SDA: P6.4
 */
#define CONFIG_I2C_0                0
/*
 *  SCL: P1.7
 *  SDA: P1.6
 */
#define CONFIG_I2C_1                1

/* ======== I2C Addresses and Speeds ======== */
#include <ti/drivers/I2C.h>

/* ---- CONFIG_I2C_0 I2C bus components ---- */

/* no components connected to CONFIG_I2C_0 */

/* max speed unspecified, defaulting to 100 Kbps */
#define CONFIG_I2C_0_MAXSPEED   (100U) /* Kbps */
#define CONFIG_I2C_0_MAXBITRATE ((I2C_BitRate)I2C_100kHz)

/* ---- CONFIG_I2C_1 I2C bus components ---- */

/* no components connected to CONFIG_I2C_1 */

/* max speed unspecified, defaulting to 100 Kbps */
#define CONFIG_I2C_1_MAXSPEED   (100U) /* Kbps */
#define CONFIG_I2C_1_MAXBITRATE ((I2C_BitRate)I2C_100kHz)


/*
 *  ======== PWM ========
 */

/* P2.5 */
#define CONFIG_PWM_Motor            0
/* P2.1, LaunchPad LED 2 Green */
#define CONFIG_PWM_Green            1


/*
 *  ======== Timer ========
 */

#define CONFIG_TIMER_0              0

/*
 *  ======== UART ========
 */

/*
 *  TX: P1.3
 *  RX: P1.2
 *  XDS110 UART
 */
#define CONFIG_UART_0               0


/*
 *  ======== Button ========
 */

/* P1.1, LaunchPad Button S1 (Left) */
#define CONFIG_BUTTON_0             0


/*
 *  ======== Board_init ========
 *  Perform all required TI-Drivers initialization
 *
 *  This function should be called once at a point before any use of
 *  TI-Drivers.
 */
extern void Board_init(void);

/*
 *  ======== Board_initGeneral ========
 *  (deprecated)
 *
 *  Board_initGeneral() is defined purely for backward compatibility.
 *
 *  All new code should use Board_init() to do any required TI-Drivers
 *  initialization _and_ use <Driver>_init() for only where specific drivers
 *  are explicitly referenced by the application.  <Driver>_init() functions
 *  are idempotent.
 */
#define Board_initGeneral Board_init

#ifdef __cplusplus
}
#endif

#endif /* include guard */
