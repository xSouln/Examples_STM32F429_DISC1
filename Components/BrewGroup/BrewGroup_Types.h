//==============================================================================
#ifndef _BREW_GROUP_TYPES_H
#define _BREW_GROUP_TYPES_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
 extern "C" {
#endif 
//==============================================================================
#include "Common/xTypes.h"
#include "Common/xRxTransaction.h"
#include "BrewGroup_Config.h"
#include "BrewGroup/Controls/BrewGroup_MotorBase.h"
#include "BrewGroup/Controls/BrewGroup_ThermostatBase.h"
#include "BrewGroup/Controls/BrewGroup_WaterPumpBase.h"
#include "BrewGroup/Controls/BrewGroup_SensorsBase.h"
//==============================================================================
typedef enum
{
	BrewGroupEventIdle,
	BrewGroupEventOpen,
	BrewGroupEventStartMove,
	BrewGroupEventClose,
	BrewGroupEventTimeout,
	BrewGroupEventOvercurrent,
	BrewGroupEventStatusChanged
	
} BrewGroupEventSelector;
//------------------------------------------------------------------------------
typedef enum
{
	BrewGroupRequestIdle,
	BrewGroupRequestDelay
	
} BrewGroupRequestSelector;
//------------------------------------------------------------------------------
typedef enum
{
	BrewGroupValueIdle,
	
} BrewGroupValueSelector;
//------------------------------------------------------------------------------
typedef void (*BrewGroupEventListenerT)(void* device, BrewGroupEventSelector event, uint32_t args, uint32_t count);
typedef xResult (*BrewGroupRequestListenerT)(void* device, BrewGroupRequestSelector event, uint32_t args, uint32_t count);

//typedef uint32_t (*BrewGroupActionGetValueT)(void* device, BrewGroupValueSelector event, uint32_t args, uint32_t count);
//typedef xResult (*BrewGroupActionSetValueT)(void* device, BrewGroupValueSelector event, uint32_t args, uint32_t count);
//------------------------------------------------------------------------------
typedef struct
{
	BrewGroupEventListenerT EventListener;
	BrewGroupRequestListenerT RequestListener;
	
	//BrewGroupActionGetValueT GetValue;
	//BrewGroupActionSetValueT SetValue;
	
} BrewGroupInterfaceT;
//==============================================================================
typedef union
{
	struct
	{
		uint64_t InitResult : 4;
	};
	
	uint64_t Value;
	
} BrewGroupStatusT;
//------------------------------------------------------------------------------
typedef struct
{
	OBJECT_HEADER;
	
	BrewGroupInterfaceT* Interface;
	
	BrewGroupMotorBaseT Motor;
	BrewGroupTermostatBaseT Termostat;
	BrewGroupWaterPumpBaseT WaterPump;
	BrewGroupSensorsBaseT Sensors;
	
	BrewGroupStatusT Status;
	
	xRxRequestT* Requests;
	
} BrewGroupT;
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif
