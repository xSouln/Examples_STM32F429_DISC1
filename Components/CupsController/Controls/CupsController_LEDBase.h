//==============================================================================
#ifndef _CUPS_CONTROLLER_LED_BASE_H
#define _CUPS_CONTROLLER_LED_BASE_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "Common/xTypes.h"
//==============================================================================
typedef enum
{
	CupsControllerLEDEventIdle,
	
} CupsControllerLEDEventSelector;
//------------------------------------------------------------------------------
typedef enum
{
	CupsControllerLEDRequestIdle,
	CupsControllerLEDRequestFillPixels,
	CupsControllerLEDRequestSetPixel,
	CupsControllerLEDRequestWritePixels
	
} CupsControllerLEDRequestSelector;
//------------------------------------------------------------------------------
typedef enum
{
	CupsControllerLEDValueIdle,
	
} CupsControllerLEDValueSelector;
//------------------------------------------------------------------------------
typedef void (*CupsControllerLEDHandlerT)(void* device);

typedef void (*CupsControllerLEDEventListenerT)(void* device, CupsControllerLEDEventSelector selector, uint32_t args, uint32_t count);
typedef xResult (*CupsControllerLEDRequestListenerT)(void* device, CupsControllerLEDRequestSelector selector, uint32_t args, uint32_t count);

typedef uint32_t (*CupsControllerLEDActionGetValueT)(void* device, CupsControllerLEDValueSelector selector);
typedef xResult (*CupsControllerLEDActionSetValueT)(void* device, CupsControllerLEDValueSelector selector, uint32_t value);
//------------------------------------------------------------------------------
typedef struct
{
	CupsControllerLEDHandlerT Handler;
	
	CupsControllerLEDEventListenerT EventListener;
	CupsControllerLEDRequestListenerT RequestListener;
	
	CupsControllerLEDActionGetValueT GetValue;
	CupsControllerLEDActionSetValueT SetValue;
	
} CupsControllerLEDInterfaceT;
//------------------------------------------------------------------------------
typedef struct
{
	OBJECT_HEADER;
	
	void* Child;
	CupsControllerLEDInterfaceT Interface;
	
} CupsControllerLEDBaseT;
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif