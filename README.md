#BUILD

. modular_tools.sh build

#SET BOOTLOADER PASSWORD

stop on uboot

setenv autostop <mypassword>

saveenv

reset
