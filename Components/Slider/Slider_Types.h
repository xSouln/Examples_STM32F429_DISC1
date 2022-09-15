//==============================================================================
#ifndef _SLIDER_TYPES_H
#define _SLIDER_TYPES_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
 extern "C" {
#endif 
//==============================================================================
#include "Common/xTypes.h"
#include "Common/xRxTransaction.h"
#include "Slider_Config.h"
#include "Adapters/Slider_AdapterBase.h"
//==============================================================================
typedef enum
{
	SliderEventIdle,
	SliderEventOpen,
	SliderEventStartMove,
	SliderEventClose,
	SliderEventTimeout,
	SliderEventOvercurrent
	
} SliderEventSelector;
//------------------------------------------------------------------------------
typedef enum
{
	SliderRequestIdle,
	SliderRequestDelay
	
} SliderRequestSelector;
//------------------------------------------------------------------------------
typedef enum
{
	SliderValueIdle,
	
} SliderValueSelector;
//------------------------------------------------------------------------------
typedef void (*SliderEventListenerT)(void* device, SliderEventSelector event, uint32_t args, uint32_t count);
typedef xResult (*SliderRequestListenerT)(void* device, SliderRequestSelector event, uint32_t args, uint32_t count);

//typedef uint32_t (*SliderActionGetValueT)(void* device, SliderValueSelector event, uint32_t args, uint32_t count);
//typedef xResult (*SliderActionSetValueT)(void* device, SliderValueSelector event, uint32_t args, uint32_t count);
//------------------------------------------------------------------------------
typedef struct
{
	SliderEventListenerT EventListener;
	SliderRequestListenerT RequestListener;
	
	//SliderActionGetValueT GetValue;
	//SliderActionSetValueT SetValue;
	
} SliderInterfaceT;
//==============================================================================
typedef enum
{
	SliderMotionNoError,
	SliderPositionSettingTimeout,
	SliderOvercurrent,
	
} SliderMotionErrors;
//------------------------------------------------------------------------------
typedef enum
{
	SliderStateIdle,
	SliderStateOpening,
	SliderStateClosing,
	SliderStateIsOpen,
	SliderStateIsClose
	
} SliderStates;
//------------------------------------------------------------------------------
typedef enum
{
	SliderSensorClose = 1 << 0,
	SliderSensorOpen = 1 << 1,
	SliderSensorOvercurrent = 1 << 2
	
} SliderSensors;
//------------------------------------------------------------------------------
typedef union
{
	struct
	{
		SliderSensors Close : 1;
		SliderSensors Open : 1;
		SliderSensors Overcurrent : 1;
	};
	
	SliderSensors Value;
	
} SliderSensorsT;
//------------------------------------------------------------------------------
typedef union
{
	struct
	{
		SliderSensors Sensors : 4;
		
		SliderStates State : 4;
		SliderMotionErrors Errors : 4;
		
		xResult InitResult : 4;
		xResult DriverInitResult : 4;
		xResult AdapterInitResult : 4;
	};
	
	uint32_t Value;
	
} SliderStatusT;
//------------------------------------------------------------------------------
typedef struct
{
	uint16_t Acceleration;
	uint16_t StartPower;
	
} SliderOptionsT;
//------------------------------------------------------------------------------
typedef struct
{
	uint16_t TotalPower;
	uint16_t RequestPower;
	uint32_t MoveTime;
	
} SliderValuesT;
//------------------------------------------------------------------------------
typedef struct
{
	uint16_t Power;
	uint32_t TimeOut;
	
} SliderMoveRequestT;
//------------------------------------------------------------------------------
typedef struct
{
	OBJECT_HEADER;
	
	SliderAdapterBaseT Adapter;
	SliderInterfaceT* Interface;
	
	SliderStatusT Status;
	SliderOptionsT Options;
	SliderValuesT Values;
	
	xRxRequestT* Requests;
	xRxT* RxLine;
	
} SliderT;
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif
