//==============================================================================
#include "CupsController.h"
#include "CupsController/Controls/CupsController_LEDBase.h"
//==============================================================================
CupsControllerT CupsController;
//==============================================================================
void CupsControllerHandler()
{
	CupsControllerDraw(Cup1|Cup2);
	CupsControllerUpdateLayout(Cup1|Cup2, 1000);
}
//------------------------------------------------------------------------------
static xResult CupsControllerSetTemplate(CupSelector cups, CupDrawingTemplateT* pattern)
{
	uint8_t request = cups;
	uint8_t i = 0;
	
	if (pattern)
	{
		while (request && i < CupsCount)
		{
			if ((request & 0x01))
			{
				CupDrawManagerSetTemplate(&CupsController.Cups[i], pattern);
			}
			
			request >>= 1;
			i++;
		}
		
		return xResultAccept;
	}
	
	return xResultError;
}
//------------------------------------------------------------------------------
xResult CupsControllerSetColor(CupSelector cups, CupLEDColorT color)
{
	uint8_t request = cups;
	uint8_t i = 0;
	
	while (request && i < CupsCount)
	{
		if (request & 0x01)
		{
			WS2812_FillPixels(&CupsController.Cups[i].Driver, color, 0, CupsController.Cups[i].PixelsCount);
		}
		
		request >>= 1;
		i++;
	}
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
xResult CupsControllerUpdateLayout(CupSelector cups, uint32_t time_out)
{
	uint8_t request = cups;
	uint8_t i = 0;
	
	while (request && i < CupsCount)
	{
		if (request & 0x03)
		{
			/*
			while (WS2812_GetTransmitterStatus(&CupsController[i].Driver) != WS2812_TransmitterStopped && time_out)
			{
				if (!time_out)
				{
					return CupsControllerResultTimeOut;
				}
			}
			*/
			if (WS2812_GetTransmitterStatus(&CupsController.Cups[i].Driver) == WS2812_TransmitterStopped)
			{
				WS2812_UpdateLayout(&CupsController.Cups[i].Driver);
			}
		}
		
		request >>= 2;
		i += 2;
	}
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
xResult CupsControllerDrawingStart(CupSelector cups, CupDrawingTemplateT* pattern)
{
	uint8_t request = cups;
	uint8_t i = 0;
	
	if (pattern)
	{
		while (request && i < CupsCount)
		{
			if ((request & 0x01))
			{
				/*
				xResult result = CupsControllerDrawManagerEx1Init(&CupsControllerControl.Cups[i], (RGBCupDrawManagerEx1T*)pattern);
				if (result == xResultAccept) { goto start; }
				
				result = CupsControllerDrawManagerEx2Init(&CupsControllerControl.Cups[i], (RGBCupDrawManagerEx2T*)pattern);
				
				start:;
				if (result == xResultAccept)
				{
					CupsControllerControl.Cups[i].DrawManagerPattern = pattern;
					WS2812_DrawingStart(&CupsControllerControl.Cups[i].Driver,
															(WS2812_DrawManagerBaseT*)CupsControllerControl.Cups[i].DrawManager,
															&CupsControllerControl.Cups[i].DrawManagerInterface);
				}
				*/
			}
			
			request >>= 1;
			i++;
		}
		
		return xResultAccept;
	}
	
	return xResultError;
}
//------------------------------------------------------------------------------
xResult CupsControllerDrawingStop(CupSelector cups)
{
	uint8_t request = cups;
	uint8_t i = 0;
	
	while (request && i < CupsCount)
	{
		if (request & 0x01)
		{
			WS2812_DrawingStop(&CupsController.Cups[i].Driver.DrawManager);
		}
		
		request >>= 1;
		i++;
	}
	
	return xResultAccept;
}
//------------------------------------------------------------------------------
void CupsControllerDraw(CupSelector cups)
{
	uint8_t request = cups;
	uint8_t i = 0;
	
	while (request && i < CupsCount)
	{
		if (request & 0x01)
		{
			//WS2812_Draw(&CupsControllerControl.Cups[i].Driver);
			WS2812_DrawManagerHandler(&CupsController.Cups[i].Driver.DrawManager);
		}
		
		request >>= 1;
		i++;
	}
}
//==============================================================================
xResult CupsControllerInit(void* parent, CupsControllerInterfaceT* interface)
{
	extern const xRxRequestT CupsControllerRxRequests[];
	
	CupsController.Description = "CupsControllerControlT";
	CupsController.Parent = parent;
	CupsController.Requests = (xRxRequestT*)CupsControllerRxRequests;
	
	for (uint8_t i = 0; i < CupsCount; i++)
	{
		CupsController.Cups[i].Description = "CupsControllerT";
		CupsController.Cups[i].Parent = &CupsController;
		CupsController.Cups[i].Interface = interface;
		
		CupsController.Cups[i].Id = i;
	}
	
	return xResultAccept;
}
//==============================================================================
