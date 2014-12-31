#!/bin/sh
if [ "$1" == "" ]
then
	echo "Please pass the path to the 'Products' directory as the command line argument"
	exit
fi

echo building QemuUSBTablet.pkg
pkgbuild --root "$1"  --component-plist QemuUSBTablet-kext.plist --scripts ./scripts/ QemuUSBTablet.pkg
echo building QemuUSBTabletUSBDriver.pkg
pkgbuild --root "$1"  --component-plist QemuUSBTabletUSBDriver-kext.plist --scripts ./scripts/ QemuUSBTabletUSBDriver.pkg

echo auto-generating Distribution.xml
productbuild --synthesize --package QemuUSBTablet.pkg --package QemuUSBTabletUSBDriver.pkg Distribution.xml

echo patching Distribution.xml with manual changes
patch -p2 < distribution-xml.patch

