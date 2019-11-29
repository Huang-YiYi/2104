#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /Users/jameswong/ti/simplelink_msp432p4_sdk_3_30_00_13/source;/Users/jameswong/ti/simplelink_msp432p4_sdk_3_30_00_13/kernel/tirtos/packages
override XDCROOT = /Applications/ti/ccs910/xdctools_3_55_02_22_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /Users/jameswong/ti/simplelink_msp432p4_sdk_3_30_00_13/source;/Users/jameswong/ti/simplelink_msp432p4_sdk_3_30_00_13/kernel/tirtos/packages;/Applications/ti/ccs910/xdctools_3_55_02_22_core/packages;..
HOSTOS = MacOS
endif
