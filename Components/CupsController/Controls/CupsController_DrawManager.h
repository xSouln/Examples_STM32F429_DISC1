//==============================================================================
#ifndef _CUPS_CONTROLLER_DRAW_MANAGER_H
#define _CUPS_CONTROLLER_DRAW_MANAGER_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "CupsController/CupsController_Types.h"
//==============================================================================
static const CupDrawingTemplateT DrawingTemplate1 =
{
	.Id = 1,
	
	.Diraction = 1,
	.Steps = 50,
	
	.GreenIncrement = 0.33,
	.RedIncrement = 0.33,
	.BlueIncrement = 1,
};
//------------------------------------------------------------------------------
static const CupDrawingTemplateT DrawingTemplate2 =
{
	.Id = 2,
	
	.Diraction = 1,
	.Steps = 50,
	
	.GreenIncrement = 0.33,
	.RedIncrement = 0.33,
	.BlueIncrement = 0.0,
};
//------------------------------------------------------------------------------
static const CupDrawingTemplateT* DrawingTemplates[] =
{
	&DrawingTemplate1,
	&DrawingTemplate2
};
//==============================================================================
typedef enum
{
	CupTemplateIdWhiteBlink,
	CupTemplateIdRedBlink
	
} CupTemplateIdSelector;
//------------------------------------------------------------------------------
#define CUPS_CONTROLLER_LED_TEMOLATES_COUNT (sizeof(DrawingTemplates) / sizeof(DrawingTemplates[0]))
//==============================================================================
xResult CupsControllerDrawManagerInit(CupT* cup, const CupDrawingTemplateT* drawing_template);

xResult CupDrawManagerSetTemplate(CupT* cup, CupDrawingTemplateT* request);
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif
