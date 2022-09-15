/*
 *
 */
//==============================================================================
#include "Carousel_RxTransactions.h"
//==============================================================================
static void GetStatus(xRxRequestManagerT* manager)
{
	CarouselT* carousel = manager->Device;
	
	xRxPutInResponseBuffer(manager->RxLine, &carousel->Status, sizeof(carousel->Status));
}
//----------------------------------------------------------------------------
static void GetOptions(xRxRequestManagerT* manager)
{
	CarouselT* carousel = manager->Device;
	
	xRxPutInResponseBuffer(manager->RxLine, &carousel->Options, sizeof(carousel->Options));
}
//----------------------------------------------------------------------------
static void GetPosition(xRxRequestManagerT* manager)
{
	CarouselT* carousel = manager->Device;
	
	CarouselResponseGetPositionT response =
	{
		.RequestAngle = carousel->RequestAngle,
		.TotalAngle = carousel->TotalAngle,
		.EncoderPosition = CarouselGetAdapterValue(carousel, CarouselAdapterValueStepPosition)
	};
	
	xRxPutInResponseBuffer(manager->RxLine, &response, sizeof(response));
}
//----------------------------------------------------------------------------
static void GetMotionState(xRxRequestManagerT* manager)
{
	CarouselT* carousel = manager->Device;
	
	CarouselResponseGetMotionStateT response =
	{
		.Status = carousel->Status,
		.RequestAngle = carousel->RequestAngle,
		.TotalAngle = carousel->TotalAngle,
		.Power = carousel->TotalPower,
		
		.MoveTime = carousel->MoveTime,
		
		.EncoderPosition = CarouselGetAdapterValue(carousel, CarouselAdapterValueStepPosition)
	};
	
	xRxPutInResponseBuffer(manager->RxLine, &response, sizeof(response));
}
//----------------------------------------------------------------------------
static void GetCalibration(xRxRequestManagerT* manager)
{
	CarouselT* carousel = manager->Device;
	
	xRxPutInResponseBuffer(manager->RxLine, &carousel->Calibration, sizeof(carousel->Calibration));
}
//==============================================================================
static void SetPosition(xRxRequestManagerT* manager, CarouselRequestSetPositionT* request)
{
	CarouselT* carousel = manager->Device;
	int16_t result = CarouselSetPosition(carousel, request);
	
	xRxPutInResponseBuffer(manager->RxLine, &result, sizeof(result));
	xRxPutInResponseBuffer(manager->RxLine, &carousel->Status, sizeof(carousel->Status));
}
//----------------------------------------------------------------------------
static void SetOptions(xRxRequestManagerT* manager, CarouselRequestSetOptionsT* request)
{
	CarouselT* carousel = manager->Device;
	int16_t result = CarouselSetOptions(carousel, request);
	
	xRxPutInResponseBuffer(manager->RxLine, &result, sizeof(result));
	xRxPutInResponseBuffer(manager->RxLine, &carousel->Options, sizeof(carousel->Options));
}
//----------------------------------------------------------------------------
static void SetCalibration(xRxRequestManagerT* manager, CarouselCalibrationT* request)
{
	CarouselT* carousel = manager->Device;
	int16_t result = CarouselSetColibration(carousel, request);
	
	xRxPutInResponseBuffer(manager->RxLine, &result, sizeof(result));
}
//==============================================================================
static void TryResetPosition(xRxRequestManagerT* manager)
{
	CarouselT* carousel = manager->Device;
	int16_t result = CarouselDeclareAdapterRequest(carousel, CarouselAdapterRequestClearPosition, 0, 0);
	
	CarouselResponseTryClearPositionT response =
	{
		.RequestAngle = carousel->RequestAngle,
		.TotalAngle = carousel->TotalAngle,
		.EncoderPosition = CarouselGetAdapterValue(carousel, CarouselAdapterValueStepPosition)
	};
	
	xRxPutInResponseBuffer(manager->RxLine, &result, sizeof(result));
	xRxPutInResponseBuffer(manager->RxLine, &response, sizeof(response));
}
//----------------------------------------------------------------------------
static void TryStop(xRxRequestManagerT* manager)
{
	CarouselT* carousel = manager->Device;
	int16_t result = CarouselStop(carousel);
	
	xRxPutInResponseBuffer(manager->RxLine, &result, sizeof(result));
	xRxPutInResponseBuffer(manager->RxLine, &carousel->Status, sizeof(carousel->Status));
}
//==============================================================================
const xRxTransactionT CarouselTransactions[] =
{
	//----------------------------------------------------------------------------
	//GET
	{
		.Id = CAROUSEL_GET_STATUS,
		.Action = (xRxTransactionAction)GetStatus,
	},
	
	{
		.Id = CAROUSEL_GET_OPTIONS,
		.Action = (xRxTransactionAction)GetOptions,
	},
	
	{
		.Id = CAROUSEL_GET_POSITION,
		.Action = (xRxTransactionAction)GetPosition,
	},
	
	{
		.Id = CAROUSEL_GET_MOTION_STATE,
		.Action = (xRxTransactionAction)GetMotionState,
	},
	
	{
		.Id = CAROUSEL_GET_CALIBRATION,
		.Action = (xRxTransactionAction)GetCalibration,
	},
	//----------------------------------------------------------------------------
	//SET
	{
		.Id = CAROUSEL_SET_POSITION,
		.Action = (xRxTransactionAction)SetPosition,
	},
	
	{
		.Id = CAROUSEL_SET_OPTIONS,
		.Action = (xRxTransactionAction)SetOptions,
	},
	
	{
		.Id = CAROUSEL_SET_CALIBRATION,
		.Action = (xRxTransactionAction)SetCalibration,
	},
	//----------------------------------------------------------------------------
	//TRY
	{
		.Id = CAROUSEL_TRY_RESET_POSITION,
		.Action = (xRxTransactionAction)TryResetPosition,
	},
	
	{
		.Id = CAROUSEL_TRY_STOP,
		.Action = (xRxTransactionAction)TryStop,
	},
	//----------------------------------------------------------------------------
	// end of transactions marker
  { .Id = -1 }
};
//==============================================================================