//==============================================================================
#include "BrewGroup_SensorsBase.h"
#include "BrewGroup.h"
//==============================================================================
static void Handler(void* device)
{
	
}
//------------------------------------------------------------------------------
static xResult RequestListener(void* device, BrewGroupSensorsRequestSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : return xResultRequestIsNotFound;
	}
	
	return xResultAccept;
}
//==============================================================================
void BrewGroupSensorsHandler(BrewGroupT* device)
{
	device->Sensors.Interface.Handler(device);
}
//==============================================================================
xResult BrewGroupSensorsBaseInit(BrewGroupSensorsBaseT* adapter, void* parent)
{
	if (adapter)
	{
		adapter->Description = "BrewGroupWaterPumpBaseT";
		adapter->Parent = parent;
		adapter->Child = 0;
		
		adapter->Interface.Handler = Handler;
		adapter->Interface.RequestListener = RequestListener;
		
		return xResultAccept;
	}
	
	return xResultLinkError;
}
//==============================================================================