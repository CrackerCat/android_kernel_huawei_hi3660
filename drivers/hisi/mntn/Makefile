ccflags-y += -I$(srctree)/drivers/hisi/secure_boot/inc -Wall -Werror
EXTRA_CFLAGS += -Idrivers/hisi/tzdriver

obj-$(CONFIG_HISILICON_PLATFORM_MAINTAIN)	+= hisilicon_platform_mntn.o
obj-$(CONFIG_HISI_BOOT_TIME) += boottime.o
obj-$(CONFIG_HISI_BB) += blackbox/
obj-$(CONFIG_HISI_POWER_OFF)	+= hisi_poweroff.o
obj-$(CONFIG_HISI_FIQ)	+= hisi_fiq.o
hisilicon_platform_mntn-y := util.o dump.o fastbootlog.o mntn_filesys.o hisi_bootup_keypoint.o
subdir-ccflags-$(CONFIG_HISI_BB)               += -Idrivers/hisi/mntn/blackbox/
obj-$(CONFIG_HISI_MNTNDUMP)       += mntn_dump.o
obj-$(CONFIG_HISI_HISEE_MNTN) += hisee/
obj-$(CONFIG_HISI_BL31_MNTN) += bl31/
