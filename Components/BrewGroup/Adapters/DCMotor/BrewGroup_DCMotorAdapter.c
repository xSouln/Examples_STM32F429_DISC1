//==============================================================================
#include "BrewGroup_DCMotorAdapter.h"
#include "BrewGroup/Controls/BrewGroup.h"
//==============================================================================
static void DisablePWMOutputs(BrewGroupDCMotorAdapterT* adapter)
{
	adapter->PWM_ForwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_Forward.OutputEnableMask;
	adapter->PWM_BackwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_Backward.OutputEnableMask;
}
//==============================================================================
static void Handler(BrewGroupT* device)
{
	BrewGroupDCMotorAdapterT* adapter = device->Motor.Child;
	
	if (adapter->PWM_ForwardTimer->CaptureCompareOutput.Value & adapter->Values.PWM_Forward.OutputEnableMask)
	{
		device->Motor.Status.Motion = BrewGroupMotionStateOpening;
	}
	else if (adapter->PWM_BackwardTimer->CaptureCompareOutput.Value & adapter->Values.PWM_Backward.OutputEnableMask)
	{
		device->Motor.Status.Motion = BrewGroupMotionStateClosing;
	}
	else
	{
		device->Motor.Status.Motion = BrewGroupMotionStateStopped;
	}
	
}
//------------------------------------------------------------------------------
static void EventListener(BrewGroupT* device, BrewGroupMotorEventSelector selector, uint32_t args, uint32_t count)
{
	BrewGroupDCMotorAdapterT* adapter = device->Motor.Child;
	
	switch ((int)selector)
	{
		default : break;
	}
}
//------------------------------------------------------------------------------
static xResult BrewGroupMotorSetPosition(BrewGroupT* device, BrewGroupMoveRequestT* request)
{
	extern void BrewGroupMotorBaseSetPosition(BrewGroupT* device, BrewGroupMoveRequestT* request);
	
	BrewGroupDCMotorAdapterT* adapter = device->Motor.Child;
	
	BrewGroupMotorBaseSetPosition(device, request);
	
	switch ((uint8_t)request->Position)
	{
		case BrewGroupPositionOpen:
			adapter->Values.SelectedPWM = &adapter->Values.PWM_Forward;
			break;
		
		case BrewGroupPositionClose:
			adapter->Values.SelectedPWM = &adapter->Values.PWM_Backward;
			break;
		
		default : break;
	}
	
	uint16_t power = (uint16_t)(device->Motor.TotalPower / 100 * adapter->Values.SelectedPWM->Timer->Period);
	*adapter->Values.SelectedPWM->CompareValue = power;
	adapter->Values.SelectedPWM->Timer->CaptureCompareOutput.Value |= adapter->Values.SelectedPWM->OutputEnableMask;
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
static xResult RequestListener(BrewGroupT* device, BrewGroupMotorRequestSelector selector, uint32_t args, uint32_t count)
{
	BrewGroupDCMotorAdapterT* adapter = device->Motor.Child;
	
	switch ((int)selector)
	{
		case BrewGroupMotorRequestSetPower:
			if (adapter->Values.SelectedPWM)
			{
				*adapter->Values.SelectedPWM->CompareValue = (uint16_t)((device->Motor.TotalPower / 100 * adapter->Values.SelectedPWM->Timer->Period) - 1);
			}
			break;
		
		case BrewGroupMotorRequestMoveStart:
			return BrewGroupMotorSetPosition(device, (BrewGroupMoveRequestT*)args);
		
		case BrewGroupMotorRequestMoveStope:
			DisablePWMOutputs(adapter);
			break;
		
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
};
//==============================================================================
xResult BrewGroupDCMotorAdapterInit(BrewGroupT* BrewGroup, BrewGroupDCMotorAdapterT* adapter)
{
	if (BrewGroup && adapter)
	{
		BrewGroup->Motor.Description = "BrewGroupDCMotorAdapterT";
		BrewGroup->Motor.Parent = BrewGroup;
		BrewGroup->Motor.Child = adapter;
		BrewGroup->Motor.Interface = &Interface;
		
		adapter->Values.PWM_Backward.Timer = adapter->PWM_BackwardTimer;
		adapter->Values.PWM_Backward.OutputEnableMask = (1 << (adapter->PWM_BackwardChannel * 4));
		adapter->Values.PWM_Backward.CompareValue = &adapter->PWM_BackwardTimer->CaptureCompare1Value + adapter->PWM_BackwardChannel;
		
		adapter->Values.PWM_Forward.Timer = adapter->PWM_ForwardTimer;
		adapter->Values.PWM_Forward.OutputEnableMask = (1 << (adapter->PWM_ForwardChannel * 4));
		adapter->Values.PWM_Forward.CompareValue = &adapter->PWM_ForwardTimer->CaptureCompare1Value + adapter->PWM_ForwardChannel;
		
		adapter->PWM_BackwardTimer->BreakAndDeadTime.MainOutputEnable = true;
		adapter->PWM_ForwardTimer->BreakAndDeadTime.MainOutputEnable = true;
		
		adapter->PWM_BackwardTimer->Control1.CounterEnable = true;
		adapter->PWM_ForwardTimer->Control1.CounterEnable = true;
		
		return xResultAccept;
	}
	return xResultInvalidParameter;
}
//==============================================================================
