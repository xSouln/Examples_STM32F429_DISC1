//==============================================================================
#include <string.h>
#include "Slider.h"
//==============================================================================
void SliderHandler(SliderT* Slider)
{
	Slider->Adapter.Interface->Handler(Slider);
}
//------------------------------------------------------------------------------
uint32_t SliderGetAdapterValue(SliderT* Slider, SliderAdapterValueSelector selector)
{
	return Slider->Adapter.Interface->GetValue(Slider, selector);
}
//------------------------------------------------------------------------------
uint32_t SliderSetAdapterValue(SliderT* Slider, SliderAdapterValueSelector selector, uint32_t value)
{
	return Slider->Adapter.Interface->SetValue(Slider, selector, value);
}
//------------------------------------------------------------------------------
xResult SliderDeclareAdapterRequest(SliderT* Slider, SliderAdapterRequestSelector selector, uint32_t args, uint32_t count)
{
	return Slider->Adapter.Interface->RequestListener(Slider, selector, args, count);
}
//------------------------------------------------------------------------------
void SliderDeclareAdapterEvent(SliderT* Slider, SliderAdapterEventSelector selector, uint32_t args, uint32_t count)
{
	Slider->Adapter.Interface->EventListener(Slider, selector, args, count);
}
//==============================================================================
xResult SliderSetOptions(SliderT* Slider, SliderOptionsT* request)
{
	
	return xResultBusy;
}
//------------------------------------------------------------------------------
xResult SliderClose(SliderT* Slider, SliderMoveRequestT* request)
{
	return Slider->Adapter.Interface->RequestListener(Slider,
																							SliderAdapterRequestClose,
																							(uint32_t)request,
																							0);
}
//------------------------------------------------------------------------------
xResult SliderOpen(SliderT* Slider, SliderMoveRequestT* request)
{
	
	return Slider->Adapter.Interface->RequestListener(Slider,
																							SliderAdapterRequestOpen,
																							(uint32_t)request,
																							0);
}
//------------------------------------------------------------------------------
xResult SliderStop(SliderT* Slider)
{
	return Slider->Adapter.Interface->RequestListener(Slider,
																							SliderAdapterRequestStop,
																							0,
																							0);
}
//==============================================================================
xResult SliderInit(SliderT* Slider, void* parent, SliderInterfaceT* interface)
{
	extern const xRxRequestT SliderRequests[];
	
	if (Slider && interface)
	{
		Slider->Description = "SliderT";
		Slider->Parent = parent;
		Slider->Interface = interface;
		
		Slider->Requests = (xRxRequestT*)SliderRequests;
		
		return xResultAccept;
	}
	return xResultLinkError;
}
//==============================================================================
