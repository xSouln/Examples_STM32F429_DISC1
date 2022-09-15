//==============================================================================
#ifndef _SLIDER_DC_MOTOR_ADAPTER_TYPES_H
#define _SLIDER_DC_MOTOR_ADAPTER_TYPES_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "Slider/Adapters/Slider_AdapterBase.h"
#include "Slider_DCMotorAdapterConfig.h"
//==============================================================================
typedef struct
{
	uint32_t PWM_ForwardOutputEnableMask;
	uint32_t PWM_BackwardOutputEnableMask;
	
	volatile uint32_t* PWM_ForwardPeriod;
	volatile uint32_t* PWM_BackwardPeriod;
	
	uint32_t TimeOut;
	
	uint32_t Power;
	uint32_t Acceleration;
	
	union
	{
		struct
		{
			uint32_t Open : 1;
			uint32_t Close : 1;
		};
		
		uint32_t Value;
		
	} Events;
	
} SliderDCMotorAdapterValuesT;
//------------------------------------------------------------------------------
typedef struct
{
	void* Slider;
	
	REG_TIM_T* PWM_ForwardTimer;
	REG_TIM_T* PWM_BackwardTimer;
	
	GPIO_TypeDef* SensorClosePort;
	uint32_t SensorClosePin;
	
	GPIO_TypeDef* SensorOpenPort;
	uint32_t SensorOpenPin;
	
	GPIO_TypeDef* SensorOvercurrentPort;
	uint32_t SensorOvercurrentPin;
	
	SliderDCMotorAdapterValuesT Values;
	
	struct
	{
		uint8_t SensorClosingOnStateLogicLevel : 1;
		uint8_t SensorOpenOnStateLogicLevel : 1;
		uint8_t SensorOvercurrentOnStateLogicLevel : 1;
		uint8_t PWM_ForwardChannel : 2;
		uint8_t PWM_BackwardChannel : 2;
	};
	
} SliderDCMotorAdapterT;
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif

