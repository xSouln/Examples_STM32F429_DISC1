//==============================================================================
#ifndef _FLOW_DIRECTOR_TYPES_H
#define _FLOW_DIRECTOR_TYPES_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
 extern "C" {
#endif 
//==============================================================================
#include "Common/xTypes.h"
#include "Common/xRxTransaction.h"
#include "Components_Config.h"
#include "FlowDirector_Config.h"
#include "FlowDirector/Controls/FlowDirector_MotorBase.h"
//==============================================================================
typedef enum
{
	FlowDirectorEventIdle,
	
} FlowDirectorEventSelector;
//------------------------------------------------------------------------------
typedef enum
{
	FlowDirectorRequestIdle,
	FlowDirectorRequestDelay
	
} FlowDirectorRequestSelector;
//------------------------------------------------------------------------------
typedef enum
{
	FlowDirectorValueIdle,
	
} FlowDirectorValueSelector;
//------------------------------------------------------------------------------
typedef void (*FlowDirectorEventListenerT)(void* device, FlowDirectorEventSelector event, uint32_t args, uint32_t count);
typedef xResult (*FlowDirectorRequestListenerT)(void* device, FlowDirectorRequestSelector event, uint32_t args, uint32_t count);

//typedef uint32_t (*FlowDirectorActionGetValueT)(void* device, FlowDirectorValueSelector event, uint32_t args, uint32_t count);
//typedef xResult (*FlowDirectorActionSetValueT)(void* device, FlowDirectorValueSelector event, uint32_t args, uint32_t count);
//------------------------------------------------------------------------------
typedef struct
{
	FlowDirectorEventListenerT EventListener;
	FlowDirectorRequestListenerT RequestListener;
	
	//FlowDirectorActionGetValueT GetValue;
	//FlowDirectorActionSetValueT SetValue;
	
} FlowDirectorInterfaceT;
//==============================================================================
typedef union
{
	struct
	{
		uint64_t Sensors : 4;
		uint64_t Motion : 4;
		uint64_t Errors : 3;
		
		uint64_t InitResult : 4;
		uint64_t DriverInitResult : 4;
		uint64_t AdapterInitResult : 4;
	};
	
	uint64_t Value;
	
} FlowDirectorStatusT;
//------------------------------------------------------------------------------
typedef struct
{
	OBJECT_HEADER;
	
	FlowDirectorInterfaceT* Interface;
	
	FlowDirectorMotorBaseT Motor;
	
	FlowDirectorStatusT Status;
	
	xRxRequestT* Requests;
	
} FlowDirectorT;
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif
