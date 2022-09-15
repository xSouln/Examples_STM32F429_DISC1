//==============================================================================
#include "FlowDirector_Component.h"
#include "FlowDirector/Adapters/DCMotor/FlowDirector_DCMotorAdapter.h"
//==============================================================================
FlowDirectorT FlowDirector;
//==============================================================================
static void EventListener(FlowDirectorT* FlowDirector, FlowDirectorEventSelector event, uint32_t args, uint32_t count)
{
	switch ((uint8_t)event)
	{
		
		default : return;
	}
}
//------------------------------------------------------------------------------
static xResult RequestListener(FlowDirectorT* FlowDirector, FlowDirectorRequestSelector event, uint32_t args, uint32_t count)
{
	switch ((uint8_t)event)
	{
		case FlowDirectorRequestDelay :
			HAL_Delay(args);
			break;
		
		default : return xResultRequestIsNotFound;
	}
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
const static FlowDirectorInterfaceT Interface =
{
	.EventListener = (FlowDirectorEventListenerT)EventListener,
	.RequestListener = (FlowDirectorRequestListenerT)EventListener,
};
//------------------------------------------------------------------------------
FlowDirectorDCMotorAdapterT FlowDirectorDCMotorAdapter =
{
	.PWM_ForwardTimer = (REG_TIM_T*)TIM4,
	.PWM_BackwardTimer = (REG_TIM_T*)TIM4,
	
	.PWM_ForwardChannel = 2,
	.PWM_BackwardChannel = 3,
};
//==============================================================================
xResult FlowDirectorComponentInit(void* parent)
{
	FlowDirectorInit(&FlowDirector, parent, (FlowDirectorInterfaceT*)&Interface);
	
	FlowDirectorDCMotorAdapterInit(&FlowDirector, &FlowDirectorDCMotorAdapter);
	
  return 0;
}
//==============================================================================
