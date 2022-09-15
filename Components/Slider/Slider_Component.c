//==============================================================================
#include "Slider_Component.h"
#include "Adapters/Slider_Adapters.h"
#include "Communications/Slider_RxTransactions.h"
//==============================================================================
SliderT Slider;
//==============================================================================
static void EventListener(SliderT* Slider, SliderEventSelector event, uint32_t args, uint32_t count)
{
	switch ((uint8_t)event)
	{
		case SliderEventOpen:
			if (Slider->RxLine)
			{
				xRxTransactionTransmitEvent(Slider->RxLine->Tx,
																	SLIDER_DEVICE_KEY,
																	SLIDER_EVT_OPEN,
																	&Slider->Status,
																	sizeof(Slider->Status));
			}
			break;
		
		case SliderEventClose:
			if (Slider->RxLine)
			{
				xRxTransactionTransmitEvent(Slider->RxLine->Tx,
																		SLIDER_DEVICE_KEY,
																		SLIDER_EVT_CLOSE,
																		&Slider->Status,
																		sizeof(Slider->Status));
			}
			break;
			
		case SliderEventOvercurrent:
			if (Slider->RxLine)
			{
				xRxTransactionTransmitEvent(Slider->RxLine->Tx,
																		SLIDER_DEVICE_KEY,
																		SLIDER_EVT_OVERCURRENT,
																		&Slider->Status,
																		sizeof(Slider->Status));
			}
			break;
		
		default : return;
	}
}
//------------------------------------------------------------------------------
static xResult RequestListener(SliderT* Slider, SliderRequestSelector event, uint32_t args, uint32_t count)
{
	switch ((uint8_t)event)
	{
		case SliderRequestDelay :
			HAL_Delay(args);
			break;
		
		default : return xResultRequestIsNotFound;
	}
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
const static SliderInterfaceT Interface =
{
	.EventListener = (SliderEventListenerT)EventListener,
	.RequestListener = (SliderRequestListenerT)EventListener,
};
//------------------------------------------------------------------------------
SliderDCMotorAdapterT SliderDCMotorAdapter =
{
	.PWM_ForwardTimer = (REG_TIM_T*)TIM4,
	.PWM_BackwardTimer = (REG_TIM_T*)TIM4,
	
	.PWM_ForwardChannel = 2,
	.PWM_BackwardChannel = 3,
	
	.SensorClosePort = SLIDER_SENSOR_CLOSE_GPIO_Port,
	.SensorClosePin = SLIDER_SENSOR_CLOSE_Pin,
	.SensorClosingOnStateLogicLevel = 0,
	
	.SensorOpenPort = SLIDER_SENSOR_OPEN_GPIO_Port,
	.SensorOpenPin = SLIDER_SENSOR_OPEN_Pin,
	.SensorOpenOnStateLogicLevel = 0,
	
	.SensorOvercurrentPort = SLIDER_SENSOR_OVERCURRENT_GPIO_Port,
	.SensorOvercurrentPin = SLIDER_SENSOR_OVERCURRENT_Pin,
	.SensorOvercurrentOnStateLogicLevel = 0,
};
//==============================================================================
xResult SliderComponentInit(void* parent)
{
	SliderInit(&Slider, parent, (SliderInterfaceT*)&Interface);
	SliderDCMotorAdapterInit(&Slider, &SliderDCMotorAdapter);
	
  return 0;
}
//==============================================================================
