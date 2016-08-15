//
//  PJQemuUSBTablet1011.h
//  QemuUSBTablet
//
//  Created by Phil Dennis-Jordan on 15/8/2016.
//
/* Copyright 2016 Phil & Laura Dennis-Jordan <phil@philjordan.eu>
 * This code made available under the GNU LGPL
 * (GNU Library/Lesser General Public License)
 * A copy of this license can be found in the LICENSE file provided together
 * with this source file, or at https://www.gnu.org/licenses/lgpl.html if
 * that file is missing.
 *
 * For practical purposes, what does this mean?
 * - You may use, modify and/or run this code freely
 * - You may redistribute this code and the compiled kext, provided that
 *   copyright notices remain intact and that you make available the full source
 *   code, including any modifications.
 * - You may create and distribute other kexts with different licenses which
 *   depend upon this kext, as long as this kext remains independently loadable
 *   and modifiable by all users.
 *
 * If you require additional permissions not covered by this license, please
 * contact the author at phil@philjordan.eu - other licensing options are available.
 */


#pragma once

#include <IOKit/usb/IOUSBHostHIDDevice.h>
#include <IOKit/hidevent/IOHIDEventDriver.h>

#define QemuUSBTablet1011 eu_dennis_jordan_driver_QemuUSBTablet1011

class QemuUSBTablet1011 : public IOUSBHostHIDDevice
{
	OSDeclareDefaultStructors(QemuUSBTablet1011)
  typedef IOUSBHostHIDDevice super;
public:
	virtual IOReturn newReportDescriptor(IOMemoryDescriptor** descriptor) const override;
  bool publishProperties(IOService * provider) override;

protected:
	static IOMemoryMap* mapDescriptorIfExpected(IOMemoryDescriptor* desc);
};
