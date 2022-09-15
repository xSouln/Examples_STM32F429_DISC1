//==============================================================================
#include "BrewGroup_WaterPumpAdapter.h"
#include "BrewGroup/Controls/BrewGroup.h"
//==============================================================================
static void Handler(BrewGroupT* device)
{
	
}
//------------------------------------------------------------------------------
static void EventListener(BrewGroupT* device, BrewGroupWaterPumpEventSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : break;
	}
}
//------------------------------------------------------------------------------
static xResult RequestListener(BrewGroupT* device, BrewGroupWaterPumpRequestSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : return xResultRequestIsNotFound;
	}
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
static uint32_t GetValue(BrewGroupT* device, BrewGroupWaterPumpValueSelector selector)
{
	switch ((int)selector)
	{
		default : break;
	}
	
	return 0;
}
//------------------------------------------------------------------------------
static xResult SetValue(BrewGroupT* device, BrewGroupWaterPumpValueSelector selector, uint32_t value)
{
	switch ((int)selector)
	{
		default : return xResultValueIsNotFound;
	}
	
	return xResultAccept;
}
//==============================================================================
xResult BrewGroupWaterPumpAdapterInit(BrewGroupT* device, BrewGroupWaterPumpAdapterT* adapter)
{
	if (device && adapter)
	{
		device->WaterPump.Description = "BrewGroupWaterPumpAdapterT";
		device->WaterPump.Parent = device;
		device->WaterPump.Child = adapter;
		
		device->WaterPump.Interface.Handler = (BrewGroupWaterPumpHandlerT)Handler;
		device->WaterPump.Interface.EventListener = (BrewGroupWaterPumpEventListenerT)EventListener;
		device->WaterPump.Interface.RequestListener = (BrewGroupWaterPumpRequestListenerT)RequestListener;
		device->WaterPump.Interface.GetValue = (BrewGroupWaterPumpActionGetValueT)GetValue;
		device->WaterPump.Interface.SetValue = (BrewGroupWaterPumpActionSetValueT)SetValue;
		
		return xResultAccept;
	}
	return xResultInvalidParameter;
}
//==============================================================================
