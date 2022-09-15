//==============================================================================
#include <string.h>
#include "Carousel.h"
//==============================================================================
void CarouselHandler(CarouselT* carousel)
{
	carousel->Adapter.Interface->Handler(carousel);
}
//------------------------------------------------------------------------------
uint32_t CarouselGetAdapterValue(CarouselT* carousel, CarouselAdapterValueSelector selector)
{
	return carousel->Adapter.Interface->GetValue(carousel, selector);
}
//------------------------------------------------------------------------------
uint32_t CarouselSetAdapterValue(CarouselT* carousel, CarouselAdapterValueSelector selector, uint32_t value)
{
	return carousel->Adapter.Interface->SetValue(carousel, selector, value);
}
//------------------------------------------------------------------------------
xResult CarouselDeclareAdapterRequest(CarouselT* carousel, CarouselAdapterRequestSelector selector, uint32_t args, uint32_t count)
{
	return carousel->Adapter.Interface->RequestListener(carousel, selector, args, count);
}
//------------------------------------------------------------------------------
void CarouselDeclareAdapterEvent(CarouselT* carousel, CarouselAdapterEventSelector selector, uint32_t args, uint32_t count)
{
	carousel->Adapter.Interface->EventListener(carousel, selector, args, count);
}
//==============================================================================
xResult CarouselSetOptions(CarouselT* carousel, CarouselOptionsT* request)
{
	if (carousel->Status.Motion == CarouselMotionStateStopped)
	{
		if (carousel->Adapter.Interface->RequestListener(carousel,
				CarouselAdapterRequestSetOptions,
				(uint32_t)request, 0) == xResultAccept)
		{
			memcpy(&carousel->Options, request, sizeof(carousel->Options));
			return xResultAccept;
		}
		
		return xResultError;
	}
	
	return xResultBusy;
}
//------------------------------------------------------------------------------
xResult CarouselSetPosition(CarouselT* carousel, CarouselRequestSetPositionT* request)
{
	return carousel->Adapter.Interface->RequestListener(carousel,
																											CarouselAdapterRequestSetPosition,
																											(uint32_t)request,
																											0);
}
//------------------------------------------------------------------------------
xResult CarouselSetColibration(CarouselT* carousel, CarouselCalibrationT* request)
{
	if (carousel->Status.Motion == CarouselMotionStateStopped)
	{
		memcpy(&carousel->Calibration, request, sizeof(carousel->Calibration));
		
		return xResultAccept;
	}
	
	return xResultBusy;
}
//------------------------------------------------------------------------------
xResult CarouselResetPosition(CarouselT* carousel)
{
	if (carousel->Status.Motion == CarouselMotionStateStopped)
	{
		return carousel->Adapter.Interface->RequestListener(carousel,
																											CarouselAdapterRequestClearPosition,
																											0,
																											0);
	}
	
	return xResultBusy;
}
//------------------------------------------------------------------------------
xResult CarouselStop(CarouselT* carousel)
{
	carousel->Adapter.Interface->RequestListener(carousel,
																								CarouselAdapterRequestStop,
																								0,
																								0);
	
	return xResultAccept;
}
//==============================================================================
xResult CarouselInit(CarouselT* carousel, void* parent, CarouselInterfaceT* interface)
{
	extern const xRxRequestT CarouselRequests[];
	
	if (carousel && interface)
	{
		carousel->Description = "CarouselT";
		carousel->Parent = parent;
		carousel->Interface = interface;
		
		carousel->Calibration.Position = 1000.0;
		carousel->Options.Acceleration = 33.0;
		carousel->Options.Deceleration = 33.0;
		carousel->Options.StartPower = 10.0;
		carousel->Options.StopPower = 10.0;
		
		carousel->Requests = (xRxRequestT*)CarouselRequests;
		
		return xResultAccept;
	}
	return xResultLinkError;
}
//==============================================================================
