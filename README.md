#BUILD

. modular_tools.sh build

. modular_tools.sh copy_image

then to copy and update on device:

scp ilan@10.100.102.22:/tmp/openwrt-ipq40xx-generic-8dev_habanero-dvk-squashfs-sysupgrade.bin /tmp/

sysupgrade -F -v -c /tmp/openwrt-ipq40xx-generic-8dev_habanero-dvk-squashfs-sysupgrade.bin

#SET BOOTLOADER PASSWORD

stop on uboot

setenv autostop <mypassword>

saveenv

reset


