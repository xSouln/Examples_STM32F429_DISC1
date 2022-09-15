//==============================================================================
#include "BrewGroup_ThermostatAdapter.h"
#include "BrewGroup/Controls/BrewGroup.h"
//==============================================================================
static void Handler(BrewGroupT* device)
{
	
}
//------------------------------------------------------------------------------
static void EventListener(BrewGroupT* device, BrewGroupTermostatEventSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : break;
	}
}
//------------------------------------------------------------------------------
static xResult RequestListener(BrewGroupT* device, BrewGroupTermostatRequestSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : return xResultRequestIsNotFound;
	}
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
static uint32_t GetValue(BrewGroupT* device, BrewGroupTermostatValueSelector selector)
{
	switch ((int)selector)
	{
		default : break;
	}
	
	return 0;
}
//------------------------------------------------------------------------------
static xResult SetValue(BrewGroupT* device, BrewGroupTermostatValueSelector selector, uint32_t value)
{
	switch ((int)selector)
	{
		default : return xResultValueIsNotFound;
	}
	
	return xResultAccept;
}
//==============================================================================
xResult BrewGroupTermostatAdapterInit(BrewGroupT* device, BrewGroupTermostatAdapterT* adapter)
{
	if (device && adapter)
	{
		device->Termostat.Description = "BrewGroupTermostatAdapterT";
		device->Termostat.Parent = device;
		device->Termostat.Child = adapter;
		
		device->Termostat.Interface.Handler = (BrewGroupTermostatHandlerT)Handler;
		device->Termostat.Interface.EventListener = (BrewGroupTermostatEventListenerT)EventListener;
		device->Termostat.Interface.RequestListener = (BrewGroupTermostatRequestListenerT)RequestListener;
		device->Termostat.Interface.GetValue = (BrewGroupTermostatActionGetValueT)GetValue;
		device->Termostat.Interface.SetValue = (BrewGroupTermostatActionSetValueT)SetValue;
		
		return xResultAccept;
	}
	return xResultInvalidParameter;
}
//==============================================================================
