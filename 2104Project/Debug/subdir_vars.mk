################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../MSP_EXP432P401R_TIRTOS.cmd 

SYSCFG_SRCS += \
../i2cmasterexample1.syscfg 

C_SRCS += \
../MPUThread.c \
../MPUThread2.c \
../UARTThread.c \
../VibrationMotor.c \
./syscfg/ti_drivers_config.c \
../main_tirtos.c \
../timer.c 

GEN_FILES += \
./syscfg/ti_drivers_config.c 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./MPUThread.d \
./MPUThread2.d \
./UARTThread.d \
./VibrationMotor.d \
./syscfg/ti_drivers_config.d \
./main_tirtos.d \
./timer.d 

OBJS += \
./MPUThread.obj \
./MPUThread2.obj \
./UARTThread.obj \
./VibrationMotor.obj \
./syscfg/ti_drivers_config.obj \
./main_tirtos.obj \
./timer.obj 

GEN_MISC_FILES += \
./syscfg/ti_drivers_config.h \
./syscfg/syscfg_c.rov.xs 

GEN_MISC_DIRS__QUOTED += \
"syscfg/" 

OBJS__QUOTED += \
"MPUThread.obj" \
"MPUThread2.obj" \
"UARTThread.obj" \
"VibrationMotor.obj" \
"syscfg/ti_drivers_config.obj" \
"main_tirtos.obj" \
"timer.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg/ti_drivers_config.h" \
"syscfg/syscfg_c.rov.xs" 

C_DEPS__QUOTED += \
"MPUThread.d" \
"MPUThread2.d" \
"UARTThread.d" \
"VibrationMotor.d" \
"syscfg/ti_drivers_config.d" \
"main_tirtos.d" \
"timer.d" 

GEN_FILES__QUOTED += \
"syscfg/ti_drivers_config.c" 

C_SRCS__QUOTED += \
"../MPUThread.c" \
"../MPUThread2.c" \
"../UARTThread.c" \
"../VibrationMotor.c" \
"./syscfg/ti_drivers_config.c" \
"../main_tirtos.c" \
"../timer.c" 

SYSCFG_SRCS__QUOTED += \
"../i2cmasterexample1.syscfg" 


