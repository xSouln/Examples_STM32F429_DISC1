//==============================================================================
#ifndef _CUPS_CONTROLLER_FLOW_DIRECTOR_BASE_H
#define _CUPS_CONTROLLER_FLOW_DIRECTOR_BASE_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "Common/xTypes.h"
//==============================================================================
typedef enum
{
	CupsControllerFlowDirectorEventIdle,
	
} CupsControllerFlowDirectorEventSelector;
//------------------------------------------------------------------------------
typedef enum
{
	CupsControllerFlowDirectorRequestIdle,
	
} CupsControllerFlowDirectorRequestSelector;
//------------------------------------------------------------------------------
typedef enum
{
	CupsControllerFlowDirectorValueIdle,
	
} CupsControllerFlowDirectorValueSelector;
//------------------------------------------------------------------------------
typedef void (*CupsControllerFlowDirectorHandlerT)(void* device);

typedef void (*CupsControllerFlowDirectorEventListenerT)(void* device, CupsControllerFlowDirectorEventSelector selector, uint32_t args, uint32_t count);
typedef xResult (*CupsControllerFlowDirectorRequestListenerT)(void* device, CupsControllerFlowDirectorRequestSelector selector, uint32_t args, uint32_t count);

typedef uint32_t (*CupsControllerFlowDirectorActionGetValueT)(void* device, CupsControllerFlowDirectorValueSelector selector);
typedef xResult (*CupsControllerFlowDirectorActionSetValueT)(void* device, CupsControllerFlowDirectorValueSelector selector, uint32_t value);
//------------------------------------------------------------------------------
typedef struct
{
	CupsControllerFlowDirectorHandlerT Handler;
	
	CupsControllerFlowDirectorEventListenerT EventListener;
	CupsControllerFlowDirectorRequestListenerT RequestListener;
	
	CupsControllerFlowDirectorActionGetValueT GetValue;
	CupsControllerFlowDirectorActionSetValueT SetValue;
	
} CupsControllerFlowDirectorInterfaceT;
//------------------------------------------------------------------------------
typedef struct
{
	OBJECT_HEADER;
	
	void* Child;
	CupsControllerFlowDirectorInterfaceT Interface;
	
} CupsControllerFlowDirectorBaseT;
//==============================================================================
xResult CupsControllerFlowDirectorBaseInit(CupsControllerFlowDirectorBaseT* adapter, void* parent);
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif