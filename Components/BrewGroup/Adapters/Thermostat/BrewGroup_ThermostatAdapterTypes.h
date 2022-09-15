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
	uint32_t SensorPin;
	
} BrewGroupTermostatAdapterT;
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif

