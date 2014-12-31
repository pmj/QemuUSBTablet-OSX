//
//  PJQemuUSBTabletDriver.h
//  QemuUSBTablet
//
//  Created by Phil Jordan on 31/12/2014.
//
/* Copyright 2014 Phil Jordan <phil@philjordan.eu>
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


#ifndef __QemuUSBTablet__PJQemuUSBTabletDriver__
#define __QemuUSBTablet__PJQemuUSBTabletDriver__

#include <IOKit/usb/IOUSBHIDDriver.h>

#define PJQemuUSBTabletDriver eu_philjordan_driver_QemuUSBTabletDriver

class PJQemuUSBTabletDriver : public IOUSBHIDDriver
{
	OSDeclareDefaultStructors(PJQemuUSBTabletDriver)
public:
	virtual IOReturn newReportDescriptor(IOMemoryDescriptor** descriptor) const;


protected:
	static IOMemoryMap* mapDescriptorIfExpected(IOMemoryDescriptor* desc);
};

#endif /* defined(__QemuUSBTablet__PJQemuUSBTabletDriver__) */
