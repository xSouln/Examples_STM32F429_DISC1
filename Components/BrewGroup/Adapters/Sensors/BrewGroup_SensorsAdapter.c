//==============================================================================
#include "BrewGroup_SensorsAdapter.h"
#include "BrewGroup/Controls/BrewGroup.h"
//==============================================================================
static void Handler(BrewGroupT* device)
{
	BrewGroupSensorsAdapterT* adapter = device->Sensors.Child;
	BrewGroupSensorsStateT sensors_state = { 0 };
	
	device->Sensors.LastState.Value = device->Sensors.State.Value;
	
	sensors_state.Open = (adapter->SensorOpenPort->IDR & adapter->SensorOpenPin) > 0;
	sensors_state.Open = sensors_state.Open == adapter->SensorOpenOnStateLogicLevel;
	
	sensors_state.Close = (adapter->SensorClosePort->IDR & adapter->SensorClosePin) > 0;
	sensors_state.Close = sensors_state.Close == adapter->SensorCloseOnStateLogicLevel;
	
	sensors_state.Overcurrent = (adapter->SensorOvercurrentPort->IDR & adapter->SensorOvercurrentPin) > 0;
	sensors_state.Overcurrent = sensors_state.Overcurrent == adapter->SensorOvercurrentOnStateLogicLevel;
	
	device->Sensors.State.Value = sensors_state.Value;
}
//------------------------------------------------------------------------------
static xResult RequestListener(BrewGroupT* device, BrewGroupSensorsRequestSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		case BrewGroupSensorsRequestUpdateState:
			Handler(device);
			break;
			
		default : return xResultRequestIsNotFound;
	}
	
	return xResultAccept;
}
//==============================================================================
xResult BrewGroupSensorsAdapterInit(BrewGroupT* device, BrewGroupSensorsAdapterT* adapter)
{
	if (device && adapter)
	{
		device->Sensors.Description = "BrewGroupSensorsAdapterT";
		device->Sensors.Parent = device;
		device->Sensors.Child = adapter;
		
		device->Sensors.Interface.Handler = (BrewGroupSensorsHandlerT)Handler;
		device->Sensors.Interface.RequestListener = (BrewGroupSensorsRequestListenerT)RequestListener;
		
		return xResultAccept;
	}
	return xResultInvalidParameter;
}
//==============================================================================
