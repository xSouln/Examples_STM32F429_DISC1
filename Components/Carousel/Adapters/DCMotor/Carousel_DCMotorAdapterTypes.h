//==============================================================================
#ifndef _CAROUSEL_DC_MOTOR_ADAPTER_TYPES_H
#define _CAROUSEL_DC_MOTOR_ADAPTER_TYPES_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "Carousel/Adapters/Carousel_AdapterBase.h"
#include "Carousel_DCMotorAdapterConfig.h"
//==============================================================================
typedef struct
{
	REG_TIM_T* Timer;
	uint32_t OutputEnableMask;
	volatile uint32_t* CompareValue;
	
} CarouselDCMotorAdapterPWM_T;
//------------------------------------------------------------------------------
typedef struct
{
	CarouselDCMotorAdapterPWM_T PWM_Forward;
	CarouselDCMotorAdapterPWM_T PWM_Backward;
	
	CarouselDCMotorAdapterPWM_T* SelectedPWM;
	
	int PositionRequest;
	float AccelerationIncrement;
	
} CarouselDCMotorAdapterValuesT;
//------------------------------------------------------------------------------
typedef struct
{
	void* Carousel;
	
	REG_TIM_T* PWM_ForwardTimer;
	REG_TIM_T* PWM_BackwardTimer;
	
	REG_TIM_T* EncoderTimer;
	
	GPIO_TypeDef* SensorOvercurrentPort;
	uint32_t SensorOvercurrentPin;
	
	GPIO_TypeDef* SensorZeroMarkPort;
	uint32_t SensorZeroMarkPin;
	
	CarouselDCMotorAdapterValuesT Values;
	
	struct
	{
		uint8_t SensorZeroMarkOnStateLogicLevel : 1;
		uint8_t SensorOvercurrentOnStateLogicLevel : 1;
		uint8_t PWM_ForwardChannel : 2;
		uint8_t PWM_BackwardChannel : 2;
	};
	
} CarouselDCMotorAdapterT;
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif

