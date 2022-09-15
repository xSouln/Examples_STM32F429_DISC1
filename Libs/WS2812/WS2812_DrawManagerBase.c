//==============================================================================
#include "WS2812_DrawManagerBase.h"
//==============================================================================
static void Handler(void* device)
{
	
}
//------------------------------------------------------------------------------
static void EventListener(void* device, WS2812_DrawManagerEventSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : break;
	}
}
//------------------------------------------------------------------------------
static xResult RequestListener(void* device, WS2812_DrawManagerRequestSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : return xResultRequestIsNotFound;
	}
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
static uint32_t GetValue(void* device, WS2812_DrawManagerValueSelector selector)
{
	switch ((int)selector)
	{
		default : break;
	}
	
	return 0;
}
//------------------------------------------------------------------------------
static xResult SetValue(void* device, WS2812_DrawManagerValueSelector selector, uint32_t value)
{
	switch ((int)selector)
	{
		default : return xResultValueIsNotFound;
	}
	
	return xResultAccept;
}
//==============================================================================
static WS2812_DrawManagerInterfaceT Interface =
{
	.Handler = (WS2812_DrawManagerHandlerT)Handler,
	.EventListener = (WS2812_DrawManagerEventListenerT)EventListener,
	.RequestListener = (WS2812_DrawManagerRequestListenerT)RequestListener,
	.GetValue = (WS2812_DrawManagerActionGetValueT)GetValue,
	.SetValue = (WS2812_DrawManagerActionSetValueT)SetValue,
};
//------------------------------------------------------------------------------
xResult WS2812_DrawManagerBaseInit(WS2812_DrawManagerBaseT* base, void* parent)
{
	if (base)
	{
		base->Description = "WS2812_DrawManagerBaseT";
		base->Parent = parent;
		base->Child = 0;
		
		base->Interface.Handler = Handler;
		base->Interface.EventListener = EventListener;
		base->Interface.RequestListener = RequestListener;
		base->Interface.GetValue = GetValue;
		base->Interface.SetValue = SetValue;
	}
	return xResultAccept;
}
//==============================================================================
void WS2812_DrawManagerHandler(WS2812_DrawManagerBaseT* base)
{
	if (base->Status.DrawingIsEnable)
	{
		base->Interface.Handler(base);
	}
}
//------------------------------------------------------------------------------
xResult WS2812_DrawingStart(WS2812_DrawManagerBaseT* base)
{
	xResult result = base->Interface.RequestListener(base, WS2812_DrawManagerRequestDrawingStart, 0, 0);
		
	base->Status.DrawingIsEnable = result == xResultAccept;
	return result;
}
//------------------------------------------------------------------------------
void WS2812_DrawingStop(WS2812_DrawManagerBaseT* base)
{
	base->Status.DrawingIsEnable = false;
	base->Interface.RequestListener(base, WS2812_DrawManagerRequestDrawingStop, 0, 0);
}
//------------------------------------------------------------------------------
xResult WS2812_DrawManagerSetTemplate(WS2812_DrawManagerBaseT* base, void* value)
{
	return base->Interface.RequestListener(base, WS2812_DrawManagerRequestSetTemplate, (uint32_t)value, 0);
}
//==============================================================================