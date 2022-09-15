//==============================================================================
#include <string.h>
#include "Carousel_DCMotorAdapter.h"
#include "MotorDriver/MotorDriver.h"
//==============================================================================
static void Handler(CarouselT* device)
{
	CarouselDCMotorAdapterT* adapter = device->Adapter.Child;
	CarouselSensorsT sensors_state;
	
	MotorDriverHandler(&adapter->Driver);
	
	device->RequestAngle = adapter->Driver.PositionRequest / device->Calibration.Position;
	device->TotalAngle = adapter->Driver.Position / device->Calibration.Position;
	device->Power = adapter->Driver.Speed / device->Calibration.Speed.Polynomial[0];
	
	sensors_state.ZeroMark = (adapter->SensorZeroMarkPort->IDR & adapter->SensorZeroMarkPin) > 0;
	sensors_state.ZeroMark ^= adapter->SensorZeroMarkOnStateLogicLevel;
	
	device->Status.Sensors = sensors_state.Value;
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
static xResult SetPosition(CarouselT* device, CarouselRequestSetPositionT* request)
{
	CarouselDCMotorAdapterT* adapter = device->Adapter.Child;
	
	if (device && request)
	{
		int position = (int)(request->Angle * device->Calibration.Position);
		float speed = request->Speed * device->Calibration.Speed.Polynomial[0];
		
		return MotorDriverSetPosition(&adapter->Driver, position, speed, request->Time);
	}
	return xResultLinkError;
}
//------------------------------------------------------------------------------
static xResult SetOptions(CarouselT* device, CarouselOptionsT* request)
{
	CarouselDCMotorAdapterT* adapter = device->Adapter.Child;
	
	if (!device || !request)
	{
		return xResultLinkError;
	}
	
	if (adapter->Driver.Status.MotorState == MotorDriverMotorStateStopped)
	{
		adapter->Driver.Options.Acceleration = request->Acceleration;
		adapter->Driver.Options.Deceleration = request->Deceleration;
		
		adapter->Driver.Options.StartSpeed = request->StartSpeed;
		adapter->Driver.Options.StopSpeed = request->StopSpeed;
		
		return xResultAccept;
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
			return MotorDriverStop(&adapter->Driver);
		
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
			return adapter->Driver.PositionRequest;
		
		case CarouselAdapterValueMoveTime:
			return adapter->Driver.MoveTime;
		
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
xResult CarouselDCMotorAdapterInterfaceInit(CarouselAdapterBaseT* adapter)
{
	if (adapter)
	{
		adapter->Interface = &Interface;
		
		return xResultAccept;
	}
	
	return xResultInvalidParameter;
}
//==============================================================================
