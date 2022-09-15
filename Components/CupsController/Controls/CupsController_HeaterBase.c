//==============================================================================
#include "CupsController_HeaterBase.h"
//==============================================================================
static void Handler(void* device)
{
	
}
//------------------------------------------------------------------------------
static void EventListener(void* device, CupsControllerHeaterEventSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : break;
	}
}
//------------------------------------------------------------------------------
static xResult RequestListener(void* device, CupsControllerHeaterRequestSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : return xResultRequestIsNotFound;
	}
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
static uint32_t GetValue(void* device, CupsControllerHeaterValueSelector selector)
{
	switch ((int)selector)
	{
		default : break;
	}
	
	return 0;
}
//------------------------------------------------------------------------------
static xResult SetValue(void* device, CupsControllerHeaterValueSelector selector, uint32_t value)
{
	switch ((int)selector)
	{
		default : return xResultValueIsNotFound;
	}
	
	return xResultAccept;
}
//==============================================================================
xResult CupsControllerHeaterBaseInit(CupsControllerHeaterBaseT* adapter, void* parent)
{
	if (adapter)
	{
		adapter->Description = "CupsControllerHeaterBaseT";
		adapter->Parent = parent;
		adapter->Child = 0;
		
		adapter->Interface.Handler = Handler;
		adapter->Interface.EventListener = EventListener;
		adapter->Interface.RequestListener = RequestListener;
		adapter->Interface.GetValue = GetValue;
		adapter->Interface.SetValue = SetValue;
		
		return xResultAccept;
	}
	
	return xResultLinkError;
}
//==============================================================================