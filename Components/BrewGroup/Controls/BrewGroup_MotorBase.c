//==============================================================================
#include "BrewGroup_MotorBase.h"
#include "BrewGroup.h"
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
//==============================================================================
static BrewGroupMotorInterfaceT Interface =
{
	.Handler = (BrewGroupMotorHandlerT)Handler,
	.EventListener = (BrewGroupMotorEventListenerT)EventListener,
	.RequestListener = (BrewGroupMotorRequestListenerT)RequestListener,
	//.GetValue = (BrewGroupMotorActionGetValueT)GetValue,
	//.SetValue = (BrewGroupMotorActionSetValueT)SetValue,
};
//==============================================================================
void BrewGroupMotorDisable(BrewGroupT* device)
{
	device->Motor.Interface->RequestListener(device, BrewGroupMotorRequestMoveStope, 0, 0);
	device->Motor.Status.Motion = BrewGroupMotionStateStopped;
}
//------------------------------------------------------------------------------
void BrewGroupMotorBaseSetPosition(BrewGroupT* device, BrewGroupMoveRequestT* request)
{
	switch ((uint8_t)request->Position)
	{
		case BrewGroupPositionOpen:
			device->Motor.Triggers.Open = false;
			device->Motor.Status.Motion = BrewGroupMotionStateOpening;
			break;
		
		case BrewGroupPositionClose:
			device->Motor.Triggers.Close = false;
			device->Motor.Status.Motion = BrewGroupMotionStateClosing;
			break;
		
		default : break;
	}
	
	device->Motor.TotalPower = device->Motor.Options.StartPower;
	device->Motor.RequestPower = request->Power;
	device->Motor.Status.MotionResult = BrewGroupMotionNoError;
	device->Motor.TimeOut = request->TimeOut;
	device->Motor.MoveTime = 0;
	device->Motor.Mode = request->Mode;
	device->Motor.AccelerationIncrement = device->Motor.Options.Acceleration / 1000;
	
	if (device->Motor.RequestPower > 100.0)
	{
		device->Motor.RequestPower = 100.0;
	}
	
	if (device->Motor.TotalPower > device->Motor.RequestPower)
	{
		device->Motor.TotalPower = device->Motor.RequestPower;
	}
}
//==============================================================================
void BrewGroupMotorHandler(BrewGroupT* device)
{
	device->Motor.Interface->Handler(device);
	
	if (device->Sensors.State.Overcurrent)
	{
		BrewGroupMotorDisable(device);
		
		if (device->Motor.Status.MotionResult != BrewGroupMotionOvercurrent)
		{
			device->Motor.Status.MotionResult = BrewGroupMotionOvercurrent;
			device->Interface->EventListener(device, BrewGroupEventOvercurrent, 0, 0);
		}
	}
	
	if (device->Motor.Status.Motion == BrewGroupMotionStateOpening)
	{
		if (!device->Sensors.State.Close && device->Motor.Mode == BrewGroupMoveModeMoveOffTheSensor)
		{
			BrewGroupMotorDisable(device);
		}
		else if (device->Sensors.State.Open)
		{
			BrewGroupMotorDisable(device);
		
			if (!device->Motor.Triggers.Open)
			{
				device->Motor.Triggers.Open = true;
				device->Interface->EventListener(device, BrewGroupEventOpen, 0, 0);
			}
		}
	}
	else if (device->Motor.Status.Motion == BrewGroupMotionStateClosing)
	{
		if (device->Sensors.State.Close || (!device->Sensors.State.Open && device->Motor.Mode == BrewGroupMoveModeMoveOffTheSensor))
		{
			BrewGroupMotorDisable(device);
		
			if (!device->Motor.Triggers.Close)
			{
				device->Motor.Triggers.Close = true;
				device->Interface->EventListener(device, BrewGroupEventClose, 0, 0);
			}
		}
	}
	
	if (device->Motor.Status.Motion != BrewGroupMotionStateStopped)
	{
		device->Motor.MoveTime++;
		
		if (device->Motor.MoveTime >= device->Motor.TimeOut)
		{
			BrewGroupMotorDisable(device);
			
			device->Motor.Status.MotionResult = BrewGroupMotionTimeout;
			device->Interface->EventListener(device, BrewGroupEventTimeout, 0, 0);
			return;
		}
		
		if (device->Motor.TotalPower < device->Motor.RequestPower)
		{
			device->Motor.TotalPower += device->Motor.AccelerationIncrement;
			device->Motor.Interface->RequestListener(device, BrewGroupMotorRequestSetPower, 0, 0);
		}
	}
}
//------------------------------------------------------------------------------
xResult BrewGroupMotorBaseInit(BrewGroupMotorBaseT* adapter)
{
	if (adapter)
	{
		adapter->Interface = &Interface;
	}
	return xResultAccept;
}
//==============================================================================
