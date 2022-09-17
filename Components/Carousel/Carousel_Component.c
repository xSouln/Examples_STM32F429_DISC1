//==============================================================================
#include "Carousel_Component.h"
#include "Adapters/DCMotor/Carousel_DCMotorAdapter.h"
//==============================================================================
CarouselT Carousel;
//==============================================================================
static void EventListener(CarouselT* carousel, CarouselEventSelector event, uint32_t args, uint32_t count)
{
	switch ((uint8_t)event)
	{
		
		default : return;
	}
}
//------------------------------------------------------------------------------
static xResult RequestListener(CarouselT* carousel, CarouselRequestSelector event, uint32_t args, uint32_t count)
{
	switch ((uint8_t)event)
	{
		case CarouselRequestDelay :
			HAL_Delay(args);
			break;
		
		default : return xResultRequestIsNotFound;
	}
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
const static CarouselInterfaceT Interface =
{
	.EventListener = (CarouselEventListenerT)EventListener,
	.RequestListener = (CarouselRequestListenerT)EventListener,
};
//------------------------------------------------------------------------------
CarouselDCMotorAdapterT CarouselDCMotorAdapter =
{
	.PWM_ForwardTimer = (REG_TIM_T*)TIM4,
	.PWM_BackwardTimer = (REG_TIM_T*)TIM4,
	.EncoderTimer = (REG_TIM_T*)TIM2,
	
	.PWM_ForwardChannel = 1,
	.PWM_BackwardChannel = 0,
	
	.SensorZeroMarkPort = CAROUSEL_SENSOR_ZERO_MARK_GPIO_Port,
	.SensorZeroMarkPin = CAROUSEL_SENSOR_ZERO_MARK_Pin,
	.SensorZeroMarkOnStateLogicLevel = 1,
	
	.SensorOvercurrentPort = CAROUSEL_SENSOR_OVERCURRENT_GPIO_Port,
	.SensorOvercurrentPin = CAROUSEL_SENSOR_OVERCURRENT_Pin,
	.SensorOvercurrentOnStateLogicLevel = 0,
};
//==============================================================================
xResult CarouselComponentInit(void* parent)
{
	CarouselInit(&Carousel, parent, (CarouselInterfaceT*)&Interface);
	CarouselDCMotorAdapterInit(&Carousel, &CarouselDCMotorAdapter);
	
  return 0;
}
//==============================================================================
