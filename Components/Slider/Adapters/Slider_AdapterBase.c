//==============================================================================
#include "Slider_AdapterBase.h"
//==============================================================================
static void Handler(void* device)
{
	
}
//------------------------------------------------------------------------------
static void EventListener(void* device, SliderAdapterEventSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : break;
	}
}
//------------------------------------------------------------------------------
static xResult RequestListener(void* device, SliderAdapterRequestSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : return xResultRequestIsNotFound;
	}
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
static uint32_t GetValue(void* device, SliderAdapterValueSelector selector)
{
	switch ((int)selector)
	{
		default : break;
	}
	
	return 0;
}
//------------------------------------------------------------------------------
static xResult SetValue(void* device, SliderAdapterValueSelector selector, uint32_t value)
{
	switch ((int)selector)
	{
		default : return xResultValueIsNotFound;
	}
	
	return xResultAccept;
}
//==============================================================================
static SliderAdapterInterfaceT Interface =
{
	.Handler = (SliderAdapterHandlerT)Handler,
	.EventListener = (SliderAdapterEventListenerT)EventListener,
	.RequestListener = (SliderAdapterRequestListenerT)RequestListener,
	.GetValue = (SliderAdapterActionGetValueT)GetValue,
	.SetValue = (SliderAdapterActionSetValueT)SetValue,
};
//------------------------------------------------------------------------------
xResult SliderAdapterBaseInit(SliderAdapterBaseT* adapter)
{
	if (adapter)
	{
		adapter->Interface = &Interface;
	}
	return xResultAccept;
}
//==============================================================================