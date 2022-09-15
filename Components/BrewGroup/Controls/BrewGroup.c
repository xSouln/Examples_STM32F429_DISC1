//==============================================================================
#include <string.h>
#include "BrewGroup.h"
//==============================================================================
void BrewGroupHandler(BrewGroupT* BrewGroup)
{
	BrewGroup->Motor.Interface.Handler(BrewGroup);
}
//==============================================================================
xResult BrewGroupStop(BrewGroupT* BrewGroup)
{
	
	return xResultAccept;
}
//==============================================================================
xResult BrewGroupInit(BrewGroupT* BrewGroup, void* parent, BrewGroupInterfaceT* interface)
{
	extern const xRxRequestT BrewGroupRequests[];
	
	if (BrewGroup && interface)
	{
		BrewGroup->Description = "BrewGroupT";
		BrewGroup->Parent = parent;
		BrewGroup->Interface = interface;
		
		BrewGroup->Requests = (xRxRequestT*)BrewGroupRequests;
		
		return xResultAccept;
	}
	return xResultLinkError;
}
//==============================================================================
