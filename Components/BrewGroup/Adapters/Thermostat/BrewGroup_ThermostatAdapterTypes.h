//==============================================================================
#ifndef _BREW_GROUP_TERMOSTAT_TYPES_H
#define _BREW_GROUP_TERMOSTAT_TYPES_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "BrewGroup/Controls/BrewGroup_ThermostatBase.h"
#include "BrewGroup_ThermostatAdapterConfig.h"
//==============================================================================
typedef struct
{
	GPIO_TypeDef* TermostatEnablePort;
	uint32_t TermostatEnablePin;
	
	REG_TIM_T* WaterFlowMeterTimer;
	
	ADC_HandleTypeDef* Adc;
	
	struct
	{
		uint8_t TermostatEnableOnStateLogicLevel : 1;
	};
	
} BrewGroupTermostatAdapterT;
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif

