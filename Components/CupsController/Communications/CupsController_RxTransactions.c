/*
 *
 */
//==============================================================================
#include "CupsController_RxTransactions.h"
//==============================================================================
static void SetColor(xRxRequestManagerT* manager, CupsControllerRequestSetColorT* request)
{
	CupLEDColorT color =
	{
		.Blue = request->Color.Blue,
		.Red = request->Color.Red,
		.Green = request->Color.Green,
	};
	
	uint16_t result = CupsControllerSetColor(request->Selector, color);
	
	xRxPutInResponseBuffer(manager->RxLine, &result, sizeof(result));
}
//----------------------------------------------------------------------------
static void SetTemplaet(xRxRequestManagerT* manager, CupsControllerRequestSetTemplaetT* request)
{
	
	//xRxPutInResponseBuffer(manager->RxLine, &result, sizeof(result));
}
//==============================================================================
static void GetStatus(xRxRequestManagerT* manager)
{
	for (uint8_t i = 0; i < CupsCount; i++)
	{
		xRxPutInResponseBuffer(manager->RxLine, &CupsController.Cups[i].Status, sizeof(CupsController.Cups[i].Status));
	}
}
//----------------------------------------------------------------------------
static void GetTemplaetId(xRxRequestManagerT* manager)
{
	for (uint8_t i = 0; i < CupsCount; i++)
	{
		xRxPutInResponseBuffer(manager->RxLine, &CupsController.Cups[i].DrawingTemplate.Id, sizeof(CupsController.Cups[i].DrawingTemplate.Id));
	}
}
//==============================================================================
const xRxTransactionT CupsControllerTransactions[] =
{
	//----------------------------------------------------------------------------
	//----------------------------------------------------------------------------
	//GET
	{
		.Id = CUPS_CONTROLLER_GET_STATUS,
		.Action = (xRxTransactionAction)GetStatus,
	},
	
	{
		.Id = CUPS_CONTROLLER_GET_TEMPLATE_ID,
		.Action = (xRxTransactionAction)GetTemplaetId,
	},
	//----------------------------------------------------------------------------
	//----------------------------------------------------------------------------
	//SET
	{
		.Id = CUPS_CONTROLLER_SET_COLOR,
		.Action = (xRxTransactionAction)SetColor,
	},
	
	{
		.Id = CUPS_CONTROLLER_SET_TEMPLATE,
		.Action = (xRxTransactionAction)SetColor,
	},
	//----------------------------------------------------------------------------
	//----------------------------------------------------------------------------
	//TRY
	
	//----------------------------------------------------------------------------
	//----------------------------------------------------------------------------
	// end of transactions marker
  { .Id = -1 }
};
//==============================================================================
