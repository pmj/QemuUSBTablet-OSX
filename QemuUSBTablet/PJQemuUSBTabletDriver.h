//
//  PJQemuUSBTabletDriver.h
//  QemuUSBTablet
//
//  Created by Phil Jordan on 31/12/2014.
//  Copyright (c) 2014 Phil Jordan. All rights reserved.
//

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
