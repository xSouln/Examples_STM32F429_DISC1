/*
 *
 */
//==============================================================================
#include "SLIDER_RxTransactions.h"
//==============================================================================
static void GetStatus(xRxRequestManagerT* manager)
{
	SliderT* Slider = manager->Device;
	
	xRxPutInResponseBuffer(manager->RxLine, &Slider->Status, sizeof(Slider->Status));
}
//----------------------------------------------------------------------------
static void GetOptions(xRxRequestManagerT* manager)
{
	SliderT* Slider = manager->Device;
	
	xRxPutInResponseBuffer(manager->RxLine, &Slider->Options, sizeof(Slider->Options));
}
//==============================================================================
static void SetOptions(xRxRequestManagerT* manager, SliderOptionsT* request)
{
	SliderT* Slider = manager->Device;
	int16_t result = SliderSetOptions(Slider, request);
	
	xRxPutInResponseBuffer(manager->RxLine, &result, sizeof(result));
	xRxPutInResponseBuffer(manager->RxLine, &Slider->Options, sizeof(Slider->Options));
}
//==============================================================================
static void TryOpen(xRxRequestManagerT* manager, SliderRequestTryOpenT* request)
{
	SliderT* Slider = manager->Device;
	Slider->RxLine = manager->RxLine;
	
	int16_t result = SliderOpen(Slider, request);
	
	xRxPutInResponseBuffer(manager->RxLine, &result, sizeof(result));
	xRxPutInResponseBuffer(manager->RxLine, &Slider->Status, sizeof(Slider->Status));
}
//----------------------------------------------------------------------------
static void TryClose(xRxRequestManagerT* manager, SliderRequestTryOpenT* request)
{
	SliderT* Slider = manager->Device;
	Slider->RxLine = manager->RxLine;
	
	int16_t result = SliderClose(Slider, request);
	
	xRxPutInResponseBuffer(manager->RxLine, &result, sizeof(result));
	xRxPutInResponseBuffer(manager->RxLine, &Slider->Status, sizeof(Slider->Status));
}
//----------------------------------------------------------------------------
static void TryStop(xRxRequestManagerT* manager)
{
	SliderT* Slider = manager->Device;
	int16_t result = SliderStop(Slider);
	
	xRxPutInResponseBuffer(manager->RxLine, &result, sizeof(result));
	xRxPutInResponseBuffer(manager->RxLine, &Slider->Status, sizeof(Slider->Status));
}
//==============================================================================
const xRxTransactionT SliderTransactions[] =
{
	//----------------------------------------------------------------------------
	//GET
	{
		.Id = SLIDER_GET_STATUS,
		.Action = (xRxTransactionAction)GetStatus,
	},
	
	{
		.Id = SLIDER_GET_OPTIONS,
		.Action = (xRxTransactionAction)GetOptions,
	},
	//----------------------------------------------------------------------------
	//SET
	{
		.Id = SLIDER_SET_OPTIONS,
		.Action = (xRxTransactionAction)SetOptions,
	},
	//----------------------------------------------------------------------------
	//TRY
	{
		.Id = SLIDER_TRY_OPEN,
		.Action = (xRxTransactionAction)TryOpen,
	},
	
	{
		.Id = SLIDER_TRY_CLOSE,
		.Action = (xRxTransactionAction)TryClose,
	},
	
	{
		.Id = SLIDER_TRY_STOP,
		.Action = (xRxTransactionAction)TryStop,
	},
	//----------------------------------------------------------------------------
	// end of transactions marker
  { .Id = -1 }
};
//==============================================================================
