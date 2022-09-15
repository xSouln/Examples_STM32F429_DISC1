//==============================================================================
#include "BrewGroup_DCMotorAdapter.h"
#include "BrewGroup/Controls/BrewGroup.h"
//==============================================================================
static void Handler(void* device)
{
	
}
//------------------------------------------------------------------------------
static void EventListener(void* device, BrewGroupMotorEventSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : break;
	}
}
//------------------------------------------------------------------------------
static xResult RequestListener(void* device, BrewGroupMotorRequestSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : return xResultRequestIsNotFound;
	}
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
static uint32_t GetValue(void* device, BrewGroupMotorValueSelector selector)
{
	switch ((int)selector)
	{
		default : break;
	}
	
	return 0;
}
//------------------------------------------------------------------------------
static xResult SetValue(void* device, BrewGroupMotorValueSelector selector, uint32_t value)
{
	switch ((int)selector)
	{
		default : return xResultValueIsNotFound;
	}
	
	return xResultAccept;
}
//==============================================================================
xResult BrewGroupDCMotorAdapterInit(BrewGroupT* device, BrewGroupDCMotorAdapterT* adapter)
{
	if (device && adapter)
	{
		device->Motor.Description = "BrewGroupDCMotorAdapterT";
		device->Motor.Parent = device;
		device->Motor.Child = adapter;
		
		device->Motor.Interface.Handler = Handler;
		device->Motor.Interface.EventListener = EventListener;
		device->Motor.Interface.RequestListener = RequestListener;
		device->Motor.Interface.GetValue = GetValue;
		device->Motor.Interface.SetValue = SetValue;
		
		return xResultAccept;
	}
	return xResultInvalidParameter;
}
//==============================================================================
