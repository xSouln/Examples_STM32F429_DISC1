//==============================================================================
#ifndef _FLOW_DIRECTOR_MOTOR_BASE_H
#define _FLOW_DIRECTOR_MOTOR_BASE_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "Common/xTypes.h"
//==============================================================================
typedef enum
{
	FlowDirectorMotorEventIdle,
	
} FlowDirectorMotorEventSelector;
//------------------------------------------------------------------------------
typedef enum
{
	FlowDirectorMotorRequestIdle,
	FlowDirectorMotorRequestSetPosition,
	FlowDirectorMotorRequestSetOptions,
	FlowDirectorMotorRequestClearPosition,
	FlowDirectorMotorRequestStop,
	FlowDirectorMotorRequestDelay
	
} FlowDirectorMotorRequestSelector;
//------------------------------------------------------------------------------
typedef enum
{
	FlowDirectorMotorValueIdle,
	FlowDirectorMotorValueMotionState,
	FlowDirectorMotorValueOptions,
	FlowDirectorMotorValueMoveTime,
	FlowDirectorMotorValueStepPosition,
	FlowDirectorMotorValueRequestStepPosition,
	
} FlowDirectorMotorValueSelector;
//------------------------------------------------------------------------------
typedef void (*FlowDirectorMotorHandlerT)(void* device);

typedef void (*FlowDirectorMotorEventListenerT)(void* device, FlowDirectorMotorEventSelector selector, uint32_t args, uint32_t count);
typedef xResult (*FlowDirectorMotorRequestListenerT)(void* device, FlowDirectorMotorRequestSelector selector, uint32_t args, uint32_t count);

typedef uint32_t (*FlowDirectorMotorActionGetValueT)(void* device, FlowDirectorMotorValueSelector selector);
typedef xResult (*FlowDirectorMotorActionSetValueT)(void* device, FlowDirectorMotorValueSelector selector, uint32_t value);
//------------------------------------------------------------------------------
typedef struct
{
	FlowDirectorMotorHandlerT Handler;
	
	FlowDirectorMotorEventListenerT EventListener;
	FlowDirectorMotorRequestListenerT RequestListener;
	
	FlowDirectorMotorActionGetValueT GetValue;
	FlowDirectorMotorActionSetValueT SetValue;
	
} FlowDirectorMotorInterfaceT;
//------------------------------------------------------------------------------
typedef struct
{
	OBJECT_HEADER;
	
	void* Child;
	FlowDirectorMotorInterfaceT Interface;
	
} FlowDirectorMotorBaseT;
//==============================================================================
xResult FlowDirectorMotorBaseInit(FlowDirectorMotorBaseT* adapter, void* parent);
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif