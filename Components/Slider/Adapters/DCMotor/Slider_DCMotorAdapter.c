//==============================================================================
#include "Slider_DCMotorAdapter.h"
#include "Slider/Controls/Slider.h"
//==============================================================================
static void Stop(SliderT* device);
//==============================================================================
static void UpdateSensors(SliderT* device)
{
	SliderDCMotorAdapterT* adapter = device->Adapter.Child;
	SliderSensorsT sensors_state;
	
	sensors_state.Open = (adapter->SensorOpenPort->IDR & adapter->SensorOpenPin) > 0;
	sensors_state.Open = sensors_state.Open == adapter->SensorOpenOnStateLogicLevel;
	
	sensors_state.Close = (adapter->SensorClosePort->IDR & adapter->SensorClosePin) > 0;
	sensors_state.Close = sensors_state.Close == adapter->SensorClosingOnStateLogicLevel;
	
	sensors_state.Overcurrent = (adapter->SensorOvercurrentPort->IDR & adapter->SensorOvercurrentPin) > 0;
	sensors_state.Overcurrent = sensors_state.Overcurrent == adapter->SensorOvercurrentOnStateLogicLevel;
	
	device->Status.Sensors = sensors_state.Value;
}
//------------------------------------------------------------------------------
static void Handler(SliderT* device)
{
	SliderDCMotorAdapterT* adapter = device->Adapter.Child;
	SliderSensorsT sensors_state;
	
	sensors_state.Open = (adapter->SensorOpenPort->IDR & adapter->SensorOpenPin) > 0;
	sensors_state.Open = sensors_state.Open == adapter->SensorOpenOnStateLogicLevel;
	
	sensors_state.Close = (adapter->SensorClosePort->IDR & adapter->SensorClosePin) > 0;
	sensors_state.Close = sensors_state.Close == adapter->SensorClosingOnStateLogicLevel;
	
	sensors_state.Overcurrent = (adapter->SensorOvercurrentPort->IDR & adapter->SensorOvercurrentPin) > 0;
	sensors_state.Overcurrent = sensors_state.Overcurrent == adapter->SensorOvercurrentOnStateLogicLevel;
	
	device->Status.Sensors = sensors_state.Value;
	
	if (sensors_state.Overcurrent)
	{
		adapter->PWM_ForwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_ForwardOutputEnableMask;
		adapter->PWM_BackwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_BackwardOutputEnableMask;
		
		if (device->Status.Errors != SliderOvercurrent)
		{
			device->Status.Errors = SliderOvercurrent;
			device->Interface->EventListener(device, SliderEventOvercurrent, device->Status.State, 0);
		}
	}
	
	if (adapter->PWM_ForwardTimer->CaptureCompareOutput.Value & adapter->Values.PWM_ForwardOutputEnableMask)
	{
		device->Status.State = SliderStateOpening;
	}
	else if (adapter->PWM_BackwardTimer->CaptureCompareOutput.Value & adapter->Values.PWM_BackwardOutputEnableMask)
	{
		device->Status.State = SliderStateClosing;
	}
	
	if (sensors_state.Open)
	{
		adapter->PWM_ForwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_ForwardOutputEnableMask;
		device->Status.State = SliderStateIsOpen;
		
		if (!adapter->Values.Events.Open)
		{
			adapter->Values.Events.Open = true;
			device->Interface->EventListener(device, SliderEventOpen, device->Status.State, 0);
		}
	}
	else if (sensors_state.Close)
	{
		adapter->PWM_BackwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_BackwardOutputEnableMask;
		device->Status.State = SliderStateIsClose;
		
		if (!adapter->Values.Events.Close)
		{
			adapter->Values.Events.Close = true;
			device->Interface->EventListener(device, SliderEventClose, device->Status.State, 0);
		}
	}
	
	if (device->Status.State == SliderStateOpening || device->Status.State == SliderStateClosing)
	{
		device->Values.MoveTime++;
		
		if (device->Values.MoveTime >= adapter->Values.TimeOut)
		{
			adapter->PWM_ForwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_ForwardOutputEnableMask;
			adapter->PWM_BackwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_BackwardOutputEnableMask;
			
			device->Status.Errors = SliderPositionSettingTimeout;
			device->Interface->EventListener(device, SliderEventTimeout, device->Status.State, 0);
		}
	}
	
	end:;
}
//------------------------------------------------------------------------------
static void EventListener(SliderT* device, SliderAdapterEventSelector selector, uint32_t args, uint32_t count)
{
	SliderDCMotorAdapterT* adapter = device->Adapter.Child;
	
	switch ((int)selector)
	{
		default : break;
	}
}
//------------------------------------------------------------------------------
static xResult SetOptions(SliderT* device, SliderOptionsT* request)
{
	SliderDCMotorAdapterT* adapter = device->Adapter.Child;
	
	if (!device || !request)
	{
		return xResultLinkError;
	}
	
	return xResultBusy;
}
//------------------------------------------------------------------------------
static void Stop(SliderT* device)
{
	SliderDCMotorAdapterT* adapter = device->Adapter.Child;
	
	adapter->PWM_ForwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_ForwardOutputEnableMask;
	adapter->PWM_BackwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_BackwardOutputEnableMask;
	
	device->Status.Errors = SliderMotionNoError;
	device->Status.State = SliderStateIdle;
}
//------------------------------------------------------------------------------
static xResult Open(SliderT* device, SliderMoveRequestT* request)
{
	SliderDCMotorAdapterT* adapter = device->Adapter.Child;
	
	UpdateSensors(device);
	
	if (device->Status.Sensors & SliderSensorOvercurrent)
	{
		return xResultError;
	}
	
	if (device->Status.Sensors & SliderSensorOpen)
	{
		return xResultAccept;
	}
	
	Stop(device);
	
	device->Values.MoveTime = 0;
	adapter->Values.TimeOut = request->TimeOut;
	
	adapter->PWM_ForwardTimer->Counter = 0;
	*adapter->Values.PWM_ForwardPeriod = device->Options.StartPower;
	
	adapter->PWM_ForwardTimer->CaptureCompareOutput.Value |= adapter->Values.PWM_ForwardOutputEnableMask;
	
	adapter->Values.Events.Open = false;
	
	device->Status.Errors = SliderMotionNoError;
	device->Status.State = SliderStateOpening;
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
static xResult Close(SliderT* device, SliderMoveRequestT* request)
{
	SliderDCMotorAdapterT* adapter = device->Adapter.Child;
	
	UpdateSensors(device);
	
	if (device->Status.Sensors & SliderSensorOvercurrent)
	{
		return xResultError;
	}
	
	if (device->Status.Sensors & SliderSensorClose)
	{
		return xResultAccept;
	}
	
	Stop(device);
	
	adapter->Values.TimeOut = request->TimeOut;
	
	adapter->PWM_BackwardTimer->Counter = 0;
	*adapter->Values.PWM_BackwardPeriod = device->Options.StartPower;
	
	adapter->PWM_BackwardTimer->CaptureCompareOutput.Value |= adapter->Values.PWM_BackwardOutputEnableMask;
	
	adapter->Values.Events.Close = false;
	
	device->Status.Errors = SliderMotionNoError;
	device->Status.State = SliderStateClosing;
	
	return xResultBusy;
}
//------------------------------------------------------------------------------
static xResult RequestListener(SliderT* device, SliderAdapterRequestSelector selector, uint32_t args, uint32_t count)
{
	SliderDCMotorAdapterT* adapter = device->Adapter.Child;
	
	switch ((int)selector)
	{
		case SliderAdapterRequestOpen:
			return Open(device, (SliderMoveRequestT*)args);
		
		case SliderAdapterRequestClose:
			return Close(device, (SliderMoveRequestT*)args);
		
		case SliderAdapterRequestStop:
			Stop(device);
			break;
		
		default : return xResultRequestIsNotFound;
	}
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
static uint32_t GetValue(SliderT* device, SliderAdapterValueSelector selector)
{
	SliderDCMotorAdapterT* adapter = device->Adapter.Child;
	
	switch ((int)selector)
	{
		default : break;
	}
	
	return 0;
}
//------------------------------------------------------------------------------
static xResult SetValue(SliderT* device, SliderAdapterValueSelector selector, uint32_t value)
{
	SliderDCMotorAdapterT* adapter = device->Adapter.Child;
	
	switch ((int)selector)
	{
		default : return xResultValueIsNotFound;
	}
	
	return xResultAccept;
}
//==============================================================================
static SliderAdapterInterfaceT Interface =
{
	.Handler = (SliderAdapterHandlerT)Handler,
	.EventListener = (SliderAdapterEventListenerT)EventListener,
	.RequestListener = (SliderAdapterRequestListenerT)RequestListener,
	.GetValue = (SliderAdapterActionGetValueT)GetValue,
	.SetValue = (SliderAdapterActionSetValueT)SetValue,
};
//------------------------------------------------------------------------------
static const SliderOptionsT Options =
{
	.Acceleration = 10,
	.StartPower = 10,
};
//==============================================================================
xResult SliderDCMotorAdapterInit(SliderT* Slider, SliderDCMotorAdapterT* adapter)
{
	if (Slider && adapter)
	{
		Slider->Adapter.Description = "SliderDCMotorAdapterT";
		Slider->Adapter.Parent = Slider;
		Slider->Adapter.Child = adapter;
		Slider->Adapter.Interface = &Interface;
		
		Slider->Options.StartPower = 4000;
		Slider->Options.Acceleration = 20;
		
		adapter->Slider = Slider;
		
		adapter->Values.PWM_ForwardOutputEnableMask  = (1 << (adapter->PWM_ForwardChannel * 4));
		adapter->Values.PWM_BackwardOutputEnableMask  = (1 << (adapter->PWM_BackwardChannel * 4));
		
		adapter->Values.PWM_BackwardPeriod = &adapter->PWM_BackwardTimer->CaptureCompare1Value + adapter->PWM_BackwardChannel;
		adapter->Values.PWM_ForwardPeriod = &adapter->PWM_ForwardTimer->CaptureCompare1Value + adapter->PWM_ForwardChannel;
		
		adapter->PWM_BackwardTimer->BreakAndDeadTime.MainOutputEnable = true;
		adapter->PWM_ForwardTimer->BreakAndDeadTime.MainOutputEnable = true;
		
		adapter->PWM_BackwardTimer->Control1.CounterEnable = true;
		adapter->PWM_ForwardTimer->Control1.CounterEnable = true;
		
		return xResultAccept;
	}
	return xResultInvalidParameter;
}
//==============================================================================
