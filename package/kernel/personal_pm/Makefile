#
# Copyright (C) 2008-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=personal_pm
PKG_RELEASE:=3
PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/package.mk

define KernelPackage/personal_pm
  SUBMENU:=Other modules
  TITLE:=personal GPIO driver
  FILES:=$(PKG_BUILD_DIR)/personal_pm.ko
  AUTOLOAD:=$(call AutoLoad,30,personal_pm,1)
  KCONFIG:=
endef

define KernelPackage/personal_pm/description
 setting and naming dedicated gpio settings.
endef

define Build/Compile
	$(KERNEL_MAKE) M="$(PKG_BUILD_DIR)" modules
endef

$(eval $(call KernelPackage,personal_pm))
