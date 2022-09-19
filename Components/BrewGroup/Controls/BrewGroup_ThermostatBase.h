//==============================================================================
#ifndef _BREW_GROUP_TERMOSTAT_BASE_H
#define _BREW_GROUP_TERMOSTAT_BASE_H
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
	BrewGroupTermostatEventIdle,
	
} BrewGroupTermostatEventSelector;
//------------------------------------------------------------------------------
typedef enum
{
	BrewGroupTermostatRequestIdle,
	
} BrewGroupTermostatRequestSelector;
//------------------------------------------------------------------------------
typedef enum
{
	BrewGroupTermostatValueIdle,
	
} BrewGroupTermostatValueSelector;
//------------------------------------------------------------------------------
typedef void (*BrewGroupTermostatHandlerT)(void* device);

typedef void (*BrewGroupTermostatEventListenerT)(void* device, BrewGroupTermostatEventSelector selector, uint32_t args, uint32_t count);
typedef xResult (*BrewGroupTermostatRequestListenerT)(void* device, BrewGroupTermostatRequestSelector selector, uint32_t args, uint32_t count);

typedef uint32_t (*BrewGroupTermostatActionGetValueT)(void* device, BrewGroupTermostatValueSelector selector);
typedef xResult (*BrewGroupTermostatActionSetValueT)(void* device, BrewGroupTermostatValueSelector selector, uint32_t value);
//------------------------------------------------------------------------------
typedef struct
{
	BrewGroupTermostatHandlerT Handler;
	
	BrewGroupTermostatEventListenerT EventListener;
	BrewGroupTermostatRequestListenerT RequestListener;
	
	BrewGroupTermostatActionGetValueT GetValue;
	BrewGroupTermostatActionSetValueT SetValue;
	
} BrewGroupTermostatInterfaceT;
//------------------------------------------------------------------------------
typedef union
{
	struct
	{
		uint32_t IsEnable : 1;
	};
	
	uint32_t Value;
	
} BrewGroupTermostatStatusT;
//------------------------------------------------------------------------------
typedef struct
{
	float Level;
	
} BrewGroupTermostatOptionsT;
//------------------------------------------------------------------------------
typedef struct
{
	OBJECT_HEADER;
	
	void* Child;
	BrewGroupTermostatInterfaceT Interface;
	
	BrewGroupTermostatOptionsT Options;
	
	float TotalTemperature;
	float RequestTemperature;
	
} BrewGroupTermostatBaseT;
//==============================================================================
xResult BrewGroupTermostatBaseInit(BrewGroupTermostatBaseT* adapter, void* parent);
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif