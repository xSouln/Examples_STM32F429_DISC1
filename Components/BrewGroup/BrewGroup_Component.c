//==============================================================================
#include "BrewGroup_Component.h"
#include "BrewGroup/Adapters/DCMotor/BrewGroup_DCMotorAdapter.h"
#include "BrewGroup/Adapters/Thermostat/BrewGroup_ThermostatAdapter.h"
#include "BrewGroup/Adapters/WaterPump/BrewGroup_WaterPumpAdapter.h"
//==============================================================================
BrewGroupT BrewGroup;
//==============================================================================
static void EventListener(BrewGroupT* BrewGroup, BrewGroupEventSelector event, uint32_t args, uint32_t count)
{
	switch ((uint8_t)event)
	{
		
		default : return;
	}
}
//------------------------------------------------------------------------------
static xResult RequestListener(BrewGroupT* BrewGroup, BrewGroupRequestSelector event, uint32_t args, uint32_t count)
{
	switch ((uint8_t)event)
	{
		case BrewGroupRequestDelay :
			HAL_Delay(args);
			break;
		
		default : return xResultRequestIsNotFound;
	}
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
const static BrewGroupInterfaceT Interface =
{
	.EventListener = (BrewGroupEventListenerT)EventListener,
	.RequestListener = (BrewGroupRequestListenerT)EventListener,
};
//------------------------------------------------------------------------------
BrewGroupDCMotorAdapterT BrewGroupDCMotorAdapter =
{
	.PWM_ForwardTimer = (REG_TIM_T*)TIM4,
	.PWM_BackwardTimer = (REG_TIM_T*)TIM4,
	
	.PWM_ForwardChannel = 2,
	.PWM_BackwardChannel = 3,
};
//------------------------------------------------------------------------------
BrewGroupTermostatAdapterT BrewGroupTermostatAdapter =
{
	
};
//------------------------------------------------------------------------------
BrewGroupWaterPumpAdapterT BrewGroupWaterPumpAdapter =
{
	
};
//==============================================================================
xResult BrewGroupComponentInit(void* parent)
{
	BrewGroupInit(&BrewGroup, parent, (BrewGroupInterfaceT*)&Interface);
	
	BrewGroupDCMotorAdapterInit(&BrewGroup, &BrewGroupDCMotorAdapter);
	BrewGroupTermostatAdapterInit(&BrewGroup, &BrewGroupTermostatAdapter);
	BrewGroupWaterPumpAdapterInit(&BrewGroup, &BrewGroupWaterPumpAdapter);
	
  return 0;
}
//==============================================================================
