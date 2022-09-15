//==============================================================================
#include <string.h>
#include "FlowDirector.h"
//==============================================================================
void FlowDirectorHandler(FlowDirectorT* FlowDirector)
{
	FlowDirector->Motor.Interface.Handler(FlowDirector);
}
//==============================================================================
xResult FlowDirectorStop(FlowDirectorT* FlowDirector)
{
	
	return xResultAccept;
}
//==============================================================================
xResult FlowDirectorInit(FlowDirectorT* FlowDirector, void* parent, FlowDirectorInterfaceT* interface)
{
	extern const xRxRequestT FlowDirectorRequests[];
	
	if (FlowDirector && interface)
	{
		FlowDirector->Description = "FlowDirectorT";
		FlowDirector->Parent = parent;
		FlowDirector->Interface = interface;
		
		FlowDirector->Requests = (xRxRequestT*)FlowDirectorRequests;
		
		return xResultAccept;
	}
	return xResultLinkError;
}
//==============================================================================
