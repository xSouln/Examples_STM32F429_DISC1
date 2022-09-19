//==============================================================================
#ifndef _BREW_GROUP_WATER_PUMP_ADAPTER_TYPES_H
#define _BREW_GROUP_WATER_PUMP_ADAPTER_TYPES_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "BrewGroup/Controls/BrewGroup_WaterPumpBase.h"
#include "BrewGroup_WaterPumpAdapterConfig.h"
//==============================================================================
typedef struct
{
	GPIO_TypeDef* PumpEnablePort;
	uint32_t PumpEnablePin;
	
	REG_TIM_T* WaterFlowMeterTimer;
	
	struct
	{
		uint8_t PumpEnableOnStateLogicLevel : 1;
	};
	
} BrewGroupWaterPumpAdapterT;
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif

