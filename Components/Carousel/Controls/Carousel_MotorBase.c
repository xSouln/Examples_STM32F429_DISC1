//==============================================================================
#include "Carousel_MotorBase.h"
//==============================================================================
static void Handler(void* device)
{
	
}
//------------------------------------------------------------------------------
static void EventListener(void* device, CarouselMotorEventSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : break;
	}
}
//------------------------------------------------------------------------------
static xResult RequestListener(void* device, CarouselMotorRequestSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : return xResultRequestIsNotFound;
	}
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
static uint32_t GetValue(void* device, CarouselMotorValueSelector selector)
{
	switch ((int)selector)
	{
		default : break;
	}
	
	return 0;
}
//------------------------------------------------------------------------------
static xResult SetValue(void* device, CarouselMotorValueSelector selector, uint32_t value)
{
	switch ((int)selector)
	{
		default : return xResultValueIsNotFound;
	}
	
	return xResultAccept;
}
//==============================================================================
static CarouselMotorInterfaceT Interface =
{
	.Handler = (CarouselMotorHandlerT)Handler,
	.EventListener = (CarouselMotorEventListenerT)EventListener,
	.RequestListener = (CarouselMotorRequestListenerT)RequestListener,
	.GetValue = (CarouselMotorActionGetValueT)GetValue,
	.SetValue = (CarouselMotorActionSetValueT)SetValue,
};
//------------------------------------------------------------------------------
xResult CarouselMotorBaseInit(CarouselMotorBaseT* adapter)
{
	if (adapter)
	{
		adapter->Interface = &Interface;
	}
	return xResultAccept;
}
//==============================================================================