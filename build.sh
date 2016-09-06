#!/bin/sh

export XCODEAPP=`mdfind 'kMDItemCFBundleIdentifier = "com.apple.dt.Xcode" && (kMDItemVersion = "7.3.1")'`
"$XCODEAPP/Contents/Developer/usr/bin/xcodebuild"  -target QemuUSBTablet-all $@
