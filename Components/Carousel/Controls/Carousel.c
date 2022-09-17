//==============================================================================
#include <string.h>
#include <math.h>
#include "Carousel.h"
//==============================================================================
//------------------------------------------------------------------------------
uint32_t CarouselGetAdapterValue(CarouselT* carousel, CarouselMotorValueSelector selector)
{
	return carousel->Motor.Interface->GetValue(carousel, selector);
}
//------------------------------------------------------------------------------
uint32_t CarouselSetAdapterValue(CarouselT* carousel, CarouselMotorValueSelector selector, uint32_t value)
{
	return carousel->Motor.Interface->SetValue(carousel, selector, value);
}
//------------------------------------------------------------------------------
xResult CarouselDeclareAdapterRequest(CarouselT* carousel, CarouselMotorRequestSelector selector, uint32_t args, uint32_t count)
{
	return carousel->Motor.Interface->RequestListener(carousel, selector, args, count);
}
//------------------------------------------------------------------------------
void CarouselDeclareAdapterEvent(CarouselT* carousel, CarouselMotorEventSelector selector, uint32_t args, uint32_t count)
{
	carousel->Motor.Interface->EventListener(carousel, selector, args, count);
}
//------------------------------------------------------------------------------
//==============================================================================
void CarouselHandler(CarouselT* carousel)
{
	carousel->Motor.Interface->Handler(carousel);
}
//==============================================================================
xResult CarouselSetOptions(CarouselT* carousel, CarouselOptionsT* request)
{
	if (carousel->Status.Motion == CarouselMotionStateStopped)
	{
		if (carousel->Motor.Interface->RequestListener(carousel,
				CarouselMotorRequestSetOptions,
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
	return carousel->Motor.Interface->RequestListener(carousel,
																										CarouselMotorRequestSetPosition,
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
		return carousel->Motor.Interface->RequestListener(carousel,
																											CarouselMotorRequestClearPosition,
																											0,
																											0);
	}
	
	return xResultBusy;
}
//------------------------------------------------------------------------------
xResult CarouselCalibrateAsync(CarouselT* carousel)
{
	if (carousel->Status.Calibration != CarouselCalibratinStatusCalibrating
		&& carousel->Status.Motion == CarouselMotionStateStopped)
	{
		CarouselRequestSetPositionT request;
		
		carousel->Calibration.Position = CAROUSEL_DEFAULT_POSITION_CALIBRATION_VALUE;
		carousel->Status.CalibrationState = CarouselCalibratinStateFindZeroMark;
		carousel->Status.Calibration = CarouselCalibratinStatusCalibrating;
		
		request.Angle = -10000;
		request.Power = 80.0;
		request.Timeout = 60000;
		request.Mode = CarouselSetPositionModeStopAtZeroMark;
		
		CarouselResetPosition(carousel);
		CarouselSetPosition(carousel, &request);
	}
	return xResultBusy;
}
//------------------------------------------------------------------------------
xResult CarouselSetPod(CarouselT* carousel, uint8_t number)
{
	if (number >= CAROUSEL_PODS_COUNT)
	{
		return xResultOutOfRange;
	}
	
	float request_angle = 360.0 / CAROUSEL_PODS_COUNT * number + carousel->Calibration.Offset;
	float total_angle = carousel->TotalAngle;
	
	int n = (int)(total_angle / 360.0);	
	total_angle -= 360.0 * n;
	
	if (total_angle < 0)
	{
		total_angle = 360 + total_angle;
	}
	
	int dirrect = 1;
	
	if (request_angle > 360.0)
	{
		request_angle -= 360.0;
	}
	
	float difference = fabs(request_angle - total_angle);
	
	if (difference > 180)
	{
		difference = 360 - difference;
		difference *= -1;
	}
	
	if (total_angle > request_angle)
	{
		dirrect = -1;
	}
	
	float angle = dirrect * difference + carousel->TotalAngle;
	
	CarouselRequestSetPositionT request =
	{
		.Angle = angle,
		.Power = carousel->Options.Power,
		.Timeout = 60000
	};
	
	return CarouselSetPosition(carousel, &request);
}
//------------------------------------------------------------------------------
xResult CarouselStop(CarouselT* carousel)
{
	carousel->Motor.Interface->RequestListener(carousel,
																							CarouselMotorRequestStop,
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
		
		carousel->Calibration.Position = CAROUSEL_DEFAULT_POSITION_CALIBRATION_VALUE;
		carousel->Calibration.Offset = CAROUSEL_DEFAULT_POSITION_OFFSET;
		
		carousel->Options.StartPower = CAROUSEL_DEFAULT_MOVE_STAR_POWER;
		carousel->Options.StopPower = CAROUSEL_DEFAULT_MOVE_STOP_POWER;
		carousel->Options.Acceleration = CAROUSEL_DEFAULT_MOVE_ACCELERATION;
		carousel->Options.Deceleration = CAROUSEL_DEFAULT_MOVE_DECCELERATION;
		carousel->Options.Power = CAROUSEL_DEFAULT_MOVE_POWER;
		
		carousel->Requests = (xRxRequestT*)CarouselRequests;
		
		return xResultAccept;
	}
	return xResultLinkError;
}
//==============================================================================
