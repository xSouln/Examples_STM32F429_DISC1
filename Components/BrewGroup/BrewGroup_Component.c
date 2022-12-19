//==============================================================================
#include "BrewGroup_Component.h"
#include "BrewGroup/Adapters/Sensors/BrewGroup_SensorsAdapter.h"
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
	.RequestListener = (BrewGroupRequestListenerT)RequestListener,
};
//------------------------------------------------------------------------------
BrewGroupDCMotorAdapterT BrewGroupDCMotorAdapter =
{
	.PWM_ForwardTimer = (REG_TIM_T*)TIM9,
	.PWM_BackwardTimer = (REG_TIM_T*)TIM9,
	
	.PWM_ForwardChannel = 0,
	.PWM_BackwardChannel = 1,
};
//------------------------------------------------------------------------------
BrewGroupTermostatAdapterT BrewGroupTermostatAdapter =
{
	
};
//------------------------------------------------------------------------------
BrewGroupWaterPumpAdapterT BrewGroupWaterPumpAdapter =
{
	
};
//------------------------------------------------------------------------------
BrewGroupSensorsAdapterT BrewGroupSensorsAdapter =
{
	.SensorClosePort = SLIDER_SENSOR_CLOSE_GPIO_Port,
	.SensorClosePin = SLIDER_SENSOR_CLOSE_Pin,
	.SensorCloseOnStateLogicLevel = 0,
	
	.SensorOpenPort = SLIDER_SENSOR_OPEN_GPIO_Port,
	.SensorOpenPin = SLIDER_SENSOR_OPEN_Pin,
	.SensorOpenOnStateLogicLevel = 0,
	
	.SensorOvercurrentPort = BREW_SENSOR_OVERCURRENT_GPIO_Port,
	.SensorOvercurrentPin = BREW_SENSOR_OVERCURRENT_Pin,
	.SensorOvercurrentOnStateLogicLevel = 0,
};
//==============================================================================
xResult BrewGroupComponentInit(void* parent)
{
	BrewGroupInit(&BrewGroup, parent, (BrewGroupInterfaceT*)&Interface);
	
	BrewGroupSensorsAdapterInit(&BrewGroup, &BrewGroupSensorsAdapter);
	BrewGroupDCMotorAdapterInit(&BrewGroup, &BrewGroupDCMotorAdapter);
	BrewGroupTermostatAdapterInit(&BrewGroup, &BrewGroupTermostatAdapter);
	BrewGroupWaterPumpAdapterInit(&BrewGroup, &BrewGroupWaterPumpAdapter);
	
  return 0;
}
//==============================================================================
