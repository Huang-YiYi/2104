################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
build-223847199:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-223847199-inproc

build-223847199-inproc: ../release.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"/Applications/ti/ccs910/xdctools_3_55_02_22_core/xs" --xdcpath="/Users/jameswong/ti/simplelink_msp432p4_sdk_3_30_00_13/source;/Users/jameswong/ti/simplelink_msp432p4_sdk_3_30_00_13/kernel/tirtos/packages;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4F -p ti.platforms.msp432:MSP432P401R -r release -c "/Applications/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-223847199 ../release.cfg
configPkg/compiler.opt: build-223847199
configPkg/: build-223847199


