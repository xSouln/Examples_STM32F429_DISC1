//==============================================================================
#include "BrewGroup_MotorBase.h"
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
xResult BrewGroupMotorBaseInit(BrewGroupMotorBaseT* adapter, void* parent)
{
	if (adapter)
	{
		adapter->Description = "BrewGroupMotorBaseT";
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