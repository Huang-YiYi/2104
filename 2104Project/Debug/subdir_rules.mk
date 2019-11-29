################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Users/jameswong/ti/simplelink_msp432p4_sdk_3_20_00_06/source/ti/posix/ccs" --include_path="/Users/jameswong/ti/simplelink_msp432p4_sdk_3_30_00_13/source/ti/posix/ccs" --include_path="/Users/jameswong/ti/simplelink_msp432p4_sdk_3_20_00_06/source/ti/posix" --include_path="/Users/jameswong/ti/simplelink_msp432p4_sdk_3_20_00_06/source/ti/posix/tirtos" --include_path="/Users/jameswong/ti/simplelink_msp432p4_sdk_3_30_00_13/source/ti/drivers/uart" --include_path="/Applications/ti/ccs910/ccs/ccs_base/arm/include" --include_path="/Applications/ti/ccs910/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccs910/ccs/ccs_base/arm/include" --include_path="/Users/jameswong/Desktop/ICT2104_Sleep_Study-master/2104Project" --include_path="/Users/jameswong/Desktop/ICT2104_Sleep_Study-master/2104Project/Debug" --include_path="/Users/jameswong/ti/simplelink_msp432p4_sdk_3_30_00_13/source" --include_path="/Users/jameswong/ti/simplelink_msp432p4_sdk_3_30_00_13/source/third_party/CMSIS/Include" --include_path="/Users/jameswong/ti/simplelink_msp432p4_sdk_3_30_00_13/source/ti/posix/ccs" --include_path="/Applications/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/include" --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="/Users/jameswong/Desktop/ICT2104_Sleep_Study-master/2104Project/Debug/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-130098577:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-130098577-inproc

build-130098577-inproc: ../i2cmasterexample1.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"/Applications/ti/ccs910/ccs/utils/sysconfig/sysconfig_cli.sh" -s "/Users/jameswong/ti/simplelink_msp432p4_sdk_3_30_00_13/.metadata/product.json" -o "syscfg" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-130098577 ../i2cmasterexample1.syscfg
syscfg/ti_drivers_config.h: build-130098577
syscfg/syscfg_c.rov.xs: build-130098577
syscfg/: build-130098577

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Users/jameswong/ti/simplelink_msp432p4_sdk_3_20_00_06/source/ti/posix/ccs" --include_path="/Users/jameswong/ti/simplelink_msp432p4_sdk_3_30_00_13/source/ti/posix/ccs" --include_path="/Users/jameswong/ti/simplelink_msp432p4_sdk_3_20_00_06/source/ti/posix" --include_path="/Users/jameswong/ti/simplelink_msp432p4_sdk_3_20_00_06/source/ti/posix/tirtos" --include_path="/Users/jameswong/ti/simplelink_msp432p4_sdk_3_30_00_13/source/ti/drivers/uart" --include_path="/Applications/ti/ccs910/ccs/ccs_base/arm/include" --include_path="/Applications/ti/ccs910/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccs910/ccs/ccs_base/arm/include" --include_path="/Users/jameswong/Desktop/ICT2104_Sleep_Study-master/2104Project" --include_path="/Users/jameswong/Desktop/ICT2104_Sleep_Study-master/2104Project/Debug" --include_path="/Users/jameswong/ti/simplelink_msp432p4_sdk_3_30_00_13/source" --include_path="/Users/jameswong/ti/simplelink_msp432p4_sdk_3_30_00_13/source/third_party/CMSIS/Include" --include_path="/Users/jameswong/ti/simplelink_msp432p4_sdk_3_30_00_13/source/ti/posix/ccs" --include_path="/Applications/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/include" --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="/Users/jameswong/Desktop/ICT2104_Sleep_Study-master/2104Project/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


