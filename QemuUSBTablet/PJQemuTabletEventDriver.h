//
//  PJQemuTabletEventDriver.h
//  QemuUSBTablet
//
//  Created by Phil Jordan on 10/07/2014.
//  Copyright (c) 2014 Phil Jordan. All rights reserved.
//

#ifndef __QemuUSBTablet__PJQemuTabletEventDriver__
#define __QemuUSBTablet__PJQemuTabletEventDriver__

#include <IOKit/hidevent/IOHIDEventDriver.h>

#define PJQemuUSBTableEventDriver eu_philjordan_driver_QemuUSBTableEventDriver

class PJQemuUSBTableEventDriver : public IOHIDEventService
{
	OSDeclareDefaultStructors(PJQemuUSBTableEventDriver);

private:
    IOHIDInterface *            _interface;
    IOHIDReportHandler *        _reportHandlers;
    
    IOHIDElement *              _ledElements[2];
    OSArray *                   _supportedElements;
        
    UInt32                      _bootSupport;
    bool                        _multipleReports;
    bool                        _relativeButtonCollection;
    UInt32                      _cachedButtonState;
    bool                        _cachedRangeState;
    
    struct ExpansionData { 
    };
    /*! @var reserved
        Reserved for future use.  (Internal use only)  */
    ExpansionData *             _reserved;
    
    bool                    findElements ( OSArray * elementArray, UInt32 bootProtocol );
    
    bool                    storeReportElement ( IOHIDElement * element );

    void                    handleBootPointingReport (
                                IOMemoryDescriptor *        report,
                                SInt32 *                    dX,
                                SInt32 *                    dY,
                                UInt32 *                    buttonState);
    
    static void             _handleInterruptReport (
                                OSObject *                  target,
                                AbsoluteTime                timeStamp,
                                IOMemoryDescriptor *        report,
                                IOHIDReportType             reportType,
                                UInt32                      reportID,
                                void *                      refcon);
    
protected:

    virtual void            free();
    
    virtual OSArray *       getReportElements();
    
    virtual bool            handleStart( IOService * provider );

    virtual void            handleStop(  IOService * provider );
    
    virtual void            handleInterruptReport (
                                AbsoluteTime                timeStamp,
                                IOMemoryDescriptor *        report,
                                IOHIDReportType             reportType,
                                UInt32                      reportID);

    virtual OSString *      getTransport ();

    virtual UInt32          getLocationID ();

    virtual UInt32          getVendorID ();

    virtual UInt32          getVendorIDSource ();

    virtual UInt32          getProductID ();

    virtual UInt32          getVersion ();

    virtual UInt32          getCountryCode ();

    virtual OSString *      getManufacturer ();

    virtual OSString *      getProduct ();

    virtual OSString *      getSerialNumber ();

    virtual void            setElementValue (
                                UInt32                      usagePage,
                                UInt32                      usage,
                                UInt32                      value );
    
    virtual UInt32          getElementValue ( 
                                UInt32                      usagePage,
                                UInt32                      usage );

public:


    virtual bool            init( OSDictionary * dictionary = 0 );

    virtual bool            didTerminate(
                                IOService *                 provider,
                                IOOptionBits                options,
                                bool *                      defer );
  
};

#endif /* defined(__QemuUSBTablet__PJQemuTabletEventDriver__) */
