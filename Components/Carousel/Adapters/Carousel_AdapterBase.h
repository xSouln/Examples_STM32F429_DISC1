//==============================================================================
#ifndef _CAROUSEL_ADAPTER_BASE_H
#define _CAROUSEL_ADAPTER_BASE_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "Common/xTypes.h"
//==============================================================================
typedef enum
{
	CarouselAdapterEventIdle,
	CarouselAdapterEventPositionIsSet
	
} CarouselAdapterEventSelector;
//------------------------------------------------------------------------------
typedef enum
{
	CarouselAdapterRequestIdle,
	CarouselAdapterRequestSetPosition,
	CarouselAdapterRequestSetOptions,
	CarouselAdapterRequestClearPosition,
	CarouselAdapterRequestStop,
	CarouselAdapterRequestDelay
	
} CarouselAdapterRequestSelector;
//------------------------------------------------------------------------------
typedef enum
{
	CarouselAdapterValueIdle,
	CarouselAdapterValueMotionState,
	CarouselAdapterValueOptions,
	CarouselAdapterValueMoveTime,
	CarouselAdapterValueStepPosition,
	CarouselAdapterValueRequestStepPosition,
	
} CarouselAdapterValueSelector;
//------------------------------------------------------------------------------
typedef void (*CarouselAdapterHandlerT)(void* device);

typedef void (*CarouselAdapterEventListenerT)(void* device, CarouselAdapterEventSelector selector, uint32_t args, uint32_t count);
typedef xResult (*CarouselAdapterRequestListenerT)(void* device, CarouselAdapterRequestSelector selector, uint32_t args, uint32_t count);

typedef uint32_t (*CarouselAdapterActionGetValueT)(void* device, CarouselAdapterValueSelector selector);
typedef xResult (*CarouselAdapterActionSetValueT)(void* device, CarouselAdapterValueSelector selector, uint32_t value);
//------------------------------------------------------------------------------
typedef struct
{
	CarouselAdapterHandlerT Handler;
	
	CarouselAdapterEventListenerT EventListener;
	CarouselAdapterRequestListenerT RequestListener;
	
	CarouselAdapterActionGetValueT GetValue;
	CarouselAdapterActionSetValueT SetValue;
	
} CarouselAdapterInterfaceT;
//------------------------------------------------------------------------------
typedef struct
{
	OBJECT_HEADER;
	
	void* Child;
	CarouselAdapterInterfaceT* Interface;
	
} CarouselAdapterBaseT;
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif