//
//  PJQemuUSBTabletDriver.cpp
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

#include "PJQemuUSBTabletDriver.h"

#define super IOUSBHIDDriver

OSDefineMetaClassAndStructors(PJQemuUSBTabletDriver, IOUSBHIDDriver)

static const uint8_t expected_descriptor_start[] =
{
	0x05, 0x01,		/* Usage Page (Generic Desktop) */
	0x09, 0x01,		/* Usage (Pointer) */
	0xa1, 0x01,		/* Collection (Application) */
};

IOMemoryMap* PJQemuUSBTabletDriver::mapDescriptorIfExpected(IOMemoryDescriptor* desc)
{
	if (desc->getLength() >= sizeof(expected_descriptor_start))
	{
		IOMemoryMap* mapping = desc->createMappingInTask(kernel_task, 0, kIOMapReadOnly | kIOMapAnywhere);
		if (mapping)
		{
			const void* descriptor_bytes = reinterpret_cast<const void*>(mapping->getAddress());
			if (0 == memcmp(descriptor_bytes, expected_descriptor_start, sizeof(expected_descriptor_start)))
			{
				return mapping;
			}
			mapping->release();
		}
	}
	return NULL;
}


IOReturn PJQemuUSBTabletDriver::newReportDescriptor(IOMemoryDescriptor** descriptor) const
{
	if (!descriptor)
		return kIOReturnBadArgument;
	
	IOMemoryDescriptor* desc = NULL;
	IOReturn result = super::newReportDescriptor(&desc);
	if (result == kIOReturnSuccess && desc)
	{
		IOMemoryMap* mapping = mapDescriptorIfExpected(desc);
		
		if (mapping)
		{
			IOBufferMemoryDescriptor* buffer = IOBufferMemoryDescriptor::withCapacity(desc->getLength(), kIODirectionOutIn);
			if (buffer)
			{
				const void* descriptor_bytes = reinterpret_cast<const void*>(mapping->getAddress());
				memcpy(buffer->getBytesNoCopy(), descriptor_bytes, desc->getLength());
				uint8_t* buffer_bytes = static_cast<uint8_t*>(buffer->getBytesNoCopy());
				buffer_bytes[3] = 0x02; // set usage to "mouse", which causes IOHIDEventDriver to deal with the device correctly
				*descriptor = buffer;
			}
			else
			{
				result = kIOReturnNoMemory;
			}
			mapping->release();
		}
		else
		{
			result = kIOReturnDeviceError;
		}
	}
	OSSafeReleaseNULL(desc);
	return result;
}
