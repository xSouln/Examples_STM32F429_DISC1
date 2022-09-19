//==============================================================================
#include <string.h>
#include "BrewGroup.h"
//==============================================================================
extern void BrewGroupMotorDisable(BrewGroupT* device);
//==============================================================================
void BrewGroupHandler(BrewGroupT* BrewGroup)
{
	BrewGroup->Sensors.Interface.Handler(BrewGroup);
	BrewGroup->Motor.Interface->Handler(BrewGroup);
}
//==============================================================================
xResult BrewGroupSetMotorOptions(BrewGroupT* device, BrewGroupMotorOptionsT* request)
{
	if (device->Motor.Status.Motion == BrewGroupMotionStateStopped)
	{
		memcpy(&device->Motor.Options, request, sizeof(device->Motor.Options));
		return xResultAccept;
	}
	return xResultBusy;
}
//------------------------------------------------------------------------------
void BrewGroupStop(BrewGroupT* device)
{
	BrewGroupMotorDisable(device);
	device->Motor.Status.MotionResult = BrewGroupMotionNoError;
}
//------------------------------------------------------------------------------
xResult BrewGroupSetPosition(BrewGroupT* device, BrewGroupMoveRequestT* request)
{
	device->Sensors.Interface.Handler(device);
	
	if (device->Sensors.State.Overcurrent)
	{
		device->Motor.Status.MotionResult = BrewGroupMotionOvercurrent;
		return xResultError;
	}
	
	if ((device->Sensors.State.Close && request->Position == BrewGroupPositionClose)
		|| (device->Sensors.State.Open && request->Position == BrewGroupPositionOpen))
	{
		return xResultAccept;
	}
	
	BrewGroupMotorDisable(device);
	
	return device->Motor.Interface->RequestListener(device, BrewGroupMotorRequestMoveStart, (uint32_t)request, 0);
}
//------------------------------------------------------------------------------
xResult BrewGroupClose(BrewGroupT* device)
{
	BrewGroupMoveRequestT request =
	{
		.Power = BREW_GROUP_DEFAULT_MOVE_POWER,
		.Mode = BrewGroupMoveModeCommon,
		.TimeOut = BREW_GROUP_DEFAULT_TIMEOUT,
		.Position = BrewGroupPositionClose
	};
	
	return BrewGroupSetPosition(device, &request);
}
//------------------------------------------------------------------------------
xResult BrewGroupOpen(BrewGroupT* device)
{
	BrewGroupMoveRequestT request =
	{
		.Power = BREW_GROUP_DEFAULT_MOVE_POWER,
		.Mode = BrewGroupMoveModeCommon,
		.TimeOut = BREW_GROUP_DEFAULT_TIMEOUT,
		.Position = BrewGroupPositionOpen
	};
	
	return BrewGroupSetPosition(device, &request);
}
//==============================================================================
xResult BrewGroupInit(BrewGroupT* BrewGroup, void* parent, BrewGroupInterfaceT* interface)
{
	extern const xRxRequestT BrewGroupRequests[];
	
	if (BrewGroup && interface)
	{
		BrewGroup->Description = "BrewGroupT";
		BrewGroup->Parent = parent;
		BrewGroup->Interface = interface;
		
		BrewGroup->Requests = (xRxRequestT*)BrewGroupRequests;
		
		return xResultAccept;
	}
	return xResultLinkError;
}
//==============================================================================
