//==============================================================================
#ifndef _SLIDER_ADAPTER_BASE_H
#define _SLIDER_ADAPTER_BASE_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "Common/xTypes.h"
//==============================================================================
typedef enum
{
	SliderAdapterEventIdle,
	
} SliderAdapterEventSelector;
//------------------------------------------------------------------------------
typedef enum
{
	SliderAdapterRequestIdle,
	SliderAdapterRequestOpen,
	SliderAdapterRequestClose,
	SliderAdapterRequestStop,
	SliderAdapterRequestDelay
	
} SliderAdapterRequestSelector;
//------------------------------------------------------------------------------
typedef enum
{
	SliderAdapterValueIdle,
	SliderAdapterValueMotionState,
	SliderAdapterValueOptions,
	SliderAdapterValueMoveTime,
	
} SliderAdapterValueSelector;
//------------------------------------------------------------------------------
typedef void (*SliderAdapterHandlerT)(void* device);

typedef void (*SliderAdapterEventListenerT)(void* device, SliderAdapterEventSelector selector, uint32_t args, uint32_t count);
typedef xResult (*SliderAdapterRequestListenerT)(void* device, SliderAdapterRequestSelector selector, uint32_t args, uint32_t count);

typedef uint32_t (*SliderAdapterActionGetValueT)(void* device, SliderAdapterValueSelector selector);
typedef xResult (*SliderAdapterActionSetValueT)(void* device, SliderAdapterValueSelector selector, uint32_t value);
//------------------------------------------------------------------------------
typedef struct
{
	SliderAdapterHandlerT Handler;
	
	SliderAdapterEventListenerT EventListener;
	SliderAdapterRequestListenerT RequestListener;
	
	SliderAdapterActionGetValueT GetValue;
	SliderAdapterActionSetValueT SetValue;
	
} SliderAdapterInterfaceT;
//------------------------------------------------------------------------------
typedef struct
{
	OBJECT_HEADER;
	
	void* Child;
	SliderAdapterInterfaceT* Interface;
	
} SliderAdapterBaseT;
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif