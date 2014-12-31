# OS X Driver for the Qemu USB Tablet input device.

When running a virtual machine in a window, it's useful to simulate an absolute pointing device, so that the host computer's mouse cursor motion through the window is seamless.
Qemu offers such a device via the `-device usb-tablet` option (in contrast to `-device usb-mouse`).
Unfortunately, OS X's HID device drivers don't pick up this device correctly.

To solve the problem, I've written a driver that makes it work.
On OS X 10.8 and earlier, all that is needed is a codeless kext that tells Apple's driver that it already knows how to drive the device.
OS X 10.9 and newer treat the device as an analog stick when you do this, converting distance from the middle of the screen as a velocity to apply to relative motion of the mouse cursor.
This is an even worse user experience than with the `usb-mouse` device, so I've written another kext that subtly rewrites the device's HID report descriptor before Apple's driver has a chance to pick it up.
Specifically, the device reports a usage mode of "pointer" (1).
OS X's drivers expect either "Mouse" (2) or "Digitiser", so the kext changes that single byte from 1 to 2 and everything starts working.

To use this driver:

 * Have OS X running in a Qemu (KVM) virtual machine, for example using [these excellent instructions](http://www.contrib.andrew.cmu.edu/~somlo/OSXKVM/).
 * Download the driver installer from this website to the virtual machine: [http://philjordan.eu/osx-virt/](http://philjordan.eu/osx-virt/)
 * Run the installer (this requires administrator access)
 * Shut down the virtual machine
 * Start the virtual machine back up with the usb-tablet device instead of the mouse.

Notes:

 * This driver is code-signed by Phillip Jordan (the author), so OS X 10.9 and up will accept it without complaining, and the installer will not produce the gatekeeper warning on 10.7.5 and up. Check the signature by clicking the lock icon in the top right corner to make sure the package has not been tampered with.
 * I have built the kext from source using Xcode 6.1.1 and the OS X 10.9 SDK. If you use the 10.10 SDK, the resulting binary will not load on 10.9. So if your Xcode version doesn't come with the 10.9 SDK, I suggest downloading and installing Xcode 6.1.1. (You can have multiple versions of Xcode installed in parallel)
 * The code is free software, released under the [LGPL (GNU Lesser General Public License)](https://www.gnu.org/licenses/lgpl.html). If you would like to use this software, but the license does not meet your requirements, or if you require commercial support for this software, please contact the author, [Phil Jordan](phil@philjordan.eu).
 * The software comes with no warranties. Use at your own risk. Please note that kernel extensions run at the lowest possible level in the operating system, so programming errors can cause crashes, data corruption, security issues, or worse.

