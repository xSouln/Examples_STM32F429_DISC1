//==============================================================================
#include <string.h>
#include "CupsController_DrawManager.h"
#include "WS2812/WS2812.h"
//==============================================================================
static char CupDrawManagerDescription[] = "CupDrawManagerT";
static char CupDrawManagerTemplateDescription[] = "CupDrawingTemplateT";
//==============================================================================
static void CupDrawingHandler(WS2812_DrawManagerBaseT* base)
{
	CupDrawingTemplateT* drawing_template = (CupDrawingTemplateT*)base->Child;
	CupT* cup = base->Parent;
	
	if (drawing_template->StepNumber >= drawing_template->Steps)
	{
		drawing_template->StepNumber = drawing_template->Steps;
		drawing_template->Diraction = -1;
	}
	else if (drawing_template->StepNumber < 0)
	{
		drawing_template->StepNumber = 0;
		drawing_template->Diraction = 1;
	}
	
	CupLEDColorT pixel =
	{
		.Green = (uint8_t)(drawing_template->GreenIncrement * drawing_template->StepNumber),
		.Red = (uint8_t)(drawing_template->RedIncrement * drawing_template->StepNumber),
		.Blue = (uint8_t)(drawing_template->BlueIncrement * drawing_template->StepNumber)
	};
	
	drawing_template->StepNumber += drawing_template->Diraction;
	
	WS2812_FillPixels(&cup->Driver, pixel, 0, cup->PixelsCount);
}
//------------------------------------------------------------------------------
xResult CupDrawManagerSetTemplate(CupT* cup, CupDrawingTemplateT* request)
{
	if (request && memcmp(CupDrawManagerTemplateDescription, request->Description, sizeof_str(CupDrawManagerTemplateDescription)) == 0)
	{
		memcpy(&cup->DrawingTemplate, request, sizeof(cup->DrawingTemplate));
	}
	
	return xResultNotSupported;
}
//------------------------------------------------------------------------------
static xResult RequestListener(WS2812_DrawManagerBaseT* base, WS2812_DrawManagerRequestSelector selector, uint32_t args, uint32_t count)
{
	CupT* cup = base->Parent;
	
	switch ((int)selector)
	{
		case WS2812_DrawManagerRequestDrawingStart:
			cup->Status.DrawingIsEnable = true;
			break;
		
		case WS2812_DrawManagerRequestDrawingStop:
			cup->Status.DrawingIsEnable = false;
			break;
		
		case WS2812_DrawManagerRequestSetTemplate:
			CupDrawManagerSetTemplate(cup, (CupDrawingTemplateT*)args);
			break;
		
		default : return xResultRequestIsNotFound;
	}
	
	return xResultAccept;
}
//==============================================================================
xResult CupsControllerDrawManagerInit(CupT* cup, const CupDrawingTemplateT* drawing_template)
{
	if (cup && drawing_template)
	{
		WS2812_DrawManagerBaseInit(&cup->Driver.DrawManager, cup);
		
		cup->Driver.DrawManager.Description = CupDrawManagerDescription;
		cup->Driver.DrawManager.Child = &cup->DrawingTemplate;
		cup->DrawingTemplate.Description = CupDrawManagerTemplateDescription;
		
		memcpy(&cup->DrawingTemplate, drawing_template, sizeof(cup->DrawingTemplate));
		
		cup->Driver.DrawManager.Interface.Handler = (WS2812_DrawManagerHandlerT)CupDrawingHandler;
		cup->Driver.DrawManager.Interface.RequestListener = (WS2812_DrawManagerRequestListenerT)RequestListener;
		
		return xResultAccept;
	}
	
	return xResultError;
}
//==============================================================================
