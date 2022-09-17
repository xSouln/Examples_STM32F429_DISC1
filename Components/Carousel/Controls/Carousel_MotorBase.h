//==============================================================================
#ifndef _CAROUSEL_MOTOR_BASE_H
#define _CAROUSEL_MOTOR_BASE_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "Common/xTypes.h"
//==============================================================================
typedef enum
{
	CarouselMotorEventIdle,
	CarouselMotorEventPositionIsSet
	
} CarouselMotorEventSelector;
//------------------------------------------------------------------------------
typedef enum
{
	CarouselMotorRequestIdle,
	CarouselMotorRequestSetPosition,
	CarouselMotorRequestSetOptions,
	CarouselMotorRequestClearPosition,
	CarouselMotorRequestStop,
	CarouselMotorRequestDelay
	
} CarouselMotorRequestSelector;
//------------------------------------------------------------------------------
typedef enum
{
	CarouselMotorValueIdle,
	CarouselMotorValueMotionState,
	CarouselMotorValueOptions,
	CarouselMotorValueMoveTime,
	CarouselMotorValueStepPosition,
	CarouselMotorValueRequestStepPosition,
	
} CarouselMotorValueSelector;
//------------------------------------------------------------------------------
typedef void (*CarouselMotorHandlerT)(void* device);

typedef void (*CarouselMotorEventListenerT)(void* device, CarouselMotorEventSelector selector, uint32_t args, uint32_t count);
typedef xResult (*CarouselMotorRequestListenerT)(void* device, CarouselMotorRequestSelector selector, uint32_t args, uint32_t count);

typedef uint32_t (*CarouselMotorActionGetValueT)(void* device, CarouselMotorValueSelector selector);
typedef xResult (*CarouselMotorActionSetValueT)(void* device, CarouselMotorValueSelector selector, uint32_t value);
//------------------------------------------------------------------------------
typedef struct
{
	CarouselMotorHandlerT Handler;
	
	CarouselMotorEventListenerT EventListener;
	CarouselMotorRequestListenerT RequestListener;
	
	CarouselMotorActionGetValueT GetValue;
	CarouselMotorActionSetValueT SetValue;
	
} CarouselMotorInterfaceT;
//------------------------------------------------------------------------------
typedef struct
{
	OBJECT_HEADER;
	
	void* Child;
	CarouselMotorInterfaceT* Interface;
	
} CarouselMotorBaseT;
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif