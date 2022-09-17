//==============================================================================
#ifndef _CUPS_CONTROLLER_TYPES_H
#define _CUPS_CONTROLLER_TYPES_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
 extern "C" {
#endif 
//==============================================================================
#include <stdlib.h>
#include "main.h"
#include "WS2812/WS2812.h"
#include "Common/xRxTransaction.h"
#include "CupsController/CupsController_Info.h"
#include "CupsController/CupsController_Config.h"
#include "Components_Config.h"
#include "CupsController/Controls/CupsController_LEDBase.h"
#include "CupsController/Controls/CupsController_HeaterBase.h"
#include "CupsController/Controls/CupsController_FlowDirectorBase.h"
//==============================================================================
typedef WS2812_ColorT CupLEDColorT;
//------------------------------------------------------------------------------
typedef enum
{
	CupNumber1,
	CupNumber2,
	CupNumber3,
	CupNumber4,
	
	CupsCount
	
} Cups;
//------------------------------------------------------------------------------
typedef enum
{
	Cup1 = 1 << CupNumber1,
	Cup2 = 1 << CupNumber2,
	Cup3 = 1 << CupNumber3,
	Cup4 = 1 << CupNumber4,
	
	CupsAll = 0xff
	
} CupSelector;
//------------------------------------------------------------------------------
typedef enum
{
	CupsControllerEventIdle,
	CupsControllerEventUpdateLayoutStarted,
	CupsControllerEventUpdateLayoutComplite,
	
} CupsControllerEventSelector;
//------------------------------------------------------------------------------
typedef enum
{
	CupsControllerRequestIdle,
	
} CupsControllerRequestSelector;
//------------------------------------------------------------------------------
typedef enum
{
	CupsControllerValueIdle,
	
} CupsControllerValueSelector;
//==============================================================================
typedef union
{
	struct
	{
		uint32_t DrawingIsEnable : 1;
	};
	uint32_t Value;
	
} CupsControllerStatusT;
//------------------------------------------------------------------------------
typedef void (*CupsControllerEventListenerT)(void* cup, CupsControllerEventSelector event, uint32_t args, uint32_t count);
typedef xResult (*CupsControllerRequestListenerT)(void* cup, CupsControllerRequestSelector event, uint32_t args, uint32_t count);
//------------------------------------------------------------------------------
typedef struct
{
	CupsControllerEventListenerT EventListener;
	CupsControllerRequestListenerT RequestListener;
	
} CupsControllerInterfaceT;
//------------------------------------------------------------------------------
typedef struct
{
	char* Description;
	uint8_t Id;
	
	int8_t Diraction;
	
	int16_t Steps;
	int16_t StepNumber;
	
	float GreenIncrement;
	float RedIncrement;
	float BlueIncrement;
	
} CupDrawingTemplateT;
//------------------------------------------------------------------------------
typedef struct
{
	OBJECT_HEADER;
	
	CupsControllerInterfaceT* Interface;
	
	CupsControllerLEDBaseT LED;
	CupsControllerHeaterBaseT Heater;
	
	CupsControllerStatusT Status;
	WS2812_T Driver;
	
	CupDrawingTemplateT DrawingTemplate;
	
	uint16_t PixelsCount;
	
	uint8_t Id;
	
	WS2812_BufT* DataBuffer;
	uint16_t DataBufferSize;
	
} CupT;
//------------------------------------------------------------------------------
typedef struct
{
	void* Description;
	void* Parent;
	
	CupT Cups[CupsCount];
	
	CupsControllerFlowDirectorBaseT FlowDirector;
	
	xRxRequestT* Requests;
	
} CupsControllerT;
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif /* RGB_CUP_TYPES_H */
