//==============================================================================
#include "FlowDirector_RxRequests.h"
#include "FlowDirector/FlowDirector_Info.h"
//==============================================================================
extern const xRxTransactionT FlowDirectorTransactions[];

static const PacketHeaderT TransactionRequestHeader =
{
	.Identificator = (PacketIdentificatorT)TRANSACTION_REQUEST_IDENTIFICATOR,
	.DeviceKey = FLOW_DIRECTOR_DEVICE_KEY
};
//----------------------------------------------------------------------------
const xRxRequestT FlowDirectorRequests[] =
{
  {
		.Header = (void*)&TransactionRequestHeader,
		.HeaderLength = sizeof(TransactionRequestHeader),
		.Action = (xRxRequestReceiverT)xRxTransactionRequestReceiver,
		.Content = (void*)&FlowDirectorTransactions
	},
	
  { 0 }
};
//==============================================================================
