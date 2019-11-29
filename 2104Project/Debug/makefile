################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /Applications/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS

GEN_OPTS += /Users/jameswong/Desktop/ICT2104_Sleep_Study-master/tirtos_builds_MSP_EXP432P401R_release_ccs/Debug/configPkg/compiler.opt
GEN_OPTS__FLAG := --cmd_file="/Users/jameswong/Desktop/ICT2104_Sleep_Study-master/tirtos_builds_MSP_EXP432P401R_release_ccs/Debug/configPkg/compiler.opt"
GEN_CMDS += /Users/jameswong/Desktop/ICT2104_Sleep_Study-master/tirtos_builds_MSP_EXP432P401R_release_ccs/Debug/configPkg/linker.cmd
GEN_CMDS__FLAG := -l"/Users/jameswong/Desktop/ICT2104_Sleep_Study-master/tirtos_builds_MSP_EXP432P401R_release_ccs/Debug/configPkg/linker.cmd"

ORDERED_OBJS += \
"./MPUThread.obj" \
"./MPUThread2.obj" \
"./UARTThread.obj" \
"./VibrationMotor.obj" \
"./syscfg/ti_drivers_config.obj" \
"./main_tirtos.obj" \
"./timer.obj" \
"../MSP_EXP432P401R_TIRTOS.cmd" \
-l"ti/display/lib/display.aem4f" \
-l"ti/grlib/lib/ccs/m4f/grlib.a" \
-l"third_party/spiffs/lib/ccs/m4f/spiffs.a" \
-l"ti/drivers/lib/drivers_msp432p401x.aem4f" \
-l"third_party/fatfs/lib/ccs/m4f/fatfs.a" \
-l"ti/dpl/lib/dpl_msp432p401x.aem4f" \
$(GEN_CMDS__FLAG) \
-l"ti/devices/msp432p4xx/driverlib/ccs/msp432p4xx_driverlib.lib" \
-llibc.a \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
2104Project.out \

EXE_OUTPUTS__QUOTED += \
"2104Project.out" \

BIN_OUTPUTS += \
2104Project.hex \

BIN_OUTPUTS__QUOTED += \
"2104Project.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "2104Project.out"

dependents:
	-cd /Users/jameswong/Desktop/ICT2104_Sleep_Study-master/tirtos_builds_MSP_EXP432P401R_release_ccs/Debug && $(MAKE) all

# Tool invocations
2104Project.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS) /Users/jameswong/Desktop/ICT2104_Sleep_Study-master/tirtos_builds_MSP_EXP432P401R_release_ccs/Debug/tirtos_builds_MSP_EXP432P401R_release_ccs.lib
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"/Applications/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on -z -m"2104Project.map" -i"/Users/jameswong/ti/simplelink_msp432p4_sdk_3_30_00_13/source" -i"/Users/jameswong/ti/simplelink_msp432p4_sdk_3_30_00_13/kernel/tirtos/packages" -i"/Applications/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/lib" --diag_wrap=off --display_error_number --warn_sections --xml_link_info="2104Project_linkInfo.xml" --rom_model -o "2104Project.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

2104Project.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"/Applications/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/bin/armhex"  -o "2104Project.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(BIN_OUTPUTS__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "MPUThread.obj" "MPUThread2.obj" "UARTThread.obj" "VibrationMotor.obj" "syscfg/ti_drivers_config.obj" "main_tirtos.obj" "timer.obj" 
	-$(RM) "MPUThread.d" "MPUThread2.d" "UARTThread.d" "VibrationMotor.d" "syscfg/ti_drivers_config.d" "main_tirtos.d" "timer.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/Users/jameswong/Desktop/ICT2104_Sleep_Study-master/tirtos_builds_MSP_EXP432P401R_release_ccs/Debug/tirtos_builds_MSP_EXP432P401R_release_ccs.lib:

-include ../makefile.targets

