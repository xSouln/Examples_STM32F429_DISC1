//==============================================================================
#include <string.h>
#include "Carousel_DCMotorAdapter.h"
//==============================================================================
static inline void UpdateSensors(CarouselT* device)
{
	CarouselDCMotorAdapterT* adapter = device->Adapter.Child;
	CarouselSensorsT sensors_state;
	
	sensors_state.ZeroMark = (adapter->SensorZeroMarkPort->IDR & adapter->SensorZeroMarkPin) > 0;
	sensors_state.ZeroMark = sensors_state.ZeroMark == adapter->SensorZeroMarkOnStateLogicLevel;
	
	sensors_state.Overcurrent = (adapter->SensorOvercurrentPort->IDR & adapter->SensorOvercurrentPin) > 0;
	sensors_state.Overcurrent = sensors_state.Overcurrent == adapter->SensorOvercurrentOnStateLogicLevel;
	
	device->Status.Sensors = sensors_state.Value;
}
//------------------------------------------------------------------------------
static void Handler(CarouselT* device)
{
	CarouselDCMotorAdapterT* adapter = device->Adapter.Child;
	int position_total = adapter->EncoderTimer->Counter;
	int power;
	
	UpdateSensors(device);
	
	device->RequestAngle = adapter->Values.PositionRequest / device->Calibration.Position;
	device->TotalAngle = position_total / device->Calibration.Position;
	
	if (adapter->PWM_ForwardTimer->CaptureCompareOutput.Value & adapter->Values.PWM_Forward.OutputEnableMask)
	{
		device->Status.Motion = CarouselMotionStateMovingForward;
		device->TotalPower = (float)*adapter->Values.PWM_Forward.CompareValue / adapter->PWM_ForwardTimer->Period * 100.0;
	}
	else if (adapter->PWM_BackwardTimer->CaptureCompareOutput.Value & adapter->Values.PWM_Backward.OutputEnableMask)
	{
		device->Status.Motion = CarouselMotionStateMovingBackward;
		device->TotalPower = (float)*adapter->Values.PWM_Backward.CompareValue / adapter->PWM_BackwardTimer->Period * 100.0;
	}
	else
	{
		device->Status.Motion = CarouselMotionStateStopped;
	}
	
	if (device->Status.Sensors & CarouselSensorOvercurrent)
	{
		adapter->PWM_ForwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_Forward.OutputEnableMask;
		adapter->PWM_BackwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_Backward.OutputEnableMask;
		
		if (device->Status.Motion != CarouselMotionStateStopped)
		{
			device->Status.Motion = CarouselMotionStateStopped;
			device->Status.Errors = CarouselMotionOvercurrent;
			
			device->Interface->EventListener(device, CarouselEventOvercurrent, 0, 0);
		}
		return;
	}
	
	if (device->Status.Motion == CarouselMotionStateStopped)
	{
		return;
	}
	
	if (device->Status.Sensors & CarouselSensorZeroMark && (device->Mode & CarouselSetPositionModeStopAtZeroMark))
	{
		adapter->PWM_ForwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_Forward.OutputEnableMask;
		adapter->PWM_BackwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_Backward.OutputEnableMask;
		
		device->Status.Motion = CarouselMotionStateStopped;
		
		device->Interface->EventListener(device, CarouselEventZeroMark, 0, 0);
	}
	
	if ((device->Status.Motion == CarouselMotionStateMovingForward && position_total >= adapter->Values.PositionRequest)
		|| (device->Status.Motion == CarouselMotionStateMovingBackward && position_total <= adapter->Values.PositionRequest))
	{
		adapter->PWM_ForwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_Forward.OutputEnableMask;
		adapter->PWM_BackwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_Backward.OutputEnableMask;
		
		device->Status.Motion = CarouselMotionStateStopped;
		
		device->Interface->EventListener(device, CarouselEventPositionIsSet, 0, 0);
		return;
	}
	
	if (device->Status.Motion != CarouselMotionStateStopped)
	{
		device->MoveTime++;
		
		if (device->MoveTime >= device->TimeOut)
		{
			adapter->PWM_ForwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_Forward.OutputEnableMask;
			adapter->PWM_BackwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_Backward.OutputEnableMask;
			
			device->Status.Motion = CarouselMotionStateStopped;
			device->Status.Errors = CarouselMotionTimeout;
			
			device->Interface->EventListener(device, CarouselEventTimeout, 0, 0);
			return;
		}
		
		if (device->TotalPower < device->RequestPower)
		{
			device->TotalPower += adapter->Values.AccelerationIncrement;
		}
		
		if (adapter->Values.SelectedPWM)
		{
			*adapter->Values.SelectedPWM->CompareValue = (uint16_t)(device->TotalPower / 100 * adapter->Values.SelectedPWM->Timer->Period);
		}
	}
}
//------------------------------------------------------------------------------
static void EventListener(CarouselT* device, CarouselAdapterEventSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : break;
	}
}
//------------------------------------------------------------------------------
static void Stop(CarouselT* device)
{
	CarouselDCMotorAdapterT* adapter = device->Adapter.Child;
	
	//adapter->PWM_BackwardTimer->Control1.CounterEnable = false;
	//adapter->PWM_ForwardTimer->Control1.CounterEnable = false;
	
	adapter->PWM_ForwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_Forward.OutputEnableMask;
	adapter->PWM_BackwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_Backward.OutputEnableMask;
	
	device->Status.Errors = CarouselMotionNoError;
	device->Status.Motion = CarouselMotionStateStopped;
}
//------------------------------------------------------------------------------
static xResult SetPosition(CarouselT* device, CarouselRequestSetPositionT* request)
{
	CarouselDCMotorAdapterT* adapter = device->Adapter.Child;
	
	if (!device || !request)
	{
		return xResultLinkError;
	}
	
	if (device->Status.Motion != CarouselMotionStateStopped)
	{
		return xResultBusy;
	}
	
	UpdateSensors(device);
	
	if (device->Status.Sensors & CarouselSensorOvercurrent)
	{
		return xResultError;
	}
	
	Stop(device);
	
	int position_total = adapter->EncoderTimer->Counter;
	int position_request = (int)(request->Angle * device->Calibration.Position);
	
	if (position_total == position_request)
	{
		return xResultAccept;
	}
	
	device->MoveTime = 0;
	device->TimeOut = request->Timeout;
	device->TotalPower = device->Options.StartPower;
	device->RequestPower = request->Power;
	device->Mode = request->Mode;
	adapter->Values.PositionRequest = position_request;
	
	uint8_t diraction;
	
	if (position_total < position_request)
	{
		adapter->Values.SelectedPWM = &adapter->Values.PWM_Forward;
		diraction = CarouselMotionStateMovingForward;
	}
	else if (position_total > position_request)
	{
		adapter->Values.SelectedPWM = &adapter->Values.PWM_Backward;
		diraction = CarouselMotionStateMovingBackward;
	}
	
	uint16_t power = (uint16_t)(device->Options.StartPower / 100 * adapter->Values.SelectedPWM->Timer->Period);
	adapter->Values.AccelerationIncrement = device->Options.Acceleration / 1000;
	
	adapter->Values.SelectedPWM->Timer->Counter = 0;
	*adapter->Values.SelectedPWM->CompareValue = power;
	adapter->Values.SelectedPWM->Timer->CaptureCompareOutput.Value |= adapter->Values.SelectedPWM->OutputEnableMask;
	//adapter->Values.SelectedPWM->Timer->Control1.CounterEnable = true;
	device->Status.Motion = diraction;
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
static xResult SetOptions(CarouselT* device, CarouselOptionsT* request)
{
	CarouselDCMotorAdapterT* adapter = device->Adapter.Child;
	
	if (!device || !request)
	{
		return xResultLinkError;
	}
	
	if (device->Status.Motion == CarouselMotionStateStopped)
	{
		memcpy(&device->Options, request, sizeof(device->Options));
		
		return xResultAccept;
	}
	
	return xResultBusy;
}
//------------------------------------------------------------------------------
static xResult ResetPosition(CarouselT* device)
{
	CarouselDCMotorAdapterT* adapter = device->Adapter.Child;
	
	if (device->Status.Motion == CarouselMotionStateStopped)
	{
		adapter->EncoderTimer->Counter = 0;
	}
	
	return xResultBusy;
}
//------------------------------------------------------------------------------
static xResult RequestListener(CarouselT* device, CarouselAdapterRequestSelector selector, uint32_t args, uint32_t count)
{
	CarouselDCMotorAdapterT* adapter = device->Adapter.Child;
	
	switch ((int)selector)
	{
		case CarouselAdapterRequestSetPosition:
			return SetPosition(device, (CarouselRequestSetPositionT*)args);
		
		case CarouselAdapterRequestSetOptions:
			return SetOptions(device, (CarouselOptionsT*)args);
		
		case CarouselAdapterRequestStop:
			Stop(device);
			break;
		
		case CarouselAdapterRequestClearPosition:
			return ResetPosition(device);
		
		default : return xResultRequestIsNotFound;
	}
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
static uint32_t GetValue(CarouselT* device, CarouselAdapterValueSelector selector)
{
	CarouselDCMotorAdapterT* adapter = device->Adapter.Child;
	
	switch ((int)selector)
	{
		case CarouselAdapterValueStepPosition:
			return adapter->EncoderTimer->Counter;
		
		case CarouselAdapterValueRequestStepPosition:
			return adapter->Values.PositionRequest;
		
		default : break;
	}
	
	return 0;
}
//------------------------------------------------------------------------------
static xResult SetValue(CarouselT* device, CarouselAdapterValueSelector selector, uint32_t value)
{
	switch ((int)selector)
	{
		default : return xResultValueIsNotFound;
	}
	
	return xResultAccept;
}
//==============================================================================
static CarouselAdapterInterfaceT Interface =
{
	.Handler = (CarouselAdapterHandlerT)Handler,
	.EventListener = (CarouselAdapterEventListenerT)EventListener,
	.RequestListener = (CarouselAdapterRequestListenerT)RequestListener,
	.GetValue = (CarouselAdapterActionGetValueT)GetValue,
	.SetValue = (CarouselAdapterActionSetValueT)SetValue,
};
//==============================================================================
xResult CarouselDCMotorAdapterInit(CarouselT* carousel, CarouselDCMotorAdapterT* adapter)
{
	extern xResult CarouselDCMotorAdapterInterfaceInit(CarouselAdapterBaseT* adapter);
	
	if (carousel && adapter)
	{
		carousel->Adapter.Description = "CarouselDCMotorAdapterT";
		carousel->Adapter.Parent = carousel;
		carousel->Adapter.Child = adapter;
		carousel->Adapter.Interface = &Interface;
		adapter->Carousel = carousel;
		
		adapter->EncoderTimer->Control1.CounterEnable = true;
		
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
