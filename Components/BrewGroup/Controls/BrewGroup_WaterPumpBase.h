//==============================================================================
#ifndef _BREW_GROUP_WATER_PUMP_BASE_H
#define _BREW_GROUP_WATER_PUMP_BASE_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "Common/xTypes.h"
//==============================================================================
typedef enum
{
	BrewGroupWaterPumpEventIdle,
	
} BrewGroupWaterPumpEventSelector;
//------------------------------------------------------------------------------
typedef enum
{
	BrewGroupWaterPumpRequestIdle,
	BrewGroupWaterPumpRequestSetPosition,
	BrewGroupWaterPumpRequestSetOptions,
	BrewGroupWaterPumpRequestClearPosition,
	BrewGroupWaterPumpRequestStop,
	BrewGroupWaterPumpRequestDelay
	
} BrewGroupWaterPumpRequestSelector;
//------------------------------------------------------------------------------
typedef enum
{
	BrewGroupWaterPumpValueIdle,
	BrewGroupWaterPumpValueMotionState,
	BrewGroupWaterPumpValueOptions,
	BrewGroupWaterPumpValueMoveTime,
	BrewGroupWaterPumpValueStepPosition,
	BrewGroupWaterPumpValueRequestStepPosition,
	
} BrewGroupWaterPumpValueSelector;
//------------------------------------------------------------------------------
typedef void (*BrewGroupWaterPumpHandlerT)(void* device);

typedef void (*BrewGroupWaterPumpEventListenerT)(void* device, BrewGroupWaterPumpEventSelector selector, uint32_t args, uint32_t count);
typedef xResult (*BrewGroupWaterPumpRequestListenerT)(void* device, BrewGroupWaterPumpRequestSelector selector, uint32_t args, uint32_t count);

typedef uint32_t (*BrewGroupWaterPumpActionGetValueT)(void* device, BrewGroupWaterPumpValueSelector selector);
typedef xResult (*BrewGroupWaterPumpActionSetValueT)(void* device, BrewGroupWaterPumpValueSelector selector, uint32_t value);
//------------------------------------------------------------------------------
typedef struct
{
	BrewGroupWaterPumpHandlerT Handler;
	
	BrewGroupWaterPumpEventListenerT EventListener;
	BrewGroupWaterPumpRequestListenerT RequestListener;
	
	BrewGroupWaterPumpActionGetValueT GetValue;
	BrewGroupWaterPumpActionSetValueT SetValue;
	
} BrewGroupWaterPumpInterfaceT;
//------------------------------------------------------------------------------
typedef struct
{
	OBJECT_HEADER;
	
	void* Child;
	BrewGroupWaterPumpInterfaceT Interface;
	
} BrewGroupWaterPumpBaseT;
//==============================================================================
xResult BrewGroupWaterPumpBaseInit(BrewGroupWaterPumpBaseT* adapter, void* parent);
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif