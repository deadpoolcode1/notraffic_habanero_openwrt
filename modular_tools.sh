#!/bin/bash

# source this script

help()
{
	echo "build	- 	huild image"
	echo "setup 	- 	one time build machine setup"
	echo "help 	-	help menu"
}

setup()
{
	sudo apt-get -y install git git-doc subversion build-essential flex wget gawk unzip man file python2.7 zlib1g-dev libssl-dev libncurses5-dev
}

build()
{
	echo "build now"
	./scripts/feeds update -a
	./scripts/feeds install -a
	make defconfig
	make -j$(nproc) IGNORE_ERRORS='m n y'
}

view_build_details()
{
	echo "show image details"
	leaf profile -v
}

if [ -n "$*" ]; then
	eval "$*" # execute arguments
	#echo $* finished, ret=$?
else
	if [ "$0" != "$BASH_SOURCE" ]; then
		help
	else
		echo $BASH_SOURCE - a library of Sierra, mangOH, legato and yocto tools
		help
	fi
fi
