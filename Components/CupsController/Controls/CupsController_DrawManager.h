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
	.Steps = 10,
	
	.GreenIncrement = 1,
	.RedIncrement = 1,
	.BlueIncrement = 1,
};
//------------------------------------------------------------------------------
static const CupDrawingTemplateT DrawingTemplate2 =
{
	.Id = 2,
	
	.Diraction = 1,
	.Steps = 10,
	
	.GreenIncrement = 0.1,
	.RedIncrement = 1,
	.BlueIncrement = 0.33,
};
//==============================================================================
xResult CupsControllerDrawManagerInit(CupT* cup, const CupDrawingTemplateT* drawing_template);

xResult CupDrawManagerSetTemplate(CupT* cup, CupDrawingTemplateT* request);
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif
