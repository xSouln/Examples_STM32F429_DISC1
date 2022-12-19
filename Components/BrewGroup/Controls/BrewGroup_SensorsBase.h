//==============================================================================
#ifndef _BREW_GROUP_SENSORS_BASE_H
#define _BREW_GROUP_SENSORS_BASE_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "Common/xTypes.h"
#include "Components_Config.h"
//==============================================================================
typedef enum
{
	BrewGroupSensorspEventIdle,
	
} BrewGroupSensorsEventSelector;
//------------------------------------------------------------------------------
typedef enum
{
	BrewGroupSensorsRequestIdle,
	BrewGroupSensorsRequestUpdateState
	
} BrewGroupSensorsRequestSelector;
//------------------------------------------------------------------------------
typedef enum
{
	BrewGroupSensorsValueIdle,
	
} BrewGroupSensorsValueSelector;
//------------------------------------------------------------------------------
typedef void (*BrewGroupSensorsHandlerT)(void* device);
typedef xResult (*BrewGroupSensorsRequestListenerT)(void* device, BrewGroupSensorsRequestSelector selector, uint32_t args, uint32_t count);
//------------------------------------------------------------------------------
typedef struct
{
	BrewGroupSensorsHandlerT Handler;
	BrewGroupSensorsRequestListenerT RequestListener;
	
} BrewGroupSensorsInterfaceT;
//------------------------------------------------------------------------------
typedef enum
{
	BrewGroupSensorClose = 1 << 0,
	BrewGroupSensorOpen = 1 << 1,
	BrewGroupSensorOvercurrent = 1 << 2
	
} BrewGroupSensors;
//------------------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t Close : 1;
		uint8_t Open : 1;
		uint8_t Overcurrent : 1;
	};
	
	BrewGroupSensors Value;
	
} BrewGroupSensorsStateT;
//------------------------------------------------------------------------------
typedef struct
{
	OBJECT_HEADER;
	
	void* Child;
	BrewGroupSensorsInterfaceT Interface;
	
	BrewGroupSensorsStateT State;
	BrewGroupSensorsStateT LastState;
	
} BrewGroupSensorsBaseT;
//==============================================================================
xResult BrewGroupSensorsBaseInit(BrewGroupSensorsBaseT* adapter, void* parent);
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif
