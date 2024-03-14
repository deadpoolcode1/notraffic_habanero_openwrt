#BUILD

. modular_tools.sh build

. modular_tools.sh copy_image

then to copy and update on device:

scp ilan@10.100.102.22:/tmp/openwrt-ipq40xx-generic-8dev_habanero-dvk-squashfs-sysupgrade.bin /tmp/

sysupgrade -F -v -c /tmp/openwrt-ipq40xx-generic-8dev_habanero-dvk-squashfs-sysupgrade.bin

#SET BOOTLOADER STOP ENABLE

fw_setenv bootdelay 1

#SET BOOTLOADER STOP DISABLE

fw_setenv bootdelay 0

#HOW TO FLASH BOOTLOADER
https://wiki.8devices.com/habanero:uboot
