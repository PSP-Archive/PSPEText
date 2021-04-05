#! /bin/bash

make $1
if [ -d E:/seplugins ]; then
	cp pspetext.prx E:/seplugins
	rm -f E:/debug.log
	echo "Copied to PSP"
fi
