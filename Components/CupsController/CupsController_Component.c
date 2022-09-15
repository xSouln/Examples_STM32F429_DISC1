//==============================================================================
#include "CupsController_Component.h"
#include "CupsController/Adapters/LED/CupsController_LEDAdapter.h"
#include "tim.h"
//==============================================================================
WS2812_BufT data_buffer_cups_12[(CUPS_CONTROLLER_LED_SYNC_START_DATA_COUNT
														+ CUPS_CONTROLLER_LED_DATA_BUFFER_SIZE_CUP1
														+ CUPS_CONTROLLER_LED_DATA_BUFFER_SIZE_CUP2
														+ CUPS_CONTROLLER_LED_SYNC_END_DATA_COUNT)];
//------------------------------------------------------------------------------
WS2812_BufT data_buffer_cups_34[(CUPS_CONTROLLER_LED_SYNC_START_DATA_COUNT
														+ CUPS_CONTROLLER_LED_DATA_BUFFER_SIZE_CUP3
														+ CUPS_CONTROLLER_LED_DATA_BUFFER_SIZE_CUP4
														+ CUPS_CONTROLLER_LED_SYNC_END_DATA_COUNT)];
//------------------------------------------------------------------------------
//==============================================================================
CupsControllerLEDAdapterT AdapterCup12 =
{
	.Timer = TIM1,
	.DMA = DMA2_Stream5,
	
	.PWM_Channel = 1,
	
	.DrawMemory = data_buffer_cups_12,
	.DrawMemorySize = sizeof(data_buffer_cups_12) / sizeof(data_buffer_cups_12[0]),
};
//------------------------------------------------------------------------------
CupsControllerLEDAdapterT AdapterCup34 =
{
	.Timer = TIM1,
	.DMA = DMA2_Stream5,
	
	.PWM_Channel = 2,
	
	.DrawMemory = data_buffer_cups_34,
	.DrawMemorySize = sizeof(data_buffer_cups_34) / sizeof(data_buffer_cups_34[0])
};
//==============================================================================
static void EventListener(void* cup, CupsControllerEventSelector event, uint32_t args, uint32_t count)
{
	switch ((uint8_t)event)
	{
		
		default : return;
	}
}
//==============================================================================
const static CupsControllerInterfaceT Interface =
{
	.EventListener = (CupsControllerEventListenerT)EventListener
};
//==============================================================================
int CupsControllerComponentInit(void* parent)
{
	CupsControllerInit(parent, (CupsControllerInterfaceT*)&Interface);
	
	uint16_t buffer_offset = CUPS_CONTROLLER_LED_SYNC_START_DATA_COUNT;
	CupsController.Cups[CupNumber1].DataBuffer = data_buffer_cups_12 + buffer_offset;
	CupsController.Cups[CupNumber1].DataBufferSize = CUPS_CONTROLLER_LED_DATA_BUFFER_SIZE_CUP1;
	buffer_offset += CUPS_CONTROLLER_LED_DATA_BUFFER_SIZE_CUP1;
	
	CupsController.Cups[CupNumber2].DataBuffer = data_buffer_cups_12 + buffer_offset;
	CupsController.Cups[CupNumber2].DataBufferSize = CUPS_CONTROLLER_LED_DATA_BUFFER_SIZE_CUP2;
	
	CupsControllerLEDAdapterInit(&CupsController.Cups[CupNumber1], &AdapterCup12);
	CupsControllerLEDAdapterInit(&CupsController.Cups[CupNumber2], &AdapterCup12);
	//----------------------------------------------------------------------------
	buffer_offset = CUPS_CONTROLLER_LED_SYNC_START_DATA_COUNT;
	CupsController.Cups[CupNumber3].DataBuffer = data_buffer_cups_34 + buffer_offset;
	CupsController.Cups[CupNumber3].DataBufferSize = CUPS_CONTROLLER_LED_DATA_BUFFER_SIZE_CUP3;
	buffer_offset += CUPS_CONTROLLER_LED_DATA_BUFFER_SIZE_CUP3;
	
	CupsController.Cups[CupNumber4].DataBuffer = data_buffer_cups_34 + buffer_offset;
	CupsController.Cups[CupNumber4].DataBufferSize = CUPS_CONTROLLER_LED_DATA_BUFFER_SIZE_CUP4;
	
	CupsControllerLEDAdapterInit(&CupsController.Cups[CupNumber3], &AdapterCup34);
	CupsControllerLEDAdapterInit(&CupsController.Cups[CupNumber4], &AdapterCup34);
	
	CupsControllerDrawManagerInit(&CupsController.Cups[CupNumber1], &DrawingTemplate1);
	CupsControllerDrawManagerInit(&CupsController.Cups[CupNumber2], &DrawingTemplate2);
	
	WS2812_DrawingStart(&CupsController.Cups[CupNumber1].Driver.DrawManager);
	WS2812_DrawingStart(&CupsController.Cups[CupNumber2].Driver.DrawManager);
	//----------------------------------------------------------------------------
	WS2812_ColorT color =
	{
		.Green = 0x01,
		.Red = 0x01,
		.Blue = 0x01
	};
	
	WS2812_FillPixels(&CupsController.Cups[CupNumber1].Driver, color, 0, 8);
	WS2812_FillPixels(&CupsController.Cups[CupNumber2].Driver, color, 0, 8);
	WS2812_FillPixels(&CupsController.Cups[CupNumber3].Driver, color, 0, 8);
	WS2812_FillPixels(&CupsController.Cups[CupNumber4].Driver, color, 0, 8);
	
  return 0;
}
//==============================================================================
