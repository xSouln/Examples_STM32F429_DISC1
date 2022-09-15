//==============================================================================
#include "Carousel_AdapterBase.h"
//==============================================================================
static void Handler(void* device)
{
	
}
//------------------------------------------------------------------------------
static void EventListener(void* device, CarouselAdapterEventSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : break;
	}
}
//------------------------------------------------------------------------------
static xResult RequestListener(void* device, CarouselAdapterRequestSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : return xResultRequestIsNotFound;
	}
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
static uint32_t GetValue(void* device, CarouselAdapterValueSelector selector)
{
	switch ((int)selector)
	{
		default : break;
	}
	
	return 0;
}
//------------------------------------------------------------------------------
static xResult SetValue(void* device, CarouselAdapterValueSelector selector, uint32_t value)
{
	switch ((int)selector)
	{
		default : return xResultValueIsNotFound;
	}
	
	return xResultAccept;
}
//==============================================================================
static CarouselAdapterInterfaceT Interface =
{
	.Handler = (CarouselAdapterHandlerT)Handler,
	.EventListener = (CarouselAdapterEventListenerT)EventListener,
	.RequestListener = (CarouselAdapterRequestListenerT)RequestListener,
	.GetValue = (CarouselAdapterActionGetValueT)GetValue,
	.SetValue = (CarouselAdapterActionSetValueT)SetValue,
};
//------------------------------------------------------------------------------
xResult CarouselAdapterBaseInit(CarouselAdapterBaseT* adapter)
{
	if (adapter)
	{
		adapter->Interface = &Interface;
	}
	return xResultAccept;
}
//==============================================================================