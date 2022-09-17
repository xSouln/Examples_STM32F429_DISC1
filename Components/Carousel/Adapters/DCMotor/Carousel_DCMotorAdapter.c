//==============================================================================
#include <string.h>
#include "Carousel_DCMotorAdapter.h"
//==============================================================================
static xResult SetPosition(CarouselT* device, CarouselRequestSetPositionT* request);
static xResult ResetPosition(CarouselT* device);
//==============================================================================
static inline void UpdateSensors(CarouselT* device)
{
	CarouselDCMotorAdapterT* adapter = device->Motor.Child;
	CarouselSensorsT sensors_state;
	
	device->Status.LastSensorsState = device->Status.Value;
	
	sensors_state.ZeroMark = (adapter->SensorZeroMarkPort->IDR & adapter->SensorZeroMarkPin) > 0;
	sensors_state.ZeroMark = sensors_state.ZeroMark == adapter->SensorZeroMarkOnStateLogicLevel;
	
	sensors_state.Overcurrent = (adapter->SensorOvercurrentPort->IDR & adapter->SensorOvercurrentPin) > 0;
	sensors_state.Overcurrent = sensors_state.Overcurrent == adapter->SensorOvercurrentOnStateLogicLevel;
	
	device->Status.Sensors = sensors_state.Value;
}
//------------------------------------------------------------------------------
static void CalibrationHandler(CarouselT* device, int position_total)
{
	if (device->Status.Calibration == CarouselCalibratinStatusCalibrating
		&& device->Status.Motion == CarouselMotionStateStopped)
	{
		if (device->Status.MotionResult != CarouselMotionNoError)
		{
			device->Status.Calibration = CarouselCalibratinStatusError;
			device->Status.CalibrationState = CarouselCalibratinStateIdle;
			device->Interface->EventListener(device, CarouselEventCalibrationError, 0, 0);
			return;
		}
		
		CarouselRequestSetPositionT request;
		
		switch(device->Status.CalibrationState)
		{
			case CarouselCalibratinStateFindZeroMark:
				device->Status.CalibrationState = CarouselCalibratinStateMoveOutAtZeroMarkAndResetSteps;
				request.Angle = 10000;
				request.Mode = CarouselSetPositionModeMoveOutAtZeroMark;
				request.Power = 30.0;
				request.Timeout = 60000;
				SetPosition(device, &request);
				return;
			
			case CarouselCalibratinStateMoveOutAtZeroMarkAndResetSteps:
				device->Status.CalibrationState = CarouselCalibratinStateFindZeroMarkBackSide;
				request.Angle = 10000;
				request.Mode = CarouselSetPositionModeFindZeroMark;
				request.Power = 80.0;
				request.Timeout = 60000;
				ResetPosition(device);
				SetPosition(device, &request);
				return;
			
			case CarouselCalibratinStateFindZeroMarkBackSide:
				device->Status.CalibrationState = CarouselCalibratinStateMoveOutAtZeroMarkAndCalibrate;
				request.Angle = 10000;
				request.Mode = CarouselSetPositionModeMoveOutAtZeroMark;
				request.Power = 30.0;
				request.Timeout = 60000;
				SetPosition(device, &request);
				return;
		}
		
		device->Status.Calibration = CarouselCalibratinStatusColibated;
		device->Status.CalibrationState = CarouselCalibratinStateIdle;
		
		//position_total *= -1;
		
		device->Calibration.Position = ((float)position_total / 360.0);
		ResetPosition(device);
		
		device->TotalAngle = 0;
		
		device->Interface->EventListener(device, CarouselEventCalibrationComplete, 0, 0);
		
		request.Angle = device->Calibration.Offset;
		request.Power = 40.0;
		request.Mode = 0;
		request.Timeout = (uint32_t)(device->Calibration.Offset * 3000);
		
		SetPosition(device, &request);
	}
}
//------------------------------------------------------------------------------
static void Handler(CarouselT* device)
{
	CarouselDCMotorAdapterT* adapter = device->Motor.Child;
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
			device->Status.MotionResult = CarouselMotionOvercurrent;
			
			device->Interface->EventListener(device, CarouselEventOvercurrent, 0, 0);
		}
		return;
	}
	
	if (device->Status.Motion == CarouselMotionStateStopped)
	{
		CalibrationHandler(device, position_total);
		return;
	}
	
	if (device->Status.Sensors & CarouselSensorZeroMark)
	{
		if ((device->Mode == CarouselSetPositionModeStopAtZeroMark)
		|| ((device->Mode == CarouselSetPositionModeFindZeroMark) && (device->Status.LastSensorsState & CarouselSensorZeroMark) == 0))
		{
			adapter->PWM_ForwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_Forward.OutputEnableMask;
			adapter->PWM_BackwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_Backward.OutputEnableMask;
			
			device->Status.Motion = CarouselMotionStateStopped;
			
			device->Interface->EventListener(device, CarouselEventZeroMark, 0, 0);
		}
	}
	else if ((device->Mode == CarouselSetPositionModeMoveOutAtZeroMark) && ((device->Status.LastSensorsState & CarouselSensorZeroMark) > 0))
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
			device->Status.MotionResult = CarouselMotionTimeout;
			
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
static void EventListener(CarouselT* device, CarouselMotorEventSelector selector, uint32_t args, uint32_t count)
{
	switch ((int)selector)
	{
		default : break;
	}
}
//------------------------------------------------------------------------------
static void Stop(CarouselT* device)
{
	CarouselDCMotorAdapterT* adapter = device->Motor.Child;
	
	adapter->PWM_ForwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_Forward.OutputEnableMask;
	adapter->PWM_BackwardTimer->CaptureCompareOutput.Value &= ~adapter->Values.PWM_Backward.OutputEnableMask;
	
	device->Status.MotionResult = CarouselMotionNoError;
	device->Status.Motion = CarouselMotionStateStopped;
}
//------------------------------------------------------------------------------
static xResult SetPosition(CarouselT* device, CarouselRequestSetPositionT* request)
{
	CarouselDCMotorAdapterT* adapter = device->Motor.Child;
	
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
	
	//adapter->Values.SelectedPWM->Timer->Counter = 0;
	*adapter->Values.SelectedPWM->CompareValue = power;
	adapter->Values.SelectedPWM->Timer->CaptureCompareOutput.Value |= adapter->Values.SelectedPWM->OutputEnableMask;
	//adapter->Values.SelectedPWM->Timer->Control1.CounterEnable = true;
	device->Status.Motion = diraction;
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
static xResult SetOptions(CarouselT* device, CarouselOptionsT* request)
{
	CarouselDCMotorAdapterT* adapter = device->Motor.Child;
	
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
	CarouselDCMotorAdapterT* adapter = device->Motor.Child;
	
	if (device->Status.Motion == CarouselMotionStateStopped)
	{
		adapter->EncoderTimer->Counter = 0;
		device->TotalAngle = 0;
	}
	
	return xResultBusy;
}
//------------------------------------------------------------------------------
static xResult RequestListener(CarouselT* device, CarouselMotorRequestSelector selector, uint32_t args, uint32_t count)
{
	CarouselDCMotorAdapterT* adapter = device->Motor.Child;
	
	switch ((int)selector)
	{
		case CarouselMotorRequestSetPosition:
			return SetPosition(device, (CarouselRequestSetPositionT*)args);
		
		case CarouselMotorRequestSetOptions:
			return SetOptions(device, (CarouselOptionsT*)args);
		
		case CarouselMotorRequestStop:
			Stop(device);
			break;
		
		case CarouselMotorRequestClearPosition:
			return ResetPosition(device);
		
		default : return xResultRequestIsNotFound;
	}
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
static uint32_t GetValue(CarouselT* device, CarouselMotorValueSelector selector)
{
	CarouselDCMotorAdapterT* adapter = device->Motor.Child;
	
	switch ((int)selector)
	{
		case CarouselMotorValueStepPosition:
			return adapter->EncoderTimer->Counter;
		
		case CarouselMotorValueRequestStepPosition:
			return adapter->Values.PositionRequest;
		
		default : break;
	}
	
	return 0;
}
//------------------------------------------------------------------------------
static xResult SetValue(CarouselT* device, CarouselMotorValueSelector selector, uint32_t value)
{
	switch ((int)selector)
	{
		default : return xResultValueIsNotFound;
	}
	
	return xResultAccept;
}
//==============================================================================
static CarouselMotorInterfaceT Interface =
{
	.Handler = (CarouselMotorHandlerT)Handler,
	.EventListener = (CarouselMotorEventListenerT)EventListener,
	.RequestListener = (CarouselMotorRequestListenerT)RequestListener,
	.GetValue = (CarouselMotorActionGetValueT)GetValue,
	.SetValue = (CarouselMotorActionSetValueT)SetValue,
};
//==============================================================================
xResult CarouselDCMotorAdapterInit(CarouselT* carousel, CarouselDCMotorAdapterT* adapter)
{
	extern xResult CarouselDCMotorAdapterInterfaceInit(CarouselMotorBaseT* adapter);
	
	if (carousel && adapter)
	{
		carousel->Motor.Description = "CarouselDCMotorAdapterT";
		carousel->Motor.Parent = carousel;
		carousel->Motor.Child = adapter;
		carousel->Motor.Interface = &Interface;
		adapter->Carousel = carousel;
		
		adapter->Values.PWM_Backward.Timer = adapter->PWM_BackwardTimer;
		adapter->Values.PWM_Backward.OutputEnableMask = (1 << (adapter->PWM_BackwardChannel * 4));
		adapter->Values.PWM_Backward.CompareValue = &adapter->PWM_BackwardTimer->CaptureCompare1Value + adapter->PWM_BackwardChannel;
		
		adapter->Values.PWM_Forward.Timer = adapter->PWM_ForwardTimer;
		adapter->Values.PWM_Forward.OutputEnableMask = (1 << (adapter->PWM_ForwardChannel * 4));
		adapter->Values.PWM_Forward.CompareValue = &adapter->PWM_ForwardTimer->CaptureCompare1Value + adapter->PWM_ForwardChannel;
		
		adapter->PWM_BackwardTimer->BreakAndDeadTime.MainOutputEnable = true;
		adapter->PWM_ForwardTimer->BreakAndDeadTime.MainOutputEnable = true;
		
		adapter->EncoderTimer->Control1.CounterEnable = true;
		adapter->PWM_BackwardTimer->Control1.CounterEnable = true;
		adapter->PWM_ForwardTimer->Control1.CounterEnable = true;
		
		return xResultAccept;
	}
	return xResultInvalidParameter;
}
//==============================================================================
