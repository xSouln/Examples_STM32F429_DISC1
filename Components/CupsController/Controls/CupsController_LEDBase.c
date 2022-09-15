//==============================================================================
#include "CupsController_LEDBase.h"
//==============================================================================
static void Handler(void* device)
{
	
}
//------------------------------------------------------------------------------
static void EventListener(void* device, CupsControllerLEDEventSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : break;
	}
}
//------------------------------------------------------------------------------
static xResult RequestListener(void* device, CupsControllerLEDRequestSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : return xResultRequestIsNotFound;
	}
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
static uint32_t GetValue(void* device, CupsControllerLEDValueSelector selector)
{
	switch ((int)selector)
	{
		default : break;
	}
	
	return 0;
}
//------------------------------------------------------------------------------
static xResult SetValue(void* device, CupsControllerLEDValueSelector selector, uint32_t value)
{
	switch ((int)selector)
	{
		default : return xResultValueIsNotFound;
	}
	
	return xResultAccept;
}
//==============================================================================
static CupsControllerLEDInterfaceT Interface =
{
	.Handler = (CupsControllerLEDHandlerT)Handler,
	.EventListener = (CupsControllerLEDEventListenerT)EventListener,
	.RequestListener = (CupsControllerLEDRequestListenerT)RequestListener,
	.GetValue = (CupsControllerLEDActionGetValueT)GetValue,
	.SetValue = (CupsControllerLEDActionSetValueT)SetValue,
};
//------------------------------------------------------------------------------
xResult CupsControllerLEDBaseInit(CupsControllerLEDBaseT* adapter, void* parent)
{
	if (adapter)
	{
		adapter->Description = "CupsControllerLEDBaseT";
		adapter->Parent = parent;
		adapter->Child = 0;
		
		adapter->Interface.Handler = (CupsControllerLEDHandlerT)Handler;
		adapter->Interface.EventListener = (CupsControllerLEDEventListenerT)EventListener;
		adapter->Interface.RequestListener = (CupsControllerLEDRequestListenerT)RequestListener;
		adapter->Interface.GetValue = (CupsControllerLEDActionGetValueT)GetValue;
		adapter->Interface.SetValue = (CupsControllerLEDActionSetValueT)SetValue;
		
		return xResultAccept;
	}
	
	return xResultLinkError;
}
//==============================================================================