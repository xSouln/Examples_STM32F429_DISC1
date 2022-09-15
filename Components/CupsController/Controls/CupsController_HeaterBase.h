//==============================================================================
#ifndef _CUPS_CONTROLLER_HEATER_BASE_H
#define _CUPS_CONTROLLER_HEATER_BASE_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "Common/xTypes.h"
//==============================================================================
typedef enum
{
	CupsControllerHeaterEventIdle,
	
} CupsControllerHeaterEventSelector;
//------------------------------------------------------------------------------
typedef enum
{
	CupsControllerHeaterRequestIdle,
	
} CupsControllerHeaterRequestSelector;
//------------------------------------------------------------------------------
typedef enum
{
	CupsControllerHeaterValueIdle,
	
} CupsControllerHeaterValueSelector;
//------------------------------------------------------------------------------
typedef void (*CupsControllerHeaterHandlerT)(void* device);

typedef void (*CupsControllerHeaterEventListenerT)(void* device, CupsControllerHeaterEventSelector selector, uint32_t args, uint32_t count);
typedef xResult (*CupsControllerHeaterRequestListenerT)(void* device, CupsControllerHeaterRequestSelector selector, uint32_t args, uint32_t count);

typedef uint32_t (*CupsControllerHeaterActionGetValueT)(void* device, CupsControllerHeaterValueSelector selector);
typedef xResult (*CupsControllerHeaterActionSetValueT)(void* device, CupsControllerHeaterValueSelector selector, uint32_t value);
//------------------------------------------------------------------------------
typedef struct
{
	CupsControllerHeaterHandlerT Handler;
	
	CupsControllerHeaterEventListenerT EventListener;
	CupsControllerHeaterRequestListenerT RequestListener;
	
	CupsControllerHeaterActionGetValueT GetValue;
	CupsControllerHeaterActionSetValueT SetValue;
	
} CupsControllerHeaterInterfaceT;
//------------------------------------------------------------------------------
typedef struct
{
	OBJECT_HEADER;
	
	void* Child;
	CupsControllerHeaterInterfaceT Interface;
	
} CupsControllerHeaterBaseT;
//==============================================================================
xResult CupsControllerHeaterBaseInit(CupsControllerHeaterBaseT* adapter, void* parent);
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif