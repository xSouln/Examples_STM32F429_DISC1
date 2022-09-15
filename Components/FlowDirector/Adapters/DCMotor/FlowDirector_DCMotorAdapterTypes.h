//==============================================================================
#ifndef _FLOW_DIRECTOR_DC_MOTOR_ADAPTER_TYPES_H
#define _FLOW_DIRECTOR_DC_MOTOR_ADAPTER_TYPES_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "FlowDirector/Controls/FlowDirector_MotorBase.h"
#include "FlowDirector_DCMotorAdapterConfig.h"
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
			uint8_t SensorCup1Found : 1;
			uint8_t SensorCup2Found : 1;
			uint8_t SensorCup3Found : 1;
			uint8_t SensorCup4Found : 1;
		};
		
		uint8_t Value;
		
	} Events;
	
} FlowDirectorDCMotorAdapterValuesT;
//------------------------------------------------------------------------------
typedef struct
{
	GPIO_TypeDef* SensorCup1Port;
	uint32_t SensorCup1Pin;
	
} FlowDirectorDCMotorAdapterSensorsT;
//------------------------------------------------------------------------------
typedef struct
{
	REG_TIM_T* PWM_ForwardTimer;
	REG_TIM_T* PWM_BackwardTimer;
	
	GPIO_TypeDef* SensorCup1Port;
	uint32_t SensorCup1Pin;
	
	GPIO_TypeDef* SensorCup2Port;
	uint32_t SensorCup2Pin;
	
	GPIO_TypeDef* SensorCup3Port;
	uint32_t SensorCup3Pin;
	
	GPIO_TypeDef* SensorCup4Port;
	uint32_t SensorCup4Pin;
	
	FlowDirectorDCMotorAdapterValuesT Values;
	
	struct
	{
		uint8_t SensorCup1OnStateLogicLevel : 1;
		uint8_t SensorCup2OnStateLogicLevel : 1;
		uint8_t SensorCup3OnStateLogicLevel : 1;
		uint8_t SensorCup4OnStateLogicLevel : 1;
		
		uint8_t PWM_ForwardChannel : 2;
		uint8_t PWM_BackwardChannel : 2;
	};
	
} FlowDirectorDCMotorAdapterT;
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif

