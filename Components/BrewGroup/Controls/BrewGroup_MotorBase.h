//==============================================================================
#ifndef _BREW_GROUP_MOTOR_BASE_H
#define _BREW_GROUP_MOTOR_BASE_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "Common/xTypes.h"
//==============================================================================
typedef enum
{
	BrewGroupMotorEventIdle,
	
} BrewGroupMotorEventSelector;
//------------------------------------------------------------------------------
typedef enum
{
	BrewGroupMotorRequestIdle,
	BrewGroupMotorRequestSetPosition,
	BrewGroupMotorRequestSetOptions,
	BrewGroupMotorRequestClearPosition,
	BrewGroupMotorRequestStop,
	BrewGroupMotorRequestDelay
	
} BrewGroupMotorRequestSelector;
//------------------------------------------------------------------------------
typedef enum
{
	BrewGroupMotorValueIdle,
	BrewGroupMotorValueMotionState,
	BrewGroupMotorValueOptions,
	BrewGroupMotorValueMoveTime,
	BrewGroupMotorValueStepPosition,
	BrewGroupMotorValueRequestStepPosition,
	
} BrewGroupMotorValueSelector;
//------------------------------------------------------------------------------
typedef void (*BrewGroupMotorHandlerT)(void* device);

typedef void (*BrewGroupMotorEventListenerT)(void* device, BrewGroupMotorEventSelector selector, uint32_t args, uint32_t count);
typedef xResult (*BrewGroupMotorRequestListenerT)(void* device, BrewGroupMotorRequestSelector selector, uint32_t args, uint32_t count);

typedef uint32_t (*BrewGroupMotorActionGetValueT)(void* device, BrewGroupMotorValueSelector selector);
typedef xResult (*BrewGroupMotorActionSetValueT)(void* device, BrewGroupMotorValueSelector selector, uint32_t value);
//------------------------------------------------------------------------------
typedef struct
{
	BrewGroupMotorHandlerT Handler;
	
	BrewGroupMotorEventListenerT EventListener;
	BrewGroupMotorRequestListenerT RequestListener;
	
	BrewGroupMotorActionGetValueT GetValue;
	BrewGroupMotorActionSetValueT SetValue;
	
} BrewGroupMotorInterfaceT;
//------------------------------------------------------------------------------
typedef struct
{
	OBJECT_HEADER;
	
	void* Child;
	BrewGroupMotorInterfaceT Interface;
	
} BrewGroupMotorBaseT;
//==============================================================================
xResult BrewGroupMotorBaseInit(BrewGroupMotorBaseT* adapter, void* parent);
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif